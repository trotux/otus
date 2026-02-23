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

#include <gtest/gtest.h>

#include <memory>

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
