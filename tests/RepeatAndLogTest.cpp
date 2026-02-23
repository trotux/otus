#include "BaseException.h"
#include "FailCommand.h"
#include "RepeatOnceCommand.h"
#include "RepeatOnceExceptionHandler.h"
#include "CommandQueue.h"
#include "CommandQueueProcessor.h"
#include "LogExceptionHandler.h"

#include "FailCommand.h"
#include "TestLogger.h"

#include <gtest/gtest.h>

#include <memory>

namespace otus
{
using FailCommandWithBaseException = otus::FailCommand<otus::BaseException>;
}

TEST(CQ, RepeatAndLog)
{
    otus::TestLogger logger;
    otus::CommandQueue queue;
    otus::ExceptionDispatcher dispatcher;
    otus::CommandQueueProcessor queueProcessor(queue, dispatcher);
    auto cmd = std::make_shared<otus::FailCommand<otus::BaseException>>();

    using RepeatOnceHandlerType = otus::RepeatOnceExceptionHandler<otus::FailCommandWithBaseException>;
    dispatcher.addHandler<otus::BaseException, otus::FailCommandWithBaseException, RepeatOnceHandlerType>(queue);

    using LogHandlerType = otus::LogExceptionHandler<otus::RepeatOnceCommand>;
    dispatcher.addHandler<otus::BaseException, otus::RepeatOnceCommand, LogHandlerType>(logger, queue);

    queue.push(cmd);

    queueProcessor.process();
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(cmd->getExecuteCount(), 1);
    std::string message = logger.getMessage();
    EXPECT_TRUE(message.empty());

    queueProcessor.process();
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(cmd->getExecuteCount(), 2);
    message = logger.getMessage();
    EXPECT_TRUE(message.empty());

    queueProcessor.process();
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(cmd->getExecuteCount(), 2);

    std::string testMessage{
        "command \"otus::FailCommand<otus::BaseException>\" throw exception \"otus::BaseException\""};
    message = logger.getMessage();
    EXPECT_FALSE(message.empty());
    EXPECT_EQ(message, testMessage);
}
