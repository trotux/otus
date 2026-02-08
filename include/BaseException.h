#pragma once

#include <exception>
#include <string>

namespace otus
{

class BaseException : public std::exception
{
public:
    virtual ~BaseException() = default;

    BaseException(const char* message)
        : m_message(message)
    {}

    const char* what() const noexcept { return m_message.c_str(); }

private:
    std::string m_message;
};

}  // namespace otus
