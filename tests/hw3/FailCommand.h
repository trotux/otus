#pragma once

#include "ICommand.h"

namespace otus
{

template<typename ExceptionType>
class FailCommand : public ICommand
{
public:
    virtual ~FailCommand() = default;

    void execute() override
    {
        m_executeCount++;
        throw ExceptionType("test");
    }

    unsigned getExecuteCount() const { return m_executeCount; }

private:
    unsigned m_executeCount{0};
};

}  // namespace otus
