#pragma once

#include "ICommand.h"

#include <queue>
#include <memory>

namespace otus
{

class CommandQueue
{
public:
    void push(std::shared_ptr<ICommand> cmd);
    std::shared_ptr<ICommand> pop();
    bool empty() { return m_queue.empty(); }
    bool size() { return m_queue.size(); }

private:
    std::queue<std::shared_ptr<ICommand>> m_queue;
};

}  // namespace otus
