#pragma once

#include "Point.h"
#include "Velocity.h"

#include <memory>

namespace otus
{

class IMovableObject
{
public:
    virtual ~IMovableObject() = default;
    virtual std::shared_ptr<Point> getPosition() = 0;
    virtual void setPosition(std::shared_ptr<Point>) = 0;
    virtual std::shared_ptr<Velocity> getVelocity() = 0;
};

}  // namespace otus
