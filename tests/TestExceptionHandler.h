#include "IExceptionHandler.h"

namespace otus
{

class TestExceptionHandler : public IExceptionHandler
{
public:
    virtual ~TestExceptionHandler() = default;

    void handle(std::shared_ptr<ICommand> cmd, std::exception& exception) override { m_callCount++; }

    unsigned getCallCount() const { return m_callCount; }

private:
    unsigned m_callCount{0};
};

}  // namespace otus
