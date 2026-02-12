#pragma once

#include "IProperty.h"

namespace otus
{

class Point : public IProperty
{
public:
    Point() = default;
    Point(int x = 0, int y = 0)
        : m_x{x}
        , m_y{y}
    {}

    std::string name() override { return "position"; }

    int getX() { return m_x; }
    int getY() { return m_y; }

private:
    int m_x{0};
    int m_y{0};
};

}
