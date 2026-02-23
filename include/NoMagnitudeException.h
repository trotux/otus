#pragma once

#include <exception>
#include <string>

namespace otus
{

class NoMagnitudeException : public std::exception
{
public:
    virtual ~NoMagnitudeException() = default;

    NoMagnitudeException(const char* message)
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
