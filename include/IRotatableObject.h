#pragma once

#include "AngularVelocity.h"
#include "Direction.h"
#include "Magnitude.h"
#include "Velocity.h"

#include <memory>

namespace otus
{

class IRotatableObject
{
public:
    virtual ~IRotatableObject() = default;
    virtual std::shared_ptr<Direction> getDirection() = 0;
    virtual void setDirection(std::shared_ptr<Direction>) = 0;
    virtual void setVelocity(std::shared_ptr<Velocity>) = 0;
    virtual std::shared_ptr<Velocity> getVelocity() = 0;
    virtual std::shared_ptr<Magnitude> getMagnitude() = 0;
    virtual std::shared_ptr<AngularVelocity> getAngularVelocity() = 0;
};

}  // namespace otus
