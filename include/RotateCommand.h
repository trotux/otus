#pragma once

#include "ICommand.h"
#include "IRotatableObject.h"
#include "NoDirectionException.h"
#include "NoAngularVelocityException.h"
#include "NonRotatableException.h"

#include <memory>

namespace otus
{

class RotateCommand : public ICommand
{
public:
    RotateCommand(std::shared_ptr<IRotatableObject> adapter)
        : m_adapter{adapter}
    {}
    RotateCommand() = delete;

    void execute()
    {
        auto direction = m_adapter->getDirection();
        auto aVelocity = m_adapter->getAngularVelocity();

        if (direction == nullptr)
        {
            throw NoDirectionException("object does not have direction");
        }

        if (aVelocity == nullptr)
        {
            throw NoAngularVelocityException("object does not have angular velocity");
        }

        if (aVelocity->getValue() == 0)
        {
            throw NonRotatableException("object can not be rotated");
        }

        direction = std::make_shared<Direction>(direction->getValueInDegree() + aVelocity->getValue());

        m_adapter->setDirection(direction);
    }

private:
    std::shared_ptr<IRotatableObject> m_adapter;
};

}  // namespace otus
