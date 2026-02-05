#include "RepeatCommand.h"
#include "RepeatExceptionHandler.h"

#include "MockCommand.h"
#include "TestException.h"

#include <gtest/gtest.h>

#include <memory>

TEST(CQ, RepeatCommand)
{
    auto cmd = std::make_shared<otus::MockCommand>();

    auto repeatCmd = std::make_shared<otus::RepeatCommand>(cmd); 
    ASSERT_NE(repeatCmd, nullptr);

    EXPECT_EQ(cmd->getExecuteCount(), 0);
    repeatCmd->execute();
    EXPECT_EQ(cmd->getExecuteCount(), 1);
}

TEST(CQ, RepeatExceptionHandler)
{
    otus::CommandQueue queue;
    otus::TestException exception("test");
    auto cmd = std::make_shared<otus::MockCommand>();

    auto handler = std::make_shared<otus::RepeatExceptionHandler>();

    handler->handle(queue, cmd, exception);

    auto repeatCmd = queue.pop();
    ASSERT_NE(repeatCmd, nullptr);

    EXPECT_EQ(cmd->getExecuteCount(), 0);
    repeatCmd->execute();
    EXPECT_EQ(cmd->getExecuteCount(), 1);
}
