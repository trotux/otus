#pragma once

#include "CommandQueue.h"
#include "ExceptionDispatcher.h"

namespace otus {

class CommandQueueProcessor
{
public:
    CommandQueueProcessor(CommandQueue& queue, ExceptionDispatcher& dispatcher)
        : m_queue{queue}
        , m_dispatcher{dispatcher}
    {}

    void process();

private:
    CommandQueue& m_queue;
    ExceptionDispatcher& m_dispatcher;
};

} // namespace otus
