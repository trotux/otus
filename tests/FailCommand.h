#pragma once

#include "ICommand.h"
#include "TestException.h"

namespace otus
{

class FailCommand : public ICommand
{
public:
    virtual ~FailCommand() = default;

    std::string name() override
    {
        return "fail";
    }

    void execute() override
    {
        m_executeCount++;
        throw TestException("test exception");
    }

    unsigned getExecuteCount() const { return m_executeCount; }

private:
    unsigned m_executeCount{0};
};

}  // namespace otus
