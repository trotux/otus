#pragma once

#include "IProperty.h"

namespace otus
{

class Magnitude : public IProperty
{
public:
    Magnitude() = default;
    Magnitude(int value)
        : m_value{value}
    {}

    std::string name() override { return "magnitude"; }

    int getValue() { return m_value; }

private:
    int m_value{0};
};

}  // namespace otus
