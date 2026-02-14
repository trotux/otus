#include "AngularVelocity.h"
#include "Direction.h"
#include "ICommand.h"
#include "MacroCommand.h"
#include "MoveCommand.h"
#include "RotateCommand.h"
#include "ChangeVelocityCommand.h"

#include "UObject.h"

#include "MovableObjectAdapter.h"
#include "RotatableObjectAdapter.h"

#include <gtest/gtest.h>

#include <memory>

TEST(MC, MacroCommandMoveAndRotate)
{
    auto object = std::make_shared<otus::UObject>();

    std::shared_ptr<otus::ICommand> rotateCmd;
    std::shared_ptr<otus::ICommand> changeVelocityCmd;
    std::shared_ptr<otus::ICommand> moveCmd;

    auto rotateAdapter = std::make_shared<otus::RotatableObjectAdapter>(object);
    EXPECT_NO_THROW(rotateCmd = std::make_shared<otus::RotateCommand>(rotateAdapter));
    EXPECT_NO_THROW(changeVelocityCmd = std::make_shared<otus::ChangeVelocityCommand>(rotateAdapter));

    auto moveAdapter = std::make_shared<otus::MovableObjectAdapter>(object);
    EXPECT_NO_THROW(moveCmd = std::make_shared<otus::MoveCommand>(moveAdapter));

    object->setProperty("position", std::make_shared<otus::Point>(0,0));
    object->setProperty("direction", std::make_shared<otus::Direction>(0));
    object->setProperty("magnitude", std::make_shared<otus::Magnitude>(10));
    object->setProperty("angular_velocity", std::make_shared<otus::AngularVelocity>(90)); // 90 degree

    EXPECT_NO_THROW(changeVelocityCmd->execute()); //init velocity

    std::shared_ptr<otus::ICommand> macroCmd;
    EXPECT_NO_THROW(macroCmd = std::make_shared<otus::MacroCommand>(moveCmd, rotateCmd, changeVelocityCmd, moveCmd));
    EXPECT_NO_THROW(macroCmd->execute());

    // 0,0 -> 10, 0 -> turn on 90 degree -> 10, 10
    auto position = object->getProperty<otus::Point>("position");
    EXPECT_DOUBLE_EQ(position->getX(), 10);
    EXPECT_DOUBLE_EQ(position->getY(), 10);

    // repeat command
    EXPECT_NO_THROW(macroCmd->execute());

    // 10,10 -> 10, 20 -> turn on 90 degree -> 0, 20
    position = object->getProperty<otus::Point>("position");
    EXPECT_DOUBLE_EQ(position->getX(), 0);
    EXPECT_DOUBLE_EQ(position->getY(), 20);

    // repeat command
    EXPECT_NO_THROW(macroCmd->execute());
    // 0,20 -> -10,20 -> turn on 90 degree -> -10, 10
    position = object->getProperty<otus::Point>("position");
    EXPECT_DOUBLE_EQ(position->getX(), -10);
    EXPECT_DOUBLE_EQ(position->getY(), 10);

    // repeat command
    EXPECT_NO_THROW(macroCmd->execute());
    // -10,10 -> -10,0 -> turn on 90 degree -> 0, 0
    position = object->getProperty<otus::Point>("position");
    EXPECT_DOUBLE_EQ(position->getX(), 0);
    EXPECT_DOUBLE_EQ(position->getY(), 0);
}
