#include "ICommand.h"
#include "BurnFuelCommand.h"
#include "FuelTank.h"

#include "NotEnoughFuelException.h"

#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>

TEST(MC, BurnFuelCommand)
{
    std::shared_ptr<otus::FuelTank> tank;

    EXPECT_NO_THROW(tank = std::make_shared<otus::FuelTank>(10));
    EXPECT_NE(tank, nullptr);

    std::shared_ptr<otus::ICommand> cmd;

    EXPECT_THROW(cmd = std::make_shared<otus::BurnFuelCommand>(nullptr, 3), std::runtime_error);
    EXPECT_THROW(cmd = std::make_shared<otus::BurnFuelCommand>(tank, 0), std::runtime_error);
    EXPECT_THROW(cmd = std::make_shared<otus::BurnFuelCommand>(tank, -1), std::runtime_error);

    EXPECT_NO_THROW(cmd = std::make_shared<otus::BurnFuelCommand>(tank, 3));
    EXPECT_NO_THROW(cmd->execute());
    EXPECT_EQ(tank->getLevel(), 7);

    EXPECT_NO_THROW(cmd->execute());
    EXPECT_EQ(tank->getLevel(), 4);

    EXPECT_NO_THROW(cmd->execute());
    EXPECT_EQ(tank->getLevel(), 1);

    EXPECT_THROW(cmd->execute(), otus::NotEnoughtFuelException);

    EXPECT_NO_THROW(cmd = std::make_shared<otus::BurnFuelCommand>(tank, 1));
    EXPECT_NO_THROW(cmd->execute());
    EXPECT_EQ(tank->getLevel(), 0);
    EXPECT_TRUE(tank->empty());
}

