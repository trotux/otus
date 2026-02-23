#pragma once

#include "ICommand.h"
#include <memory>

namespace otus
{

class ICommandWrapper
{
public:
    virtual ~ICommandWrapper() = default;
    virtual std::shared_ptr<ICommand> getCommand() const = 0;
};

}  // namespace otus
