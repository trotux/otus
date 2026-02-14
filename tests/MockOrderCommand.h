#pragma once

#include "ICommand.h"
#include "BaseException.h"

namespace otus
{

class MockOrderCommand : public ICommand
{
public:
    MockOrderCommand() = delete;

    MockOrderCommand(unsigned order)
        : m_order{order}
    {}

    virtual ~MockOrderCommand() = default;

    void execute() override
    { 
        if (m_order != ++g_counter)
        {
            throw BaseException("wrong command order");
        }
    }

    void clearCounter() { g_counter = 0; }

private:
    static inline unsigned g_counter{0};
    unsigned m_order{0};
};

}  // namespace otus
