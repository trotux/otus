#pragma once

#include "ICommand.h"
#include "IMovableObject.h"
#include "Point.h"
#include "NoLocationException.h"
#include "NoVelocityException.h"
#include "NonMovableException.h"

#include <memory>

namespace otus
{

class MoveCommand : public ICommand
{
public:
    MoveCommand(std::shared_ptr<IMovableObject> adapter)
        : m_adapter{adapter}
    {}

    void execute() override
    {
        auto currentPosition = m_adapter->getPosition();
        auto currentVelocity = m_adapter->getVelocity();

        if (currentPosition == nullptr)
        {
            throw NoLocationException("object does not have location");
        }

        if (currentVelocity == nullptr)
        {
            throw NoVelocityException("object does not have velocity");
        }

        if (currentVelocity->getDeltaX() == 0 && currentVelocity->getDeltaY() == 0)
        {
            throw NonMovableException("object can not be moved");
        }

        auto newPosition = std::make_shared<Point>(
                currentPosition->getX() + currentVelocity->getDeltaX(),
                currentPosition->getY() + currentVelocity->getDeltaY());

        m_adapter->setPosition(newPosition);
    }

private:
    std::shared_ptr<IMovableObject> m_adapter;
};

}
