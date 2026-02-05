#include "RepeatCommand.h"
#include "RepeatExceptionHandler.h"

#include "MockCommand.h"

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

