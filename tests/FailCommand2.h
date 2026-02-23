#pragma once

#include "ICommand.h"

namespace otus
{

template<typename ExceptionType>
class FailCommand2 : public ICommand
{
public:
    virtual ~FailCommand2() = default;

    void execute() override
    {
        m_executeCount++;
        throw ExceptionType("test2");
    }

    unsigned getExecuteCount() const { return m_executeCount; }

private:
    unsigned m_executeCount{0};
};

}  // namespace otus
