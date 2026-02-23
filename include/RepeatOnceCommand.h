#pragma once

#include "EmptyCommand.h"
#include "ICommand.h"
#include "ICommandWrapper.h"

#include <memory>

namespace otus
{

class RepeatOnceCommand : public ICommand, ICommandWrapper
{
public:
    RepeatOnceCommand() = delete;
    RepeatOnceCommand(std::shared_ptr<ICommand> cmd)
        : m_cmd(cmd)
    {
        if (m_cmd == nullptr)
        {
            m_cmd = std::make_shared<EmptyCommand>();
        }
    }

    virtual ~RepeatOnceCommand() = default;

    void execute() override
    {
        m_cmd->execute();
    }

    std::shared_ptr<ICommand> getCommand() const override { return m_cmd; }

private:

    std::shared_ptr<ICommand> m_cmd;
};

}  // namespace otus
