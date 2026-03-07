#include "ICommand.h"
#include "EmptyCommand.h"
#include "MoveCommand.h"
#include "LogExceptionHandler.h"

#include "IoC.h"
#include "UObject.h"
#include "MovableObjectAdapter.h"
#include "Velocity.h"

#include <gtest/gtest.h>

#include <functional>
#include <memory>
#include <print>

TEST(IOC, Base)
{
    std::shared_ptr<otus::UObject> obj = std::make_shared<otus::UObject>();

    otus::IoC ioc;

    otus::Binder<int, std::string>().call(
        [](int a, std::string s)
        {
            std::print(stderr, "int: {}\n string: {}\n", a, s);
            return 0;
        },
        {5, std::string("Hello, Delegates!")});

    //    auto cmd = otus::Builder<otus::EmptyCommand, otus::UObject>{};
    

    //std::function<std::shared_ptr<otus::ICommand>(std::shared_ptr<otus::UObject> obj)> func = lambda;

    //ioc.Register("move.command", lambda);

    ioc.Resolve<otus::ICommand>(
        "IOC.Register",
        "move.command",
        [](std::shared_ptr<otus::UObject> obj) -> std::shared_ptr<otus::ICommand>
        {
            std::print(stderr, ">>>>>> {}\n", __PRETTY_FUNCTION__);
            std::shared_ptr<otus::MovableObjectAdapter> moveAdapter = std::make_shared<otus::MovableObjectAdapter>(obj);
            return std::make_unique<otus::MoveCommand>(moveAdapter);
        }
    )->execute();

    auto cmd = ioc.Resolve<otus::ICommand>("move.command", obj);

    std::shared_ptr<otus::Velocity> velocity;
    ioc.Resolve<otus::ICommand>("Spaceship.Operations.IMovable:position.set", obj, velocity)->execute();

#if 0
    auto builder = std::make_unique<otus::Builder<otus::EmptyCommand>>();
    std::print(stderr, "type: {}\n", typeid(builder).name());


    std::shared_ptr<otus::ICommand> cmd = builder->build<otus::ICommand>();

    std::print(stderr, "type: {}\n", typeid(cmd.get() ).name());

    auto variadic_generic_lambda = [] (auto... param)
    {
        return std::make_unique<otus::EmptyCommand>(param...);
    };

    std::function<std::shared_ptr<otus::ICommand>()> func = variadic_generic_lambda;
    std::print(stderr, "type: {}\n", typeid(func).name());

    auto cmd2 = func();
#endif
}

