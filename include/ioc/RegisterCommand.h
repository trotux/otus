#pragma once

#include "ICommand.h"

#include <any>
#include <functional>
#include <memory>
#include <string>

namespace otus::ioc
{

struct RegisterCommand : public ICommand
{
    using Function = std::function<std::shared_ptr<ICommand>(std::vector<std::any>)>;
    using FunctionMap = std::unordered_map<std::string, Function>;

    RegisterCommand(FunctionMap& map, const std::string& path, Function&& func)
        : m_map(map)
        , m_path{path}
        , m_func{std::move(func)}
    {}

    static std::shared_ptr<RegisterCommand> make(FunctionMap& map, const std::string& path, Function&& func)
    {
        return std::make_shared<RegisterCommand>(map, path, std::move(func));
    }

    void execute() override { m_map.emplace(m_path, m_func); }

    std::string m_path;
    FunctionMap& m_map;
    Function m_func;
};

}  // namespace otus::ioc

