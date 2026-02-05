#pragma once

#include "ICommand.h"

#include <memory>

namespace otus
{

class RepeatCommand : public ICommand
{
public:
    RepeatCommand() = delete;
    RepeatCommand(std::shared_ptr<ICommand> cmd)
        : m_cmd(cmd)
    {}

    virtual ~RepeatCommand() = default;

    std::string name() override
    {
        return "repeat";
    }

    void execute() override
    {
        if (m_cmd == nullptr)
        {
            return;
        }

        m_cmd->execute();
    }

private:
    std::shared_ptr<ICommand> m_cmd;
};

}  // namespace otus
