#include "ILogger.h"

#include <string>

namespace otus
{

class TestLogger : public ILogger
{
public:

    virtual ~TestLogger() = default;

    void write(const std::string& message) override
    {
        m_message = message;
    }

    std::string getMessage() const
    {
        return m_message;
    }

private:

    std::string m_message;
};

}  // namespace otus
