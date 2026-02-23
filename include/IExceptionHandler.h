#pragma once

#include "ICommand.h"

#include <exception>
#include <memory>

namespace otus
{

class IExceptionHandler
{
public:
    virtual ~IExceptionHandler() {}
    virtual void handle(std::shared_ptr<ICommand> cmd, std::exception& exception) = 0;
};

}  // namespace otus
