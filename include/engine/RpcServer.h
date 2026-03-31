#pragma once

#include <cpp-httplib/httplib.h>
#include <nlohmann/json.hpp>
#include "nlohmann/json_fwd.hpp"

#include <cstdint>
#include <functional>
#include <string>

namespace otus::engine
{

class RpcServer
{
public:
    using Callback = std::function<void(const nlohmann::json&)>;
    explicit RpcServer(Callback&& callback);
    ~RpcServer() { stop(); }

    bool run(const std::string& host, uint16_t port);

    void stop()
    {
        if (m_httpServer.is_running())
        {
            m_httpServer.stop();
            m_thread.join();
        }
    }

private:
    std::thread m_thread;
    httplib::Server m_httpServer;
    Callback m_callback;
};

}  // namespace otus::engine
