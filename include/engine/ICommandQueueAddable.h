#pragma once

#include "ICommand.h"

#include <memory>

namespace otus::engine
{

class ICommandQueueAddable
{
public:
    virtual void add(std::shared_ptr<ICommand> cmd) = 0;
};

}  // namespace otus::engine

