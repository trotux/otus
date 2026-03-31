#pragma once

#include "engine/IGame.h"
#include "engine/RpcServer.h"

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

namespace otus::engine
{

class GameServer
{
public:
    GameServer()
        : m_rpcServer{std::bind(&GameServer::processRpcCall, this, std::placeholders::_1)}
    {}

    void run(const std::string& host = "127.0.0.1", uint16_t port = 8080);
    void stop();

    void addGame(std::shared_ptr<IGame> game)
    {
        const std::lock_guard<std::mutex> lock(m_mutex);
        m_games.emplace(game->getName(), game);
    }

private:

    std::shared_ptr<IGame> findGame(const std::string& name);
    
    void processRpcCall(const nlohmann::json& data);

    RpcServer m_rpcServer;

    std::mutex m_mutex;
    std::unordered_map<std::string, std::shared_ptr<IGame>> m_games;
};

}  // namespace otus::engine
