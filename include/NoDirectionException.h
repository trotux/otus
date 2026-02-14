#pragma once

#include <exception>
#include <string>

namespace otus
{

class NoDirectionException : public std::exception
{
public:
    virtual ~NoDirectionException() = default;

    NoDirectionException(const char* message)
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
