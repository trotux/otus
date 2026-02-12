#include "BaseException.h"
#include "ICommand.h"
#include "MacroCommand.h"
#include "MoveCommand.h"
#include "CheckFuelCommand.h"
#include "BurnFuelCommand.h"
#include "FuelTank.h"
#include "NotEnoughFuelException.h"
#include "NoLocationException.h"
#include "NonMovableException.h"
#include "UObject.h"
#include "MovableObjectAdapter.h"

#include "MockCommand.h"
#include "MockOrderCommand.h"
#include "FailCommand.h"

#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>

TEST(MC, MacroCommand)
{
    auto cmd1 = std::make_shared<otus::MockCommand>();
    auto cmd2 = std::make_shared<otus::MockCommand>();
    auto cmd3 = std::make_shared<otus::MockCommand>();

    std::shared_ptr<otus::ICommand> macroCmd;

    EXPECT_NO_THROW(macroCmd = std::make_shared<otus::MacroCommand>(cmd1, cmd2, cmd3));
    EXPECT_NO_THROW(macroCmd->execute());

    EXPECT_EQ(cmd1->getExecuteCount(), 1);
    EXPECT_EQ(cmd2->getExecuteCount(), 1);
    EXPECT_EQ(cmd3->getExecuteCount(), 1);

    auto cmd4 = std::make_shared<otus::MockOrderCommand>(1);
    auto cmd5 = std::make_shared<otus::MockOrderCommand>(2);
    auto cmd6 = std::make_shared<otus::MockOrderCommand>(3);

    EXPECT_NO_THROW(macroCmd = std::make_shared<otus::MacroCommand>(cmd4, cmd5, cmd6));
    EXPECT_NO_THROW(macroCmd->execute());

    auto cmd7 = std::make_shared<otus::MockCommand>();
    auto cmd8 = std::make_shared<otus::FailCommand<otus::BaseException>>();
    auto cmd9 = std::make_shared<otus::MockCommand>();

    EXPECT_NO_THROW(macroCmd = std::make_shared<otus::MacroCommand>(cmd7, cmd8, cmd9));
    EXPECT_THROW(macroCmd->execute(), otus::BaseException);

    EXPECT_EQ(cmd7->getExecuteCount(), 1);
    EXPECT_EQ(cmd9->getExecuteCount(), 0);
}

TEST(MC, MacroCommandMove)
{
    auto object = std::make_shared<otus::UObject>();

    std::shared_ptr<otus::FuelTank> tank;

    EXPECT_NO_THROW(tank = std::make_shared<otus::FuelTank>(10));
    EXPECT_NE(tank, nullptr);

    std::shared_ptr<otus::ICommand> cmd1;
    std::shared_ptr<otus::ICommand> cmd2;
    std::shared_ptr<otus::ICommand> cmd3;

    EXPECT_NO_THROW(cmd1 = std::make_shared<otus::CheckFuelCommand>(tank, 3));
    EXPECT_NO_THROW(cmd3 = std::make_shared<otus::BurnFuelCommand>(tank, 3));

    std::shared_ptr<otus::MovableObjectAdapter> moveAdapter = std::make_shared<otus::MovableObjectAdapter>(object);
    EXPECT_NO_THROW(cmd2 = std::make_shared<otus::MoveCommand>(moveAdapter));

    object->setProperty("position", std::make_shared<otus::Point>(12,5));
    object->setProperty("velocity", std::make_shared<otus::Velocity>(-7,3));

    std::shared_ptr<otus::ICommand> macroCmd;
    EXPECT_NO_THROW(macroCmd = std::make_shared<otus::MacroCommand>(cmd1, cmd2, cmd3));
    EXPECT_NO_THROW(macroCmd->execute());

    auto position = object->getProperty<otus::Point>("position");

    // New postion
    EXPECT_EQ(position->getX(), 5);
    EXPECT_EQ(position->getY(), 8);

    // New fuel level
    EXPECT_EQ(tank->getLevel(), 7);

    tank->decreaseLevel(5); // current level 2, need 3
    EXPECT_THROW(macroCmd->execute(), otus::NotEnoughtFuelException);

    tank->increaseLevel(1); // current level 3, enough
    EXPECT_NO_THROW(macroCmd->execute());
    EXPECT_EQ(tank->getLevel(), 0);

    // New position
    position = object->getProperty<otus::Point>("position");
    EXPECT_EQ(position->getX(), -2);
    EXPECT_EQ(position->getY(), 11);

    tank->increaseLevel(10); // current level 10
    object->resetProperty("position");
    EXPECT_THROW(macroCmd->execute(), otus::NoLocationException);

    object->setProperty("position", std::make_shared<otus::Point>(12,5));
    object->resetProperty("velocity");
    EXPECT_THROW(macroCmd->execute(), otus::NoVelocityException);

    object->setProperty("velocity", std::make_shared<otus::Velocity>(0,0));
    EXPECT_THROW(macroCmd->execute(), otus::NonMovableException);
}
