#pragma once

#include "IProperty.h"

#include <memory>
#include <unordered_map>

namespace otus
{

template<class...>
struct always_false_v : std::bool_constant<false>
{};

class UObject
{
public:
    template<typename T>
    std::shared_ptr<T> getProperty(const std::string& name) const
    {
        if (auto it = m_propertyMap.find(name); it != m_propertyMap.end())
        {
            return std::static_pointer_cast<T>(it->second);
        }

        return nullptr;
    }

    template<typename T>
    void setProperty(const std::string& name, std::shared_ptr<T> property)
    {
        m_propertyMap[name] = property;
    }

    void resetProperty(const std::string& name)
    {
        m_propertyMap[name] = nullptr;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<IProperty>> m_propertyMap;
};

}  // namespace otus
