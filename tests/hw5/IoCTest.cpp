#include "ICommand.h"
#include "ioc/Base.h"

#include "Test1Command.h"
#include "Test2Command.h"

#include <gtest/gtest.h>

#include <any>
#include <functional>
#include <memory>

TEST(IOC, BaseTest)
{
    otus::ioc::Base ioc;

    // create scope "test1"
    ioc.resolve<otus::ICommand>(otus::ioc::Base::Action{"Scopes.New", "test1"})->execute();

    // set scope "test1" as current
    ioc.resolve<otus::ICommand>(otus::ioc::Base::Action{"Scopes.Current", "test1"})->execute();

    // try to resolve "test.command" in scope "test1"
    auto cmd = ioc.resolve<otus::ICommand>("test.command");
    cmd->execute();

    // check command execution result, does not register any command
    EXPECT_EQ(otus::Test1Command::getExecuteCount(), 0);
    EXPECT_EQ(otus::Test2Command::getExecuteCount(), 0);

    // register test.command for Test1Command in scope test1
    ioc.resolve<otus::ICommand>(
        otus::ioc::Base::Action{"IOC.Register", "test.command"},
        std::function([](std::vector<std::any> args) -> std::shared_ptr<otus::ICommand>
        {
            return std::make_shared<otus::Test1Command>();
        })
    )->execute();

    // try to resolve "test.command" in scope "test1"
    cmd = ioc.resolve<otus::ICommand>("test.command");
    cmd->execute();

    // check command execution result
    EXPECT_EQ(otus::Test1Command::getExecuteCount(), 1);
    EXPECT_EQ(otus::Test2Command::getExecuteCount(), 0);

    // create scope "test2"
    ioc.resolve<otus::ICommand>(otus::ioc::Base::Action{"Scopes.New", "test2"})->execute();

    // set scope "test2" as current
    ioc.resolve<otus::ICommand>(otus::ioc::Base::Action{"Scopes.Current", "test2"})->execute();

    // try to resolve "test.command" in scope "test2"
    cmd = ioc.resolve<otus::ICommand>("test.command");
    cmd->execute();

    // check command execution result, must not to be changed
    EXPECT_EQ(otus::Test1Command::getExecuteCount(), 1);
    EXPECT_EQ(otus::Test2Command::getExecuteCount(), 0);

    // register test.command for Test2Command in scope test2
    ioc.resolve<otus::ICommand>(otus::ioc::Base::Action{"IOC.Register", "test.command"},
                                std::function([](std::vector<std::any> args) -> std::shared_ptr<otus::ICommand> {
                                    return std::make_shared<otus::Test2Command>();
                                }))
        ->execute();

    // try to resolve "test.command" in scope "test2"
    cmd = ioc.resolve<otus::ICommand>("test.command");
    cmd->execute();

    // check command execution result, must not to be changed
    EXPECT_EQ(otus::Test1Command::getExecuteCount(), 1);
    EXPECT_EQ(otus::Test2Command::getExecuteCount(), 1);

    // set scope "test1" as current
    ioc.resolve<otus::ICommand>(otus::ioc::Base::Action{"Scopes.Current", "test1"})->execute();

    // try to resolve "test.command" in scope "test1"
    cmd = ioc.resolve<otus::ICommand>("test.command");
    cmd->execute();

    // check command execution result, must not to be changed
    EXPECT_EQ(otus::Test1Command::getExecuteCount(), 2);
    EXPECT_EQ(otus::Test2Command::getExecuteCount(), 1);
}

TEST(IOC, MultiThreadingTest)
{
    otus::ioc::Base ioc;
    
    otus::Test1Command::clearExecuteCount();
    otus::Test2Command::clearExecuteCount();

    // create scope "test1"
    ioc.resolve<otus::ICommand>(
        otus::ioc::Base::Action{"Scopes.New",
        "test1"}
    )->execute();

    // create scope "test2"
    ioc.resolve<otus::ICommand>(
        otus::ioc::Base::Action{"Scopes.New",
        "test2"}
    )->execute();

    // create scope "test3"
    ioc.resolve<otus::ICommand>(
        otus::ioc::Base::Action{"Scopes.New",
        "test3"}
    )->execute();

    // set scope "test1" as current
    ioc.resolve<otus::ICommand>(
        otus::ioc::Base::Action{"Scopes.Current",
        "test1"}
    )->execute();

    // register test.command for Test1Command in scope test1
    ioc.resolve<otus::ICommand>(
        otus::ioc::Base::Action{"IOC.Register",
        "test.command"},
        std::function([](std::vector<std::any> args) -> std::shared_ptr<otus::ICommand>
        {
            return std::make_shared<otus::Test1Command>();
        })
    )->execute();

    // set scope "test2" as current
    ioc.resolve<otus::ICommand>(
        otus::ioc::Base::Action{"Scopes.Current",
        "test2"}
    )->execute();

    // register test.command for Test1Command in scope test1
    ioc.resolve<otus::ICommand>(
        otus::ioc::Base::Action{"IOC.Register",
        "test.command"},
        std::function([](std::vector<std::any> args) -> std::shared_ptr<otus::ICommand>
        {
            return std::make_shared<otus::Test2Command>();
        })
    )->execute();

    // set scope "test1" as current
    ioc.resolve<otus::ICommand>(
        otus::ioc::Base::Action{"Scopes.Current",
        "test3"}
    )->execute();

    ioc.resolve<otus::ICommand>("test.command")->execute();
    EXPECT_EQ(otus::Test1Command::getExecuteCount(), 0);
    EXPECT_EQ(otus::Test2Command::getExecuteCount(), 0);

    std::thread t1([&] {
        for (unsigned i = 0; i < 10; i++)
        {
            // set scope "test2" as current
            ioc.resolve<otus::ICommand>(otus::ioc::Base::Action{"Scopes.Current", "test1"})->execute();

            // try to resolve "test.command" in scope "test1"
            ioc.resolve<otus::ICommand>("test.command")->execute();
        }
    });

    std::thread t2([&] {
        for (unsigned i = 0; i < 20; i++)
        {
            // set scope "test2" as current
            ioc.resolve<otus::ICommand>(otus::ioc::Base::Action{"Scopes.Current", "test2"})->execute();

            // try to resolve "test.command" in scope "test1"
            ioc.resolve<otus::ICommand>("test.command")->execute();
        }
    });

    t1.join();
    t2.join();

    EXPECT_EQ(otus::Test1Command::getExecuteCount(), 10);
    EXPECT_EQ(otus::Test2Command::getExecuteCount(), 20);

}
