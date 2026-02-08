#include "IExceptionHandler.h"
#include "CommandQueue.h"
#include "RepeatTwiceCommand.h"

#include <memory>

namespace otus
{

template<typename T>
class RepeatTwiceExceptionHandler : public IExceptionHandler
{
public:
    RepeatTwiceExceptionHandler(CommandQueue& queue)
        : m_queue{queue}
    {}
    virtual ~RepeatTwiceExceptionHandler() = default;

    void handle(std::shared_ptr<ICommand> cmd, std::exception& e) override
    {
        auto repeatCmd = std::make_shared<RepeatTwiceCommand>(cmd);
        m_queue.push(repeatCmd);
    }

private:
    CommandQueue& m_queue;
};

}  // namespace otus
