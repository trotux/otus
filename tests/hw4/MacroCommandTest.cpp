#include "BaseException.h"
#include "ICommand.h"
#include "MacroCommand.h"

#include "MockCommand.h"
#include "MockOrderCommand.h"
#include "FailCommand.h"

#include <gtest/gtest.h>

#include <memory>

TEST(MC, MacroCommand)
{
    auto cmd1 = std::make_shared<otus::MockCommand>();
    auto cmd2 = std::make_shared<otus::MockCommand>();
    auto cmd3 = std::make_shared<otus::MockCommand>();

    std::shared_ptr<otus::ICommand> macroCmd = std::make_shared<otus::MacroCommand>(cmd1, cmd2, cmd3);

    EXPECT_NO_THROW(macroCmd->execute());
    EXPECT_EQ(cmd1->getExecuteCount(), 1);
    EXPECT_EQ(cmd2->getExecuteCount(), 1);
    EXPECT_EQ(cmd3->getExecuteCount(), 1);

    auto cmd4 = std::make_shared<otus::MockOrderCommand>(1);
    auto cmd5 = std::make_shared<otus::MockOrderCommand>(2);
    auto cmd6 = std::make_shared<otus::MockOrderCommand>(3);

    macroCmd = std::make_shared<otus::MacroCommand>(cmd4, cmd5, cmd6);
    EXPECT_NO_THROW(macroCmd->execute());

    auto cmd7 = std::make_shared<otus::MockCommand>();
    auto cmd8 = std::make_shared<otus::FailCommand<otus::BaseException>>();
    auto cmd9 = std::make_shared<otus::MockCommand>();

    macroCmd = std::make_shared<otus::MacroCommand>(cmd7, cmd8, cmd9);
    EXPECT_THROW(macroCmd->execute(), otus::BaseException);

    EXPECT_EQ(cmd7->getExecuteCount(), 1);
    EXPECT_EQ(cmd9->getExecuteCount(), 0);
}

