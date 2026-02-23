#pragma once

#include "ICommand.h"

namespace otus
{

class Test1Command : public ICommand
{
public:
    virtual ~Test1Command() = default;

    void execute() override
    {
        g_executeCount++;
    }

    static unsigned getExecuteCount() { return g_executeCount; }
    static void clearExecuteCount() { g_executeCount = 0; }

private:
    static inline unsigned g_executeCount{0};
};

}  // namespace otus
