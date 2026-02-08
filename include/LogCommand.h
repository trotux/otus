#pragma once

#include "ICommand.h"
#include "ILogger.h"

namespace otus
{

class LogCommand : public ICommand
{
public:
    LogCommand(ILogger& logger, std::string message)
        : m_logger{logger}
        , m_message{message}
    {}

    virtual ~LogCommand() = default;

    void execute() override { m_logger.write(m_message); }

private:
    ILogger& m_logger;
    std::string m_message;
};

}  // namespace otus
