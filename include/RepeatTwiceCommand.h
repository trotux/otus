#pragma once

#include "ICommand.h"
#include "ICommandWrapper.h"
#include "EmptyCommand.h"

#include <memory>

namespace otus
{

class RepeatTwiceCommand : public ICommand, ICommandWrapper
{
public:
    RepeatTwiceCommand() = delete;
    RepeatTwiceCommand(std::shared_ptr<ICommand> cmd)
        : m_cmd(cmd)
    {
        if (m_cmd == nullptr)
        {
            m_cmd = std::make_shared<EmptyCommand>();
        }
    }

    virtual ~RepeatTwiceCommand() = default;

    void execute() override { m_cmd->execute(); }

    std::shared_ptr<ICommand> getCommand() const override { return m_cmd; }

private:
    std::shared_ptr<ICommand> m_cmd;
};

}  // namespace otus
