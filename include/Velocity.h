#pragma once

#include "IProperty.h"

namespace otus
{

class Velocity : public IProperty
{
public:
    Velocity() = default;
    Velocity(double deltaX, double deltaY)
        : m_deltaX{deltaX}
        , m_deltaY{deltaY}
    {}

    std::string name() override { return "linear velocity"; }

    double getDeltaX() { return m_deltaX; }
    double getDeltaY() { return m_deltaY; }

private:
    double m_deltaX{0};
    double m_deltaY{0};
};

}  // namespace otus
