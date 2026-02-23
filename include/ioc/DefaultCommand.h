#pragma once

#include "ICommand.h"

#include <functional>

namespace otus::ioc
{

struct DefaultCommand : public ICommand
{
public:
    DefaultCommand(std::function<void()>&& func)
        : m_func{std::move(func)}
    {}

    void execute() override
    {
        if (m_func)
        {
            m_func();
        }
    }

private:
    std::function<void()> m_func;
};

}  // namespace otus::ioc

