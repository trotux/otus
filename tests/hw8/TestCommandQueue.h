#pragma once

#include "ICommand.h"
#include "engine/ICommandQueue.h"

#include <memory>

namespace otus::tests
{

class TestCommandQueue : public engine::ICommandQueue
{
public:
    void push(std::shared_ptr<ICommand> cmd) override
    {
        m_cmd = cmd;
    }

    std::shared_ptr<ICommand> pop() override
    {
        auto cmd = m_cmd;
        m_cmd = nullptr;
        return cmd;
    }

    virtual bool empty() override { return m_cmd == nullptr; }
    virtual bool size() override { return m_cmd == nullptr ? 0 : 1; }

    void execute()
    {
        m_cmd->execute();
    }

    void clear() { m_cmd.reset(); }

private:
    std::shared_ptr<ICommand> m_cmd; 
};

}  // namespace otus::engine

