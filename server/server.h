#pragma once
#include <asio.hpp>
#include <unordered_map>
#include "http_service.h"
#include "router.h"

namespace tcp_server {
    
    class Server {
        unsigned short port_ = 3000;
        int backlog_size_ = 200;
        
		public:
            Server();
            Server(const unsigned short port, const int backlog_size);
            ~Server();

            /*! Start the server.
             *
             * The routing map with the mapping of the routes with the handler functions 
             */
            void start(Router& router);

    };

}
