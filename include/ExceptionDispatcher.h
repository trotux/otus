#pragma once

#include <memory>
#include "CommandQueue.h"
#include "ExceptionHandlerLocator.h"

namespace otus
{

class ExceptionDispatcher
{
public:
    template<typename ExceptionType, typename CommandType>
    void addHandlerSimple(std::shared_ptr<IExceptionHandler> handler)
    {
        m_locator.registerHandler<ExceptionType, CommandType>(handler);
    }

    template<typename ExceptionType, typename CommandType, typename HandlerType, class... Args>
    void addHandler(Args&&... args)
    {
        auto handler = std::make_shared<HandlerType>(std::forward<Args>(args)...);

        m_locator.registerHandler<ExceptionType, CommandType>(handler);
    }

    template<typename ExceptionType, typename CommandType, typename HandlerType>
    std::shared_ptr<HandlerType> getHandler()
    {
        std::type_index exceptionTypeIndex = typeid(ExceptionType);
        std::type_index cmdTypeIndex = typeid(CommandType);

        auto handler = m_locator.getHandler(exceptionTypeIndex, cmdTypeIndex);

        return std::dynamic_pointer_cast<HandlerType>(handler);
    }

    void dispatch(std::shared_ptr<ICommand> cmd, std::exception& exception);

private:
    ExceptionHandlerLocator m_locator;
};

}  // namespace otus
