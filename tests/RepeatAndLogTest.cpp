#include "FailCommand.h"
#include "RepeatCommand.h"
#include "RepeatExceptionHandler.h"
#include "CommandQueue.h"
#include "CommandQueueProcessor.h"
#include "RepeatAndLogExceptionHandler.h"

#include "MockCommand.h"
#include "TestException.h"
#include "TestLogger.h"

#include <gtest/gtest.h>

#include <memory>

TEST(CQ, RepeatAndLog)
{
    otus::TestLogger logger;
    otus::CommandQueue queue;
    otus::ExceptionDispatcher dispatcher;
    otus::CommandQueueProcessor queueProcessor(queue, dispatcher);
    
    std::shared_ptr<otus::IExceptionHandler> handler = std::make_shared<otus::RepeatAndLogExceptionHandler>(logger);
    dispatcher.addHandler<otus::TestException>(handler);
    
    auto cmd = std::make_shared<otus::FailCommand>();
    queue.push(cmd);

    //First call
    EXPECT_EQ(cmd->getExecuteCount(), 0);
    queueProcessor.process();
    EXPECT_EQ(cmd->getExecuteCount(), 1);
    auto message = logger.getMessage();
    EXPECT_TRUE(message.empty());

    // Repeat
    queueProcessor.process();
    EXPECT_EQ(cmd->getExecuteCount(), 2);
    message = logger.getMessage();
    EXPECT_TRUE(message.empty());

    //Log
    queueProcessor.process();
    EXPECT_EQ(cmd->getExecuteCount(), 2);
    message = logger.getMessage();
    EXPECT_FALSE(message.empty());
    EXPECT_EQ(logger.getMessage(), "command \"fail\" throwed exception \"test\"");

}
