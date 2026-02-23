#pragma once

#include <cstdint>
#include "IProperty.h"

namespace otus
{

class Direction : public IProperty
{
public:
    Direction() = default;
    Direction(unsigned value)
        : m_value{value}
    {
        if (m_value >= rotateStepMax)
        {
            m_value = m_value % rotateStepMax;
        }
    }

    std::string name() override { return "direction"; }

    int getValueInSteps() { return m_value; }
    double getValueInDegree() { return (double)m_value * rotateStepValue; }
    int getRotateStepValue() { return rotateStepValue; }

private:
    static constexpr unsigned rotateStepMax = 360;
    static constexpr unsigned rotateStepValue = 360 / rotateStepMax;

    unsigned m_value{0};
};

}  // namespace otus
