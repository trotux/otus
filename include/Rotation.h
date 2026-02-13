#pragma once

#include "Error.h"
#include "IRotatableObject.h"
#include "Direction.h"
#include "AngularVelocity.h"


#include <memory>
#include <system_error>

namespace otus
{

class Rotation
{
public:
    Rotation(IRotatableObject& adapter)
        : m_adapter{adapter}
    {}

    std::error_code execute()
    {
        auto currentDirection = m_adapter.getDirection();
        auto currentVelocity = m_adapter.getAngularVelocity();

        if (currentDirection == nullptr)
        {
            return MoveErrc::NoDirection;
        }

        if (currentVelocity == nullptr)
        {
            return MoveErrc::NoAngularVelocity;
        }

        if (currentVelocity->getValue() == 0)
        {
            return MoveErrc::NoRotatable;
        }

        auto newDirection = std::make_shared<Direction>(currentDirection->getValue() + currentVelocity->getValue()); 

        m_adapter.setDirection(newDirection);

        return MoveErrc::Ok;
    }

private:
    IRotatableObject& m_adapter;
};

}  // namespace otus
