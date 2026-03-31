#pragma once

#include <cstdint>
#include "ICommand.h"

namespace otus::tests
{

class TestMoveCommand : public ICommand
{
public:
    TestMoveCommand() = default;
    void execute() override { numberOfCall++; }

    static inline uint32_t numberOfCall = 0;
};

}  // namespace otus::tests
