#pragma once

#include <exception>
#include <string>

namespace otus
{

class BaseException : public std::exception
{
public:
    virtual ~BaseException() = default;

    // Constructor accepting const char*
    BaseException(const char* message)
        : m_message(message)
    {}

    // Override what() method, marked
    // noexcept for modern C++
    const char* what() const noexcept
    {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

}  // namespace otus
