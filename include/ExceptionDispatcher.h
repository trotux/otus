#pragma once

#include "CommandQueue.h"
#include "ExceptionHandlerLocator.h"

namespace otus
{

class ExceptionDispatcher
{
public:
    template<typename ExceptionType>
    void addHandler(std::shared_ptr<IExceptionHandler> handler)
    {
        m_locator.registerHandler<ExceptionType>(handler);
    }

    void dispatch(CommandQueue& queue, std::shared_ptr<ICommand> cmd, std::exception& exception);

private:
    ExceptionHandlerLocator m_locator;
};

}  // namespace otus
