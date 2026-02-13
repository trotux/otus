#pragma once

#include "IProperty.h"

namespace otus
{

class Point : public IProperty
{
public:
    Point() = default;
    Point(double x = 0, double y = 0)
        : m_x{x}
        , m_y{y}
    {}

    std::string name() override { return "position"; }

    double getX() { return m_x; }
    double getY() { return m_y; }

private:
    double m_x{0};
    double m_y{0};
};

}  // namespace otus
