#include "EmptyCommand.h"
#include "ioc/Scope.h"
#include "ioc/DefaultCommand.h"

#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <string>

namespace otus::ioc
{

class Base
{
public:
    Base() = default;

    template<typename T, typename... Args>
    std::shared_ptr<T> resolve(const std::string& key, Args&&... args)
    {
        std::shared_ptr<T> cmd = checkForAction<T>(key, std::forward<Args>(args)...);
        if (cmd != nullptr)
        {
            return cmd;
        }

        std::shared_ptr<IScope> scope = g_currentScope ? g_currentScope : m_defaultScope;
        if (scope != nullptr)
        {
            auto impl = std::dynamic_pointer_cast<Scope<T>>(scope);
            return impl->resolve(key, std::forward<Args>(args)...);
        }

        return std::make_shared<EmptyCommand>();
    }

    template<typename T>
    std::shared_ptr<T> resolve(const std::string& key)
    {
        std::shared_ptr<IScope> scope = g_currentScope ? g_currentScope : m_defaultScope;
        if (scope != nullptr)
        {
            auto impl = std::dynamic_pointer_cast<Scope<T>>(scope);
            return impl->resolve(key);
        }

        return std::make_shared<EmptyCommand>();
    }

private:
    template <typename First, typename... Rest>
    static std::optional<std::string> getFirstArg(First firstArg, Rest... restArgs)
    {
        if constexpr (std::is_convertible_v<First, std::string>)
        {
            return std::string(firstArg);
        }

        return std::nullopt;
    }

    template<typename T>
    void addNewScope(const std::string& name)
    {
        std::unique_lock<std::mutex> lock_guard(m_mutex);
        auto scope = std::make_shared<Scope<T>>(name);
        m_scopes.emplace(name, scope);
    }

    void setCurrentScope(const std::string& name)
    {
        std::unique_lock<std::mutex> lock_guard(m_mutex);
        if (m_scopes.contains(name))
        {
            g_currentScope = m_scopes[name];
        }
    }

    void setDefaultScope(const std::string& name)
    {
        std::unique_lock<std::mutex> lock_guard(m_mutex);
        if (m_scopes.contains(name))
        {
            m_defaultScope = m_scopes[name];
        }
    }

    template<typename T, typename... Args>
    std::shared_ptr<T> checkForAction(const std::string& key, Args&&... args)
    {
        std::function<void()> command;

        if (key == "Scopes.New")
        {
            auto key2 = getFirstArg(std::forward<Args>(args)...);
            if (key2.has_value())
            {
                auto cmd = [&, name=key2.value()] {
                    addNewScope<T>(name);
                };

                return std::make_shared<DefaultCommand>(cmd);
            }
        }
        else if (key == "Scopes.Current")
        {
            auto key2 = getFirstArg(std::forward<Args>(args)...);
            if (key2.has_value())
            {
                auto cmd = [&, name=key2.value()] {
                    setCurrentScope(name);
                };

                return std::make_shared<DefaultCommand>(cmd);
            }
        }
        else if (key == "Scopes.Default")
        {
            auto key2 = getFirstArg(std::forward<Args>(args)...);
            if (key2.has_value())
            {
                auto cmd = [&, name=key2.value()] {
                    setDefaultScope(name);
                };

                return std::make_shared<DefaultCommand>(cmd);
            }
        }

        return nullptr;
    }

    static inline thread_local std::shared_ptr<IScope> g_currentScope;

    std::mutex m_mutex;
    std::shared_ptr<IScope> m_defaultScope;
    std::unordered_map<std::string, std::shared_ptr<IScope>> m_scopes;
};

}  // namespace otus::ioc
