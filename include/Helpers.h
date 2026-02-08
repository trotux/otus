#pragma once

#include "ICommand.h"

#include <cstdlib>
#include <cxxabi.h>
#include <string>
#include <typeindex>

namespace otus
{

template<typename T>
static inline const std::type_info& getTypeInfo(T& obj)
{
    return typeid(obj);
}

template<typename T>
static inline std::string getTypeName(T& obj)
{
    std::type_index typeIndex = getTypeInfo(obj);

    std::string name;
    int status{0};
    char* realname = abi::__cxa_demangle(typeIndex.name(), NULL, NULL, &status);
    if (status == 0 && realname != nullptr)
    {
        name = realname;
    }
    else
    {
        name = typeIndex.name();
    }

    if (realname != nullptr)
    {
        std::free(realname);
    }

    return name;
}

inline std::string getTypeName(const std::type_info typeInfo)
{
    std::string name;
    int status{0};
    char* realname = abi::__cxa_demangle(typeInfo.name(), NULL, NULL, &status);
    if (status == 0 && realname != nullptr)
    {
        name = realname;
    }
    else
    {
        name = typeInfo.name();
    }

    if (realname != nullptr)
    {
        std::free(realname);
    }

    return name;
}

template<>
inline std::string getTypeName<ICommand>(ICommand& obj)
{
    const auto& typeInfo = getTypeInfo(obj);
    std::type_index typeIndex = typeInfo;

    std::string name;
    int status{0};
    char* realname = abi::__cxa_demangle(typeIndex.name(), NULL, NULL, &status);
    if (status == 0 && realname != nullptr)
    {
        name = realname;
    }
    else
    {
        name = typeIndex.name();
    }

    if (realname != nullptr)
    {
        std::free(realname);
    }

    return name;
}

template<typename T>
inline std::string getTypeName()
{
    const std::type_info& typeIndex = typeid(T);

    std::string name;
    int status{0};
    char* realname = abi::__cxa_demangle(typeIndex.name(), NULL, NULL, &status);
    if (status == 0 && realname != nullptr)
    {
        name = realname;
    }
    else
    {
        name = typeIndex.name();
    }

    if (realname != nullptr)
    {
        std::free(realname);
    }

    return name;
}

}  // namespace otus
