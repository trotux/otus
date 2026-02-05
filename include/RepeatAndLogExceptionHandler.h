#include "ICommand.h"
#include "IExceptionHandler.h"
#include "ILogger.h"
#include "CommandQueue.h"
#include "LogCommand.h"
#include "RepeatCommand.h"
#include "BaseLogger.h"

#include <exception>
#include <memory>

namespace otus
{

class RepeatAndLogExceptionHandler : public IExceptionHandler
{
public:
    RepeatAndLogExceptionHandler(ILogger& logger)
        : m_logger{logger}
    {}

    virtual ~RepeatAndLogExceptionHandler() = default;

    void handle(CommandQueue& queue, std::shared_ptr<ICommand> cmd, std::exception& e) override
    {
        std::shared_ptr<RepeatCommand> repeatCmd = std::dynamic_pointer_cast<RepeatCommand>(cmd);
        if (repeatCmd)
        {            
            auto logCmd = std::make_shared<LogCommand>(m_logger, repeatCmd->getCmd(), e); 
            if (logCmd != nullptr)
            {
                queue.push(logCmd);
            }

            return;
        }
        
        repeatCmd = std::make_shared<RepeatCommand>(cmd);
        queue.push(repeatCmd);
    }

private:
    ILogger& m_logger;
};

}  // namespace otus
