#pragma once

#include <stdexcept>

namespace otus
{

class FuelTank
{
public:
    FuelTank() = delete;
    FuelTank(int level)
        : m_level{level}
    {}

    int getLevel() const
    {
        return m_level;
    }

    void decreaseLevel(int delta) 
    {
        if (m_level < delta)
        {
            throw std::runtime_error("not enough fuel");
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
