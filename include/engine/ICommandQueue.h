#pragma once

#include "ICommand.h"

#include <memory>

namespace otus::engine
{

class ICommandQueue
{
public:
    virtual void push(std::shared_ptr<ICommand> cmd) = 0;
    virtual std::shared_ptr<ICommand> pop() = 0;
    virtual bool empty() = 0;
    virtual bool size() = 0;
};

}  // namespace otus::engine

