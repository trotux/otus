#include "LogCommand.h"

#include "TestLogger.h"
#include "FailCommand.h"
#include "TestException.h"

#include <gtest/gtest.h>
#include <memory>

TEST(CQ, LogCommand)
{
    otus::TestLogger logger;
    auto cmd = std::make_shared<otus::FailCommand>();

    otus::TestException exception("test");

    auto logCmd = std::make_shared<otus::LogCommand>(logger, cmd, exception); 
    ASSERT_NE(logCmd, nullptr);

    logCmd->execute();

    auto message = logger.getMessage();
    EXPECT_FALSE(message.empty());
    EXPECT_EQ(logger.getMessage(), "command \"fail\" throwed exception \"test\"");
}

