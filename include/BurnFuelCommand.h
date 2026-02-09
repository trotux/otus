#pragma once

#include "ICommand.h"
#include "FuelTank.h"
#include "NotEnoughFuelException.h"

#include <memory>
#include <stdexcept>

namespace otus
{

class BurnFuelCommand : public ICommand
{
public:
    BurnFuelCommand() = delete;
    BurnFuelCommand(std::shared_ptr<FuelTank> tank, int delta)
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

    virtual ~BurnFuelCommand() = default;

    void execute() override
    {
        m_tank->decreaseLevel(m_delta);
    }

private:
    std::shared_ptr<FuelTank> m_tank;
    int m_delta;
};

}  // namespace otus
