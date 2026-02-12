#pragma once

#include "IProperty.h"

namespace otus
{

class Velocity : public IProperty
{
public:
    Velocity() = default;
    Velocity(int deltaX, int deltaY)
        : m_deltaX{deltaX}
        , m_deltaY{deltaY}
    {}

    std::string name() override { return "linear velocity"; }

    int getDeltaX() { return m_deltaX; }
    int getDeltaY() { return m_deltaY; }

private:
    int m_deltaX{0};
    int m_deltaY{0};
};

}  // namespace otus
