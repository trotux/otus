#pragma once

#include "NotEnoughFuelException.h"

namespace otus
{

class FuelTank
{
public:
    FuelTank() = delete;
    FuelTank(int level)
        : m_level{level}
    {}

    bool empty() const
    {
        return m_level == 0;
    }

    int getLevel() const
    {
        return m_level;
    }

    void decreaseLevel(int delta) 
    {
        if (m_level < delta)
        {
            throw NotEnoughtFuelException("not enough fuel");
        }

        m_level -= delta;
    }

    void increaseLevel(int delta) 
    {
        m_level += delta; // assume infinite size
    }

private:
    int m_level{0};
};

}  // namespace otus
