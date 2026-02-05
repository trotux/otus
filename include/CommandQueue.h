#pragma once

#include "ICommand.h"

#include <queue>
#include <memory>

namespace otus {

class CommandQueue
{
public:
    void push(std::shared_ptr<ICommand> cmd);
    std::shared_ptr<ICommand> pop();

private:
    std::queue<std::shared_ptr<ICommand>> m_queue;
};

} // namespace otus
