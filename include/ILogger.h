#pragma once

#include <string>

namespace otus {

class ILogger
{
public:
  virtual ~ILogger() = default;
  virtual void write(const std::string& message) = 0;
};

} // namespace otus
