#pragma once

#include <string>

namespace otus {

class ICommand
{
public:
  virtual ~ICommand() = default;
  virtual void execute() = 0;
  virtual std::string name() = 0;
};

} // namespace otus
