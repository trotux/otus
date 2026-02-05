#pragma once

#include "ICommand.h"
#include "ILogger.h"

#include <memory>
#include <format>

namespace otus
{

class LogCommand : public ICommand
{
public:
    LogCommand(ILogger& logger, std::shared_ptr<ICommand> cmd, std::exception& e)
        : m_logger(logger)
    {
        m_name = cmd->name();
        m_message = e.what();
    }

    std::string name() override
    {
        return "log";
    }

    virtual ~LogCommand() = default;

    void execute() override
    {
        auto msg = std::format("command \"{}\" throwed exception \"{}\"", m_name, m_message);

        m_logger.write(msg);
    }

private:
    ILogger& m_logger;
    std::string m_name;
    std::string m_message;
};

}  // namespace otus
