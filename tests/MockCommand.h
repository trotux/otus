#pragma once

#include "ICommand.h"

namespace otus
{

class MockCommand : public ICommand
{
public:
    virtual ~MockCommand() = default;

    std::string name() override
    {
        return "mock";
    }

    void execute() override { m_executeCount++; }

    unsigned getExecuteCount() const { return m_executeCount; }

private:
    unsigned m_executeCount{0};
};

}  // namespace otus
