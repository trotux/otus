#include "BaseException.h"
#include "CommandQueue.h"
#include "CommandQueueProcessor.h"

#include "RepeatTwiceCommand.h"
#include "RepeatTwiceExceptionHandler.h"
#include "RepeatOnceCommand.h"
#include "RepeatOnceExceptionHandler.h"
#include "LogExceptionHandler.h"

#include "FailCommand.h"
#include "TestLogger.h"

#include <gtest/gtest.h>

#include <memory>

namespace otus
{
using FailCommandWithBaseException = otus::FailCommand<otus::BaseException>;
}

TEST(CQ, RepeatTwiceAndLog)
{
    otus::TestLogger logger;
    otus::CommandQueue queue;
    otus::ExceptionDispatcher dispatcher;
    otus::CommandQueueProcessor queueProcessor(queue, dispatcher);

    using RepeatTwiceHandlerType = otus::RepeatTwiceExceptionHandler<otus::FailCommandWithBaseException>;
    dispatcher.addHandler<otus::BaseException, otus::FailCommandWithBaseException, RepeatTwiceHandlerType>(queue);

    using RepeatOnceHandlerType = otus::RepeatOnceExceptionHandler<otus::RepeatTwiceCommand>;
    dispatcher.addHandler<otus::BaseException, otus::RepeatTwiceCommand, RepeatOnceHandlerType>(queue);

    using LogHandlerType = otus::LogExceptionHandler<otus::RepeatOnceCommand>;
    dispatcher.addHandler<otus::BaseException, otus::RepeatOnceCommand, LogHandlerType>(logger, queue);

    auto cmd = std::make_shared<otus::FailCommand<otus::BaseException>>();
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
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(cmd->getExecuteCount(), 3);
    message = logger.getMessage();
    EXPECT_TRUE(message.empty());

    queueProcessor.process();
    EXPECT_TRUE(message.empty());
    message = logger.getMessage();

    std::string testMessage{
        "command \"otus::FailCommand<otus::BaseException>\" throw exception \"otus::BaseException\""};
    EXPECT_EQ(message, testMessage);
}

