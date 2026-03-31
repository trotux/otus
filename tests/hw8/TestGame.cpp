#include "TestGame.h"

#include "ICommand.h"
#include "UObject.h"
#include "engine/InterpretCommand.h"
#include "ioc/Base.h"

#include "TestVelocitySetCommand.h"
#include "TestMoveCommand.h"

#include <any>
#include <format>
#include <cstdint>
#include <memory>

namespace otus::tests
{

TestGame::TestGame(const std::string& name, std::shared_ptr<ioc::Base> ioc,
                   std::shared_ptr<engine::ICommandQueue> queue)
    : m_name(name)
    , m_ioc{ioc}
    , m_queue{queue}
{
    auto scope = std::format("{}:objects", name);
    m_ioc->resolve<otus::UObject>(ioc::Base::Action{"Scopes.New", scope})->execute();

    // set scope "test1" as current
    ioc->resolve<otus::UObject>(ioc::Base::Action{"Scopes.Current", scope})->execute();

    // register test.command for Test1Command in scope test1
    ioc->resolve<otus::UObject>(ioc::Base::Action{"IOC.Register", "game-objects"},
                                std::function([this](std::vector<std::any> args) -> std::shared_ptr<UObject> {
                                    uint64_t id = std::any_cast<uint64_t>(args[0]);
                                    if (auto it = m_objects.find(id); it != m_objects.end())
                                    {
                                        return it->second;
                                    }

                                    return nullptr;
                                }))
        ->execute();

    scope = std::format("{}:move", name);
    m_ioc->resolve<otus::ICommand>(ioc::Base::Action{"Scopes.New", scope})->execute();

    // set scope "test1" as current
    ioc->resolve<otus::ICommand>(ioc::Base::Action{"Scopes.Current", scope})->execute();

    // register test.command for Test1Command in scope test1
    ioc->resolve<otus::ICommand>(ioc::Base::Action{"IOC.Register", "velocity:set"},
                                 std::function([this](std::vector<std::any> args) -> std::shared_ptr<ICommand> {
                                     return std::make_shared<tests::TestVelocitySetCommand>();
                                 }))
        ->execute();

    ioc->resolve<otus::ICommand>(ioc::Base::Action{"IOC.Register", "move:linear"},
                                 std::function([this](std::vector<std::any> args) -> std::shared_ptr<ICommand> {
                                     return std::make_shared<tests::TestMoveCommand>();
                                 }))
        ->execute();
}

void TestGame::addOperation(const nlohmann::json& data)
{
    auto operation = data["operation"];

    auto cmd = std::make_shared<engine::InterpretCommand>(m_name, m_ioc, m_queue, std::move(operation));

    m_queue->push(cmd);
}

}  // namespace otus::tests
