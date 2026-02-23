#pragma once

#include <exception>
#include <string>

namespace otus
{

class NoVelocityException : public std::exception
{
public:
    virtual ~NoVelocityException() = default;

    NoVelocityException(const char* message)
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
