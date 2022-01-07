#pragma once

#include "3rdparty/doctest/doctest.hpp"

/*
 * These includes get included by doctest.hpp. However, there is a note:
 *
 * "required includes - will go only in one translation unit!"
 *
 * which means that we have to include them again as we generate multiple translation units.
 */
#include <iostream>
#include <functional>
#include <malloy/client/controller.hpp>
#include <malloy/server/controller.hpp>

namespace malloy::test
{
    /**
     * Performs a roundtrip using server & client components.
     *
     * @param port The port to perform the test on.
     * @param setup_client The client setup routine.
     * @param setup_server The server setup routine.
     */
    inline void roundtrip(
        const uint16_t port,
        std::function<void(malloy::client::controller&)> setup_client,
        std::function<void(malloy::server::controller&)> setup_server)
    {
        namespace mc = malloy::client;
        namespace ms = malloy::server;

        malloy::controller::config general_cfg;
        general_cfg.num_threads = 2;
        general_cfg.logger = spdlog::default_logger();

        ms::controller::config server_cfg{general_cfg};
        server_cfg.interface = "127.0.0.1";
        server_cfg.port = port;

        ms::controller s_ctrl{server_cfg};

        mc::controller::config cli_cfg{general_cfg};
        mc::controller c_ctrl{cli_cfg};

        setup_server(s_ctrl);
        setup_client(c_ctrl);

        auto s_session = start(std::move(s_ctrl));
        start(c_ctrl).run();
    }
}
