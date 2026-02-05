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

    void execute() override { throw TestException("test exception"); }
};

}  // namespace otus
