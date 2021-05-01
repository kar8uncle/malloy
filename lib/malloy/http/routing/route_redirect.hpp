#pragma once

#include "route.hpp"

namespace malloy::http::server
{

    template<
        typename Request,
        typename Response
    >
    class route_redirect :
        public route<Request, Response>
    {
    public:
        http::status status;
        std::string resource_old;
        std::string resource_new;

        [[nodiscard]]
        bool matches(const Request& req) const override
        {
            return resource_old == req.uri().resource_string();
        }

        [[nodiscard]]
        Response handle(const Request& req) const override
        {
            response resp{ status };
            resp.set("Location", resource_new);

            return resp;
        }

    };

}