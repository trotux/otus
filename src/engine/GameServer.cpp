#include "engine/GameServer.h"

#include "nlohmann/json_fwd.hpp"

#include <cstdint>
#include <stdexcept>

namespace otus::engine
{

void GameServer::processRpcCall(const nlohmann::json& data)
{
    if (!data.contains("gameId"))
    {
        throw std::runtime_error("missing game id");
    }
    
    auto gameId = data["gameId"].get<std::string>();

    if (!data.contains("operation"))
    {
        throw std::runtime_error("missing operation data");
    }

    auto game = findGame(gameId);
    if (game == nullptr)
    {
        throw std::runtime_error("unknown game");
    }

    game->addOperation(data);
}

std::shared_ptr<IGame> GameServer::findGame(const std::string& name)
{
    const std::lock_guard<std::mutex> lock(m_mutex);
    if (auto it = m_games.find(name); it != m_games.end())
    {
        return it->second;
    }

    return nullptr;
}

void GameServer::stop()
{
    m_rpcServer.stop();
}

void GameServer::run(const std::string& host, uint16_t port)
{
    // Bindings
    //WarehouseServer app;
    //m_rpcServer.Add("GetProduct", std::bind(&Server::processRpcCall, this, std::placeholders::_1), {"gameId"});
    //rpcServer.Add("AddProduct", GetHandle(&WarehouseServer::AddProduct, app), {"product"});
    //rpcServer.Add("AllProducts", GetHandle(&WarehouseServer::AllProducts, app), {});

//    InMemoryConnector inMemoryConnector(m_rpcServer);
    //doWarehouseStuff(inMemoryConnector);

    m_rpcServer.run(host, port);

#if 0
    cout << "Running http example" << "\n";
    jsonrpccxx::CppHttpLibServerConnector httpServer(rpcServer, 8484);
    cout << "Starting http server: " << std::boolalpha << httpServer.StartListening() << "\n";
    CppHttpLibClientConnector httpClient("localhost", 8484);
    std::this_thread::sleep_for(0.5s);
    doWarehouseStuff(httpClient);
#endif
}

}  // namespace otus::engine
