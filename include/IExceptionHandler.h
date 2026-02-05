#pragma once

#include "ICommand.h"
#include "CommandQueue.h"

#include <exception>
#include <memory>

namespace otus {

class IExceptionHandler
{
public:
  virtual ~IExceptionHandler() {}
  virtual void handle(CommandQueue& queue, std::shared_ptr<ICommand> cmd, std::exception& e) = 0;
};

} // namespace otus
