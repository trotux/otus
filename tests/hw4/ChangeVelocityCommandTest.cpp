#include "Direction.h"
#include "ICommand.h"
#include "ChangeVelocityCommand.h"
#include "IRotatableObject.h"
#include "RotatableObjectAdapter.h"
#include "Magnitude.h"
#include "UObject.h"
#include "Point.h"
#include "Velocity.h"

#include <gtest/gtest.h>

#include <cmath>
#include <memory>
#include "gtest/gtest.h"

TEST(MC, ChangeVelocityCommand)
{
    auto object = std::make_shared<otus::UObject>();

    std::shared_ptr<otus::ICommand> cmd;

    auto adapter = std::make_shared<otus::RotatableObjectAdapter>(object);
    EXPECT_NO_THROW(cmd = std::make_shared<otus::ChangeVelocityCommand>(adapter));

    object->setProperty("magnitude", std::make_shared<otus::Magnitude>(10));
    object->setProperty("position", std::make_shared<otus::Point>(0, 0));
    
    object->setProperty("direction", std::make_shared<otus::Direction>(0));
    EXPECT_NO_THROW(cmd->execute());
    auto velocity = object->getProperty<otus::Velocity>("velocity");
    EXPECT_NE(velocity, nullptr);
    auto deltaX = velocity->getDeltaX();
    auto deltaY = velocity->getDeltaY();
    EXPECT_DOUBLE_EQ(deltaX, 10);
    EXPECT_DOUBLE_EQ(deltaY, 0);

    object->setProperty("direction", std::make_shared<otus::Direction>(90));
    EXPECT_NO_THROW(cmd->execute());
    velocity = object->getProperty<otus::Velocity>("velocity");
    deltaX = velocity->getDeltaX();
    deltaY = velocity->getDeltaY();

    EXPECT_DOUBLE_EQ(deltaX, 0);
    EXPECT_DOUBLE_EQ(deltaY, 10);

    object->setProperty("direction", std::make_shared<otus::Direction>(180));
    EXPECT_NO_THROW(cmd->execute());
    velocity = object->getProperty<otus::Velocity>("velocity");
    deltaX = velocity->getDeltaX();
    deltaY = velocity->getDeltaY();
    EXPECT_DOUBLE_EQ(deltaX, -10);
    EXPECT_DOUBLE_EQ(deltaY, 0);

    object->setProperty("direction", std::make_shared<otus::Direction>(270));
    EXPECT_NO_THROW(cmd->execute());
    velocity = object->getProperty<otus::Velocity>("velocity");
    deltaX = velocity->getDeltaX();
    deltaY = velocity->getDeltaY();
    EXPECT_DOUBLE_EQ(deltaX, 0);
    EXPECT_DOUBLE_EQ(deltaY, -10);

    object->setProperty("direction", std::make_shared<otus::Direction>(45));
    EXPECT_NO_THROW(cmd->execute());
    velocity = object->getProperty<otus::Velocity>("velocity");
    EXPECT_NE(velocity, nullptr);
    deltaX = velocity->getDeltaX();
    deltaY = velocity->getDeltaY();
    EXPECT_DOUBLE_EQ(deltaX, std::sqrt(50));
    EXPECT_DOUBLE_EQ(deltaY, std::sqrt(50));

    object->setProperty("direction", std::make_shared<otus::Direction>(135));
    EXPECT_NO_THROW(cmd->execute());
    velocity = object->getProperty<otus::Velocity>("velocity");
    EXPECT_NE(velocity, nullptr);
    deltaX = velocity->getDeltaX();
    deltaY = velocity->getDeltaY();
    EXPECT_DOUBLE_EQ(deltaX, -std::sqrt(50));
    EXPECT_DOUBLE_EQ(deltaY, std::sqrt(50));

    object->setProperty("direction", std::make_shared<otus::Direction>(225));
    EXPECT_NO_THROW(cmd->execute());
    velocity = object->getProperty<otus::Velocity>("velocity");
    EXPECT_NE(velocity, nullptr);
    deltaX = velocity->getDeltaX();
    deltaY = velocity->getDeltaY();
    EXPECT_DOUBLE_EQ(deltaX, -std::sqrt(50));
    EXPECT_DOUBLE_EQ(deltaY, -std::sqrt(50));

    object->setProperty("direction", std::make_shared<otus::Direction>(315));
    EXPECT_NO_THROW(cmd->execute());
    velocity = object->getProperty<otus::Velocity>("velocity");
    EXPECT_NE(velocity, nullptr);
    deltaX = velocity->getDeltaX();
    deltaY = velocity->getDeltaY();
    EXPECT_DOUBLE_EQ(deltaX, std::sqrt(50));
    EXPECT_DOUBLE_EQ(deltaY, -std::sqrt(50));
}

