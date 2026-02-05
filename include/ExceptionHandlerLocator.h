#pragma once

#include "IExceptionHandler.h"

#include <exception>
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace otus
{

class ExceptionHandlerLocator
{
public:
    template<typename ExceptionType>
    void registerHandler(std::shared_ptr<IExceptionHandler> handler)
    {
        static_assert(std::is_base_of<std::exception, ExceptionType>::value, "exception must inherit from std::exception");
        std::lock_guard<std::mutex> lock(m_mutex);
        std::type_index typeIndex = std::type_index(typeid(ExceptionType));
        if (m_handlers.contains(typeIndex))
        {
            throw std::runtime_error("handler already registered");
        }
        m_handlers[typeIndex] = handler;
    }

    template<typename T>
    void unregisterHandler()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::type_index typeIndex = std::type_index(typeid(T));
        if (m_handlers.contains(typeIndex))
        {
            m_handlers.erase(typeIndex);
        }
    }

    std::shared_ptr<IExceptionHandler> getHandler(std::type_index index) const
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (auto it = m_handlers.find(index); it != m_handlers.end())
        {
            return it->second;
        }

        return nullptr;
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<IExceptionHandler>> m_handlers;
    mutable std::mutex m_mutex;
};

}
