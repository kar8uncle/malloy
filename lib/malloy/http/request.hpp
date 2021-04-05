#pragma once

#include "uri.hpp"

#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>

namespace malloy::http
{

    /**
     * Represents an HTTP request.
     */
    class request :
        public boost::beast::http::request<boost::beast::http::string_body>
    {
    public:
        /**
         * Default constructor
         */
        request() = delete;

        /**
         * Constructor
         *
         * @param raw The underlying raw HTTP message
         */
        request(boost::beast::http::request<boost::beast::http::string_body>&& raw)
        {
            boost::beast::http::request<boost::beast::http::string_body>::operator=(std::move(raw));

            class uri u{ std::string{target().data(), target().size()} };
            m_uri = std::move(u);
        }

        /**
         * Copy constructor.
         *
         * @param other The object to copy construct from.
         */
        request(const request& other) = default;

        /**
         * Move constructor.
         *
         * @param other The object to move-construct from.
         */
        request(request&& other) noexcept = default;

        /**
         * Destructor.
         */
        virtual ~request() = default;

        /**
         * Copy assignment operator.
         *
         * @param rhs The object to copy-assign from.
         * @return A reference to the assignee.
         */
        request& operator=(const request& rhs) = default;

        /**
         * Move assignment operator.
         *
         * @param rhs The object to move-assign from.
         * @return A reference to the assignee.
         */
        request& operator=(request&& rhs) noexcept = default;

        /**
         * Returns the URI portion of the request.
         *
         * @return A copy of the URI.
         */
        [[nodiscard]]
        class uri uri() const noexcept { return m_uri; }

        /**
         * Returns the URI portion of the request.
         *
         * @return A reference to the URI.
         */
        [[nodiscard]]
        class uri& uri() noexcept { return m_uri; }

    private:
        class uri m_uri;
    };

}
