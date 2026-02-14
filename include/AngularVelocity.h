#pragma once

#include "IProperty.h"

namespace otus
{

class AngularVelocity : public IProperty
{
public:
    AngularVelocity() = default;
    AngularVelocity(int value)
        : m_value{value}
    {}

    std::string name() override { return "angular velocity"; }

    int getValue() { return m_value; }

private:
    int m_value{0};
};

}
