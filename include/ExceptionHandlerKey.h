#pragma once

#include "ICommand.h"

#include <typeindex>
#include <cstddef>

namespace otus
{

struct ExceptionHandlerKey
{
    size_t exceptionKey{0};
    size_t commandKey{0};

    template<typename ExceptionType, typename CommandType>
    static ExceptionHandlerKey create()
    {
        static_assert(std::is_base_of<std::exception, ExceptionType>::value,
                      "exception must inherit from std::exception");
        static_assert(std::is_base_of<ICommand, CommandType>::value, "command must inherit from ICommand");

        std::type_index exceptionTypeIndex = typeid(ExceptionType);
        std::type_index cmdTypeIndex = typeid(CommandType);
        return {exceptionTypeIndex.hash_code(), cmdTypeIndex.hash_code()};
    }
};

static inline bool operator==(const ExceptionHandlerKey& a, const ExceptionHandlerKey& b)
{
    return (a.commandKey == b.commandKey && a.exceptionKey == b.exceptionKey);
}

}  // namespace otus

namespace std
{

template<typename T>
inline void hash_combine(std::size_t& seed, const T& val)
{
    std::hash<T> hasher;

    seed ^= hasher(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<>
struct hash<otus::ExceptionHandlerKey>
{
    inline std::size_t operator()(const otus::ExceptionHandlerKey& key) const
    {
        std::size_t seed = 0xdeadbeaf;
        hash_combine(seed, key.exceptionKey);
        hash_combine(seed, key.commandKey);

        return seed;
    }
};

}  // namespace std
