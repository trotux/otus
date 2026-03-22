#pragma once

#include "EmptyCommand.h"
#include "ioc/RegisterCommand.h"

#include <any>
#include <functional>
#include <memory>

namespace otus::ioc
{

class IScope
{
public:
    virtual std::string name() = 0;
};

template<typename T>
class Scope : public IScope
{
public:
    Scope() = delete;
    explicit Scope(const std::string& name)
        : m_name{name}
    {}

    using Function = std::function<std::shared_ptr<T>(std::vector<std::any>)>;
    using FunctionMap = std::unordered_map<std::string, Function>;

    std::string name() override { return m_name; }

    template<typename... Args>
    std::shared_ptr<T> resolve(const std::string& key, Args&&... args)
    {
        if (key == "IOC.Register")
        {
            return emplace(std::forward<Args>(args)...);
        }

        return get(key, std::forward<Args>(args)...);
    }

    template<typename... Args>
    std::shared_ptr<T> get(std::string key, Args&&... args)
    {
        if (m_map.contains(key))
        {
            std::vector<std::any> params = {std::any{std::forward<Args>(args)}...};
            return std::invoke(m_map[key], params);
        }

        return std::make_shared<EmptyCommand>();
    }

    template<typename... Args>
    std::shared_ptr<T> emplace(Args&&... args)
    {
        return std::make_shared<EmptyCommand>();
    }

    template<typename Path=std::string, typename FunctionType>
    std::shared_ptr<T> emplace(Path&& path, FunctionType&& func)
    {
        return RegisterCommand::make(m_map, path, std::move(func));
    }

private:
    std::string m_name;
    FunctionMap m_map;
};

}  // namespace otus::ioc
