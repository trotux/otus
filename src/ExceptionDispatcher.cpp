#include "ICommand.h"

#include "ExceptionDispatcher.h"

#include "Helpers.h"
#include <memory>

namespace otus
{

void ExceptionDispatcher::dispatch(std::shared_ptr<ICommand> cmd, std::exception& exception)
{
    if (cmd == nullptr)
    {
        return;
    }

    std::type_index exceptionTypeIndex = typeid(exception);
    std::type_index cmdTypeIndex = getTypeInfo(*(cmd.get()));

    auto handler = m_locator.getHandler(exceptionTypeIndex, cmdTypeIndex);

    if (handler == nullptr)
    {
        return;
    }

    handler->handle(cmd, exception);
}

}  // namespace otus
