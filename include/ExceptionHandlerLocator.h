#pragma once

#include "IExceptionHandler.h"
#include "ExceptionHandlerKey.h"

#include <memory>
#include <typeindex>
#include <unordered_map>

namespace otus
{

class ExceptionHandlerLocator
{
public:
    template<typename ExceptionType, typename CommandType>
    void registerHandler(std::shared_ptr<IExceptionHandler> handler)
    {
        ExceptionHandlerKey key = ExceptionHandlerKey::create<ExceptionType, CommandType>();

        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_handlers.contains(key))
        {
            throw std::runtime_error("handler already registered");
        }
        m_handlers[key] = handler;
    }

    template<typename ExceptionType, typename CommandType>
    void unregisterHandler()
    {
        ExceptionHandlerKey key = ExceptionHandlerKey::create<ExceptionType, CommandType>();

        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_handlers.contains(key))
        {
            m_handlers.erase(key);
        }
    }

    std::shared_ptr<IExceptionHandler> getHandler(std::type_index exceptionTypeIndex,
                                                  std::type_index cmdTypeIndex) const
    {

        ExceptionHandlerKey key{exceptionTypeIndex.hash_code(), cmdTypeIndex.hash_code()};

        std::lock_guard<std::mutex> lock(m_mutex);
        if (auto it = m_handlers.find(key); it != m_handlers.end())
        {
            return it->second;
        }

        return nullptr;
    }

private:
    std::unordered_map<ExceptionHandlerKey, std::shared_ptr<IExceptionHandler>> m_handlers;
    mutable std::mutex m_mutex;
};

}  // namespace otus
