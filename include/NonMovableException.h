#pragma once

#include <exception>
#include <string>

namespace otus
{

class NonMovableException : public std::exception
{
public:
    virtual ~NonMovableException() = default;

    NonMovableException(const char* message)
        : m_message(message)
    {}

    const char* what() const noexcept
    {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

}  // namespace otus
