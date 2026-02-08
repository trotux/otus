#include "ICommand.h"
#include "IExceptionHandler.h"
#include "ILogger.h"
#include "CommandQueue.h"
#include "LogCommand.h"

#include "Helpers.h"

#include <exception>
#include <format>
#include <memory>

namespace otus
{

template<typename T>
class LogExceptionHandler : public IExceptionHandler
{
public:
    LogExceptionHandler(ILogger& logger, CommandQueue& queue)
        : m_logger{logger}
        , m_queue{queue}
    {}

    virtual ~LogExceptionHandler() = default;

    void handle(std::shared_ptr<ICommand> cmd, std::exception& exception) override
    {
        auto cmdName = getTypeName(*(cmd.get()));
        auto exceptionName = getTypeName(exception);
        auto message = std::format("command \"{}\" throw exception \"{}\"", cmdName, exceptionName);
        auto logCmd = std::make_shared<LogCommand>(m_logger, message);

        m_queue.push(logCmd);
    }

private:
    ILogger& m_logger;
    CommandQueue& m_queue;
};

}  // namespace otus
