#pragma once

#include "IMovableObject.h"
#include "Point.h"
#include "UObject.h"
#include "Velocity.h"

#include <memory>
#include <stdexcept>

namespace otus
{

class MovableObjectAdapter : public IMovableObject
{
public:
    MovableObjectAdapter() = delete;
    MovableObjectAdapter(std::shared_ptr<UObject> object)
        : m_object{object}
    {
        if (m_object == nullptr)
        {
            throw std::runtime_error("IMovableObject must be not nullptr");
        }
    }

    std::shared_ptr<Point> getPosition() override
    {
        if (m_object == nullptr)
        {
            return nullptr;
        }

        return m_object->getProperty<Point>("position");
    }

    void setPosition(std::shared_ptr<Point> position) override
    {
        if (m_object != nullptr)
        {
            m_object->setProperty<Point>("position", position);
        }
    }

    std::shared_ptr<Velocity> getVelocity() override
    {
        if (m_object == nullptr)
        {
            return nullptr;
        }

        return m_object->getProperty<Velocity>("velocity");
    }

private:
    std::shared_ptr<UObject> m_object;
};

}
