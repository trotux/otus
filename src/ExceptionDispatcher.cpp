#include "ICommand.h"
#include "CommandQueue.h"

#include "LogExceptionHandler.h"
#include "ExceptionDispatcher.h"

#include <memory>

namespace otus
{

void ExceptionDispatcher::dispatch(CommandQueue& queue, std::shared_ptr<ICommand> cmd, std::exception& exception)
{

    std::println(stderr, "exception has type: {}", typeid(exception).name());
    std::type_index typeIndex = std::type_index(typeid(exception));

    auto handler = m_locator.getHandler(typeIndex);

    if (handler == nullptr)
    {
        return;
    }

    handler->handle(queue, cmd, exception);
}

}
