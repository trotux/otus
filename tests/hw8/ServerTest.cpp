#include "UObject.h"
#include "engine/RpcClient.h"
#include "engine/GameServer.h"
#include "ioc/Base.h"

#include "TestGame.h"
#include "TestCommandQueue.h"
#include "TestVelocitySetCommand.h"
#include "TestMoveCommand.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>
#include "nlohmann/json_fwd.hpp"

#include <memory>
#include <stdexcept>

class ServerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        auto ioc = std::make_shared<otus::ioc::Base>();
        m_server = std::make_unique<otus::engine::GameServer>();
        m_queue = std::make_shared<otus::tests::TestCommandQueue>();

        auto game = std::make_shared<otus::tests::TestGame>("game123", ioc, m_queue);

        m_object = std::make_shared<otus::UObject>();
        game->addObject(548, m_object);

        m_server->addGame(game);

        m_server->run();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    void TearDown() override
    {
        m_server->stop();
        m_server.reset();
        m_queue.reset();
        m_object.reset();
    }

    std::unique_ptr<otus::engine::GameServer> m_server;
    std::shared_ptr<otus::tests::TestCommandQueue> m_queue;
    std::shared_ptr<otus::UObject> m_object;
};


TEST_F(ServerTest, ValidCommand)
{
    otus::engine::RpcClient client("localhost", 8080);

    // Формируем корректное сообщение

    nlohmann::json operation = {{"id", "start-moving"}, {"clientId", 548}, {"args", {{"speed", 2}}}};
    nlohmann::json request = {{"gameId", "game123"}};
    request["operation"] = operation;

    nlohmann::json response;
    auto ret = client.send(request, response);

    ASSERT_TRUE(ret);

    EXPECT_EQ(m_queue->size(), 1);
    m_queue->execute();

    EXPECT_EQ(m_queue->size(), 1);
    m_queue->execute();

    EXPECT_EQ(otus::tests::TestVelocitySetCommand::numberOfCall, 1);
    EXPECT_EQ(otus::tests::TestMoveCommand::numberOfCall, 1);
}

TEST_F(ServerTest, InvalidCommand)
{
    otus::engine::RpcClient client("localhost", 8080);

    otus::tests::TestVelocitySetCommand::numberOfCall = 0;
    otus::tests::TestMoveCommand::numberOfCall = 0;

    // invalid operation id
    nlohmann::json operation1 = {{"clientId", 548}, {"args", {{"speed", 2}}}};
    nlohmann::json request = {{"gameId", "game123"}};
    request["operation"] = operation1;

    nlohmann::json response;
    auto ret = client.send(request, response);
    ASSERT_TRUE(ret);
    EXPECT_EQ(m_queue->size(), 1);
    EXPECT_THROW(m_queue->execute(), std::runtime_error);

    m_queue->clear();
    EXPECT_EQ(m_queue->size(), 0);

    // unknown operation id
    nlohmann::json operation2 = {{"id", "stop-moving"}, {"clientId", 548}, {"args", {{"speed", 2}}}};
    request["operation"] = operation2;

    ret = client.send(request, response);
    ASSERT_TRUE(ret);
    EXPECT_EQ(m_queue->size(), 1);
    EXPECT_THROW(m_queue->execute(), std::runtime_error);

    m_queue->clear();
    EXPECT_EQ(m_queue->size(), 0);
    
    // invalid client id
    nlohmann::json operation3 = {{"id", "start-moving"}, {"args", {{"speed", 2}}}};
    request["operation"] = operation3;

    ret = client.send(request, response);
    ASSERT_TRUE(ret);
    EXPECT_EQ(m_queue->size(), 1);
    EXPECT_THROW(m_queue->execute(), std::runtime_error);

    m_queue->clear();
    EXPECT_EQ(m_queue->size(), 0);

    // unknown client id
    nlohmann::json operation4 = {{"id", "start-moving"}, {"clientId", 547}, {"args", {{"speed", 2}}}};
    request["operation"] = operation4;

    ret = client.send(request, response);
    ASSERT_TRUE(ret);
    EXPECT_EQ(m_queue->size(), 1);
    EXPECT_THROW(m_queue->execute(), std::runtime_error);

    m_queue->clear();
    EXPECT_EQ(m_queue->size(), 0);
    
    // invalid operation args
    nlohmann::json operation5 = {{"id", "start-moving"}, {"clientId", 547}};
    request["operation"] = operation5;

    ret = client.send(request, response);
    ASSERT_TRUE(ret);
    EXPECT_EQ(m_queue->size(), 1);
    EXPECT_THROW(m_queue->execute(), std::runtime_error);

    m_queue->clear();
    EXPECT_EQ(m_queue->size(), 0);
}

TEST_F(ServerTest, MissingOperation)
{
    otus::engine::RpcClient client("localhost", 8080);

    nlohmann::json request = {{"gameId", "game123"}};
    
    nlohmann::json response;
    auto ret = client.send(request, response);
    
    ASSERT_FALSE(ret);
    EXPECT_EQ(response["error"], "missing operation data");
}

TEST_F(ServerTest, MissingGame)
{
    otus::engine::RpcClient client("localhost", 8080);

    nlohmann::json request = {{"operation", {{"id", "start-moving"}, {"clientId", 548}}}};
    nlohmann::json response;
    auto ret = client.send(request, response);
    ASSERT_FALSE(ret);
    EXPECT_EQ(response["error"], "missing game id");
}

TEST_F(ServerTest, UnknownGame)
{
    otus::engine::RpcClient client("localhost", 8080);

    nlohmann::json request = {{"gameId", "game124"}, {"operation", {{"id", "start-moving"}, {"clientId", 548}}}};
    nlohmann::json response;
    auto ret = client.send(request, response);
    ASSERT_FALSE(ret);
    EXPECT_EQ(response["error"], "unknown game");
}

