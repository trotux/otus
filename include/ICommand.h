#pragma once

namespace otus
{

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
};

}  // namespace otus
