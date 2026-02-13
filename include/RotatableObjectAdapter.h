#pragma once

#include "IRotatableObject.h"

#include "Direction.h"
#include "Magnitude.h"
#include "UObject.h"
#include "Velocity.h"

#include <memory>
#include <stdexcept>

namespace otus
{

class RotatableObjectAdapter : public IRotatableObject
{
public:
    RotatableObjectAdapter() = delete;
    RotatableObjectAdapter(std::shared_ptr<UObject> object)
        : m_object{object}
    {
        if (m_object == nullptr)
        {
            throw std::runtime_error("IRotatableObject must be not nullptr");
        }
    }

    void setVelocity(std::shared_ptr<Velocity> velocity) override
    {
        m_object->setProperty<Velocity>("velocity", velocity);
    }

    std::shared_ptr<Velocity> getVelocity() override { return m_object->getProperty<Velocity>("velocity"); }

    std::shared_ptr<Direction> getDirection() override { return m_object->getProperty<Direction>("direction"); }

    void setDirection(std::shared_ptr<Direction> direction) override
    {
        m_object->setProperty<Direction>("direction", direction);
    }

    std::shared_ptr<Magnitude> getMagnitude() override { return m_object->getProperty<Magnitude>("magnitude"); }

private:
    std::shared_ptr<UObject> m_object;
};

}  // namespace otus
