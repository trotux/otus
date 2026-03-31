#pragma once

#include <cpp-httplib/httplib.h>
#include <nlohmann/json.hpp>

#include <cstdint>

namespace otus::engine
{

class RpcClient
{
public:
    using Callback = std::function<void(const nlohmann::json&)>;
    RpcClient(const std::string &host, uint16_t port)
        : m_httpClient{host.c_str(), port}
    {}

    bool send(const nlohmann::json& request, nlohmann::json& response)
    {
        bool ret = true;
        auto res = m_httpClient.Post("/jsonrpc", request.dump(), "application/json");
        if (!res || res->status != 200)
        {
            ret = false;
        }

        response = nlohmann::json::parse(res->body);

        return ret;
    }

private:
    httplib::Client m_httpClient;
    Callback m_callback;
};

}  // namespace otus::engine
