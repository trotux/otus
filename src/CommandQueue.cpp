#include "CommandQueue.h"

namespace otus
{

 std::shared_ptr<ICommand> CommandQueue::pop()
{
    if (m_queue.empty())
    {
        return nullptr;
    }

    auto cmd = m_queue.front();
    m_queue.pop();

    return cmd;
}

void CommandQueue::push(std::shared_ptr<ICommand> cmd)
{
    m_queue.push(cmd);
}

}  // namespace otus

