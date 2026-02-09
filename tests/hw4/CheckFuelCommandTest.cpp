
#include "ICommand.h"
#include "CheckFuelCommand.h"
#include "FuelTank.h"

#include "NotEnoughFuelException.h"

#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>

TEST(MC, CheckFuelCommand)
{
    std::shared_ptr<otus::FuelTank> tank;

    EXPECT_NO_THROW(tank = std::make_shared<otus::FuelTank>(10));
    EXPECT_NE(tank, nullptr);

    std::shared_ptr<otus::ICommand> cmd;

    EXPECT_THROW(cmd = std::make_shared<otus::CheckFuelCommand>(nullptr, 3), std::runtime_error);
    EXPECT_THROW(cmd = std::make_shared<otus::CheckFuelCommand>(tank, 0), std::runtime_error);
    EXPECT_THROW(cmd = std::make_shared<otus::CheckFuelCommand>(tank, -1), std::runtime_error);

    EXPECT_NO_THROW(cmd = std::make_shared<otus::CheckFuelCommand>(tank, 3));
    EXPECT_NO_THROW(cmd->execute());

    EXPECT_NO_THROW(cmd = std::make_shared<otus::CheckFuelCommand>(tank, 10));
    EXPECT_NO_THROW(cmd->execute());

    EXPECT_NO_THROW(cmd = std::make_shared<otus::CheckFuelCommand>(tank, 12));
    EXPECT_THROW(cmd->execute(), otus::NotEnoughtFuelException);
}

