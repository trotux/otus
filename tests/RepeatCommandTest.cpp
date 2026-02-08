#include "BaseException.h"
#include "CommandQueue.h"
#include "CommandQueueProcessor.h"
#include "ExceptionDispatcher.h"
#include "RepeatOnceCommand.h"
#include "RepeatOnceExceptionHandler.h"

#include "MockCommand.h"
#include "FailCommand.h"

#include <gtest/gtest.h>

#include <memory>

namespace otus
{
using FailCommandWithBaseException = otus::FailCommand<otus::BaseException>;
}

TEST(CQ, RepeatCommand)
{
    auto cmd = std::make_shared<otus::MockCommand>();
    auto repeatCmd = std::make_shared<otus::RepeatOnceCommand>(cmd);
    ASSERT_NE(repeatCmd, nullptr);

    EXPECT_EQ(cmd->getExecuteCount(), 0);
    repeatCmd->execute();
    EXPECT_EQ(cmd->getExecuteCount(), 1);
}

TEST(CQ, RepeatExceptionHandler)
{
    otus::CommandQueue queue;
    otus::ExceptionDispatcher dispatcher;
    otus::CommandQueueProcessor queueProcessor(queue, dispatcher);

    using RepeatOnceHandlerType = otus::RepeatOnceExceptionHandler<otus::FailCommandWithBaseException>;
    dispatcher.addHandler<otus::BaseException, otus::FailCommandWithBaseException, RepeatOnceHandlerType>(queue);

    auto cmd = std::make_shared<otus::FailCommand<otus::BaseException>>();

    queue.push(cmd);
    queueProcessor.process();
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(cmd->getExecuteCount(), 1);

    queueProcessor.process();
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(cmd->getExecuteCount(), 2);
}
