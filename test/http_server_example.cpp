#include "server.h"
#include "router.h"
#include <iostream>
#include <string>

void handle(Request* req, Response* res)
{
    std::string body = "It works!";
    res->send(200, body);
}


int main() {
    // The size of the queue containing the pending connection
    // requests.
    const int BACKLOG_SIZE = 30;
    // Step 1. Here we assume that the server application has
    // already obtained the protocol port number.
    unsigned short port_num = 3333;

	// Routing
	Router router;
	//load_routes(router);

    tcp_server::Server server(port_num, BACKLOG_SIZE);
    server.start();
    
    return 0; 
}


