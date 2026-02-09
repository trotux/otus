#pragma once

#include "ICommand.h"
#include "FuelTank.h"
#include "NotEnoughFuelException.h"

#include <memory>
#include <stdexcept>

namespace otus
{

class CheckFuelCommand : public ICommand
{
public:
    CheckFuelCommand() = delete;
    CheckFuelCommand(std::shared_ptr<FuelTank> tank, int delta)
        : m_tank{tank}
        , m_delta{delta}
    {
        if (m_tank == nullptr)
        {
            throw std::runtime_error("fuel tank does not exist");
        }

        if (m_delta <= 0)
        {
            throw std::runtime_error("value of delta must positive integer");
        }
    }

    virtual ~CheckFuelCommand() = default;

    void execute() override
    {
        int level = m_tank->getLevel();
        if (level < m_delta)
        {
            throw NotEnoughtFuelException("not enough fuel");
        }
    }

private:
    std::shared_ptr<FuelTank> m_tank;
    int m_delta;
};

}  // namespace otus
