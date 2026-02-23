#pragma once

#include "ICommand.h"
#include "IRotatableObject.h"
#include "NoLocationException.h"
#include "NoDirectionException.h"
#include "NoVelocityException.h"
#include "NoMagnitudeException.h"
#include "NonMovableException.h"
#include "Velocity.h"

#include <memory>
#include <cmath>

namespace otus
{

class ChangeVelocityCommand : public ICommand
{
public:
    ChangeVelocityCommand(std::shared_ptr<IRotatableObject> adapter)
        : m_adapter{adapter}
    {}

    void execute() override
    {
        auto direction = m_adapter->getDirection();
        auto magnitude = m_adapter->getMagnitude();
        auto velocity = m_adapter->getVelocity();

        if (direction == nullptr)
        {
            throw NoDirectionException("object does not have direction");
        }

        if (magnitude == nullptr)
        {
            throw NoMagnitudeException("object does not have magnitude");
        }

        auto magValue = magnitude->getValue();

        if (magValue == 0)
        {
            throw NonMovableException("object can not be moved");
        }

        auto deltaY = magnitude->getValue() * sinFromDegree(direction->getValueInDegree());
        auto deltaX = magnitude->getValue() * cosFromDegree(direction->getValueInDegree());

        m_adapter->setVelocity(std::make_shared<Velocity>(deltaX, deltaY));
    }

private:
    static double degree2rad(double d) { return (d / 180.0) * (static_cast<double>(M_PI)); }

    static double sinFromDegree(double x)
    {
        if (!std::isfinite(x))
        {
            return sin(x);
        }

        if (x < 0.0)
        {
            return -sinFromDegree(-x);
        }

        int quo{0};
        double x90 = std::remquo(fabs(x), 90.0, &quo);

        switch (quo % 4)
        {
            case 0:
                return sin(degree2rad(x90) * 1.0);

            case 1:
                return cos(degree2rad(x90) * 1.0);

            case 2:
                return sin(degree2rad(-x90) * 1.0);

            case 3:
                return -cos(degree2rad(x90));
        }

        return 0.0;
    }

    static double cosFromDegree(double x)
    {
        if (!std::isfinite(x))
        {
            return cos(x);
        }

        if (x < 0.0)
        {
            return -cosFromDegree(-x);
        }

        int quo{0};
        double x90 = std::remquo(fabs(x), 90.0, &quo);

        switch (quo % 4)
        {
            case 0:
                return cos(degree2rad(x90) * 1.0);

            case 1:
                return sin(degree2rad(x90) * 1.0);

            case 2:
                return -cos(degree2rad(-x90) * 1.0);

            case 3:
                return sin(degree2rad(x90));
        }

        return 0.0;
    }


    std::shared_ptr<IRotatableObject> m_adapter;
};

}  // namespace otus

