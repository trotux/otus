#include "CommandQueueProcessor.h"

namespace otus
{

void CommandQueueProcessor::process()
{
    auto cmd = m_queue.pop();
    if (cmd == nullptr)
    {
        return;
    }

    try
    {
        cmd->execute();
    }
    catch (std::exception& e)
    {
        m_dispatcher.dispatch(cmd, e);
    }
}

}  // namespace otus
