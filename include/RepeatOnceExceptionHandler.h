#include "ICommand.h"
#include "IExceptionHandler.h"
#include "CommandQueue.h"
#include "RepeatOnceCommand.h"

#include <exception>
#include <memory>

namespace otus
{

template<typename T>
class RepeatOnceExceptionHandler : public IExceptionHandler
{
public:
    RepeatOnceExceptionHandler(CommandQueue& queue)
        : m_queue{queue}
    {}
    virtual ~RepeatOnceExceptionHandler() = default;

    void handle(std::shared_ptr<ICommand> cmd, std::exception& e) override
    {
        auto repeatCmd = std::make_shared<RepeatOnceCommand>(cmd);
        m_queue.push(repeatCmd);
    }

private:
    CommandQueue& m_queue;
};

}  // namespace otus
