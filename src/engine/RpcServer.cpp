#include "engine/RpcServer.h"

#include "nlohmann/json_fwd.hpp"

namespace otus::engine
{
RpcServer::RpcServer(Callback&& callback)
    : m_callback{callback}
{
    m_httpServer.Post("/jsonrpc", [this](const httplib::Request& req, httplib::Response& res) {
        try
        {
            auto jsonObj = nlohmann::json::parse(req.body);
            m_callback(jsonObj);

            res.set_content(R"({"status":"accepted"})", "application/json");
        }
        catch (std::exception& e)
        {
            res.status = 400;
            nlohmann::json j;
            j["error"] = e.what();
            res.set_content(j.dump(), "application/json");
        }
    });
}

bool RpcServer::run(const std::string& host, uint16_t port)
{
    if (m_httpServer.is_running())
        return false;

    auto thread = std::thread([port = port, host = host, this]() { m_httpServer.listen(host.c_str(), port); });

    std::swap(m_thread, thread);

    return true;
}

}  // namespace otus::engine
