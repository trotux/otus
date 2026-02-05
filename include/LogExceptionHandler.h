#include "IExceptionHandler.h"
#include "ILogger.h"
#include "CommandQueue.h"
#include "LogCommand.h"
#include "BaseLogger.h"

#include <exception>
#include <memory>

namespace otus
{

class LogExceptionHandler : public IExceptionHandler
{
public:
    LogExceptionHandler(ILogger& logger)
        : m_logger{logger}
    {}

    virtual ~LogExceptionHandler() = default;

    void handle(CommandQueue& queue, std::shared_ptr<ICommand> cmd, std::exception& e) override
    {
        auto logCmd = std::make_shared<LogCommand>(m_logger, cmd, e); 
        if (logCmd != nullptr)
        {
            queue.push(logCmd);
        }
    }

private:
    ILogger& m_logger;
};

}  // namespace otus
