#pragma once

#include "UObject.h"
#include "ioc/Base.h"
#include "engine/IGame.h"
#include "engine/ICommandQueue.h"

#include <cstdint>
#include <memory>
#include <nlohmann/json.hpp>

#include <unordered_map>

namespace otus::tests
{

class TestGame : public engine::IGame
{
public:
    TestGame(const std::string& name, std::shared_ptr<ioc::Base> ioc, std::shared_ptr<engine::ICommandQueue> queue);

    std::string getName() override { return m_name; }

    void addObject(uint64_t id, std::shared_ptr<UObject> object) { m_objects.emplace(id, object); }

    void addOperation(const nlohmann::json& operation) override;

private:
    std::string m_name;
    std::shared_ptr<ioc::Base> m_ioc;
    std::shared_ptr<engine::ICommandQueue> m_queue;

    std::unordered_map<uint64_t, std::shared_ptr<UObject>> m_objects;
};

}  // namespace otus::tests
