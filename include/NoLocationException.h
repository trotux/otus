#pragma once

#include <exception>
#include <string>

namespace otus
{

class NoLocationException : public std::exception
{
public:
    virtual ~NoLocationException() = default;

    NoLocationException(const char* message)
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
