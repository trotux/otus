#include "IExceptionHandler.h"
#include "CommandQueue.h"
#include "RepeatCommand.h"

#include <exception>
#include <memory>

namespace otus
{

class RepeatExceptionHandler : public IExceptionHandler
{
public:
    RepeatExceptionHandler() = default;
    virtual ~RepeatExceptionHandler() = default;

    void handle(CommandQueue& queue, std::shared_ptr<ICommand> cmd, std::exception& e) override
    {
        auto repeatCmd = std::make_shared<RepeatCommand>(cmd); 
        if (repeatCmd != nullptr)
        {
            queue.push(repeatCmd);
        }
    }
};

}  // namespace otus
