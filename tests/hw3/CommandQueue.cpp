#include "BaseException.h"
#include "CommandQueue.h"
#include "CommandQueueProcessor.h"
#include "CommandException.h"
#include "ExceptionDispatcher.h"

#include "MockCommand.h"
#include "FailCommand.h"
#include "FailCommand2.h"
#include "TestExceptionHandler.h"

#include <gtest/gtest.h>

#include <memory>

TEST(CQ, ExecuteCommand)
{
    otus::CommandQueue queue;
    otus::ExceptionDispatcher dispatcher;
    otus::CommandQueueProcessor queueProcessor(queue, dispatcher);

    auto handler = std::make_shared<otus::TestExceptionHandler>();
    dispatcher.addHandlerSimple<otus::BaseException, otus::MockCommand>(handler);

    auto cmd = std::make_shared<otus::MockCommand>();

    queue.push(cmd);

    queueProcessor.process();

    EXPECT_EQ(cmd->getExecuteCount(), 1);
    EXPECT_EQ(handler->getCallCount(), 0);
}

TEST(CQ, ExecuteCommandWithFail)
{
    otus::CommandQueue queue;
    otus::ExceptionDispatcher dispatcher;
    otus::CommandQueueProcessor queueProcessor(queue, dispatcher);

    auto handler = std::make_shared<otus::TestExceptionHandler>();
    dispatcher.addHandlerSimple<otus::BaseException, otus::FailCommand<otus::BaseException>>(handler);

    auto cmd = std::make_shared<otus::FailCommand<otus::BaseException>>();

    queue.push(cmd);

    queueProcessor.process();

    EXPECT_EQ(cmd->getExecuteCount(), 1);
    EXPECT_EQ(handler->getCallCount(), 1);
}

TEST(CQ, ExecuteSameCommandTwiceWithFailFromTwoDifferentException)
{
    otus::CommandQueue queue;
    otus::ExceptionDispatcher dispatcher;
    otus::CommandQueueProcessor queueProcessor(queue, dispatcher);

    auto handler1 = std::make_shared<otus::TestExceptionHandler>();
    auto handler2 = std::make_shared<otus::TestExceptionHandler>();

    dispatcher.addHandlerSimple<otus::BaseException, otus::FailCommand<otus::BaseException>>(handler1);
    dispatcher.addHandlerSimple<otus::CommandException, otus::FailCommand<otus::CommandException>>(handler2);

    auto cmd1 = std::make_shared<otus::FailCommand<otus::BaseException>>();
    auto cmd2 = std::make_shared<otus::FailCommand<otus::CommandException>>();

    queue.push(cmd1);
    queue.push(cmd2);

    while (!queue.empty())
    {
        queueProcessor.process();
    }

    EXPECT_EQ(cmd1->getExecuteCount(), 1);
    EXPECT_EQ(handler1->getCallCount(), 1);
    EXPECT_EQ(cmd2->getExecuteCount(), 1);
    EXPECT_EQ(handler2->getCallCount(), 1);
}

TEST(CQ, ExecuteDifferentCommandTwiceWithFailFromSameException)
{
    otus::CommandQueue queue;
    otus::ExceptionDispatcher dispatcher;
    otus::CommandQueueProcessor queueProcessor(queue, dispatcher);

    dispatcher.addHandler<otus::BaseException, otus::FailCommand<otus::BaseException>, otus::TestExceptionHandler>();
    dispatcher.addHandler<otus::BaseException, otus::FailCommand2<otus::BaseException>, otus::TestExceptionHandler>();

    auto cmd1 = std::make_shared<otus::FailCommand<otus::BaseException>>();
    auto cmd2 = std::make_shared<otus::FailCommand2<otus::BaseException>>();

    queue.push(cmd1);
    queue.push(cmd2);

    while (!queue.empty())
    {
        queueProcessor.process();
    }

    auto handler1 =
        dispatcher
            .getHandler<otus::BaseException, otus::FailCommand<otus::BaseException>, otus::TestExceptionHandler>();
    EXPECT_NE(handler1, nullptr);

    auto handler2 =
        dispatcher
            .getHandler<otus::BaseException, otus::FailCommand2<otus::BaseException>, otus::TestExceptionHandler>();
    EXPECT_NE(handler2, nullptr);

    EXPECT_EQ(cmd1->getExecuteCount(), 1);
    EXPECT_EQ(handler1->getCallCount(), 1);
    EXPECT_EQ(cmd2->getExecuteCount(), 1);
    EXPECT_EQ(handler2->getCallCount(), 1);
}

