#pragma once

#include "ICommand.h"

#include <memory>
#include <vector>

namespace otus
{

class MacroCommand : public ICommand
{
public:
    MacroCommand() = delete;
    MacroCommand(std::vector<std::shared_ptr<ICommand>>& commands)
        : m_subCommands{commands}
    {}

    template<typename... Args>
    MacroCommand(Args&&... args)
    {
        (addToSubCommandVector(std::forward<Args>(args)), ...);
    }

    virtual ~MacroCommand() = default;

    void execute() override
    {
        for (const auto& it : m_subCommands)
        {
            if (it != nullptr)
            {
                it->execute();
            }
        }
    }

private:

    void addToSubCommandVector(std::shared_ptr<ICommand> cmd)
    {
        m_subCommands.push_back(cmd);
    }

    std::vector<std::shared_ptr<ICommand>> m_subCommands;;
};

}  // namespace otus
