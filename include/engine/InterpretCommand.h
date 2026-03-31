#pragma once

#include "ICommand.h"
#include "UObject.h"
#include "ioc/Base.h"
#include "engine/ICommandQueue.h"

#include <nlohmann/json.hpp>

namespace otus::engine
{

class InterpretCommand : public ICommand
{
public:
    explicit InterpretCommand(const std::string& name, std::shared_ptr<ioc::Base> ioc, std::shared_ptr<ICommandQueue> queue, nlohmann::json&& args)
        : m_name{name}
        , m_ioc{ioc}
        , m_queue(queue)
        , m_args(std::move(args))
    {}

    void execute() override;

private:
    void startMoving(std::shared_ptr<UObject> obj, const nlohmann::json& args);

    std::string m_name;
    std::shared_ptr<ioc::Base> m_ioc;
    std::shared_ptr<ICommandQueue> m_queue;
    nlohmann::json m_args;
};

}  // namespace otus::engine
