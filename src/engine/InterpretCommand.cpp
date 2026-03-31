#include "engine/InterpretCommand.h"

#include "ICommand.h"
#include "MacroCommand.h"
#include "UObject.h"

#include <cstdint>
#include <format>
#include <memory>
#include <stdexcept>

namespace otus::engine
{

void InterpretCommand::execute()
{
    if (!m_args.contains("clientId"))
    {
        throw std::runtime_error("invalid client id");
    }

    if (!m_args.contains("id"))
    {
        throw std::runtime_error("invalid command id");
    }

    auto clientId = m_args["clientId"].get<uint64_t>();

    auto scope = std::format("{}:objects", m_name);
    m_ioc->resolve<otus::UObject>(ioc::Base::Action{"Scopes.Current", scope})->execute();

    auto obj = m_ioc->resolve<UObject>("game-objects", clientId);
    if (obj == nullptr)
    {
        throw std::runtime_error("unknown client id");
    }

    auto id = m_args["id"].get<std::string>();
    if (id == "start-moving")
    {
        startMoving(obj, m_args);
    }
    else
    {
        auto msg = std::format("unknown operation '{}'", id);
        throw std::runtime_error(msg);
    }
}

void InterpretCommand::startMoving(std::shared_ptr<UObject> obj, const nlohmann::json& operationData)
{
    if (!operationData.contains("args"))
    {
        throw std::runtime_error("failed to get operation arguments");
    }

    auto args = operationData["args"];
    auto speed = args["speed"].get<int>();

    auto scope = std::format("{}:move", m_name);
    m_ioc->resolve<otus::ICommand>(ioc::Base::Action{"Scopes.Current", scope})->execute();

    auto initCommand = m_ioc->resolve<ICommand>("velocity:set", obj, speed);
    if (initCommand == nullptr)
    {
        throw std::runtime_error("failed to set initial speed");
    }

    auto moveCommand = m_ioc->resolve<ICommand>("move:linear", obj);
    if (moveCommand == nullptr)
    {
        throw std::runtime_error("failed to set initial speed");
    }

    auto macro = std::make_shared<MacroCommand>(initCommand, moveCommand);

    m_queue->push(macro);
}

}  // namespace otus::engine
