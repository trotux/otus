#pragma once

#include "ICommand.h"

namespace otus
{

class EmptyCommand : public ICommand
{
public:
    EmptyCommand() = default;

    virtual ~EmptyCommand() = default;

    void execute() override {}
};

}  // namespace otus
