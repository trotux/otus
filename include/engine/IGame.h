#pragma once

#include <nlohmann/json.hpp>

namespace otus::engine
{

class IGame
{
public:
    virtual std::string getName() = 0;
    virtual void addOperation(const nlohmann::json& operation) = 0;
};

}  // namespace otus::engine
