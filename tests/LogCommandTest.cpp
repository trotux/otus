#include "BaseException.h"
#include "CommandQueue.h"
#include "CommandQueueProcessor.h"
#include "ExceptionDispatcher.h"

#include "LogCommand.h"
#include "LogExceptionHandler.h"

#include "TestLogger.h"
#include "FailCommand.h"

#include <gtest/gtest.h>

#include <memory>

namespace otus
{
using FailCommandWithBaseException = otus::FailCommand<otus::BaseException>;
}

TEST(CQ, LogCommand)
{
    otus::TestLogger logger;
    std::string testMessage = std::format("test log message");

    auto logCmd = std::make_shared<otus::LogCommand>(logger, testMessage);
    ASSERT_NE(logCmd, nullptr);

    logCmd->execute();

    auto message = logger.getMessage();
    EXPECT_FALSE(message.empty());
    EXPECT_EQ(message, testMessage);
}

TEST(CQ, LogExceptionHandler)
{
    otus::TestLogger logger;
    otus::CommandQueue queue;
    otus::ExceptionDispatcher dispatcher;
    otus::CommandQueueProcessor queueProcessor(queue, dispatcher);

    using HandlerType = otus::LogExceptionHandler<otus::FailCommandWithBaseException>;

    dispatcher.addHandler<otus::BaseException, otus::FailCommandWithBaseException, HandlerType>(logger, queue);
    auto cmd = std::make_shared<otus::FailCommand<otus::BaseException>>();

    queue.push(cmd);
    queueProcessor.process();

    EXPECT_FALSE(queue.empty());
    auto message = logger.getMessage();
    EXPECT_TRUE(message.empty());

    queueProcessor.process();

    std::string testMessage{
        "command \"otus::FailCommand<otus::BaseException>\" throw exception \"otus::BaseException\""};
    message = logger.getMessage();
    EXPECT_FALSE(message.empty());
    EXPECT_EQ(message, testMessage);
}
