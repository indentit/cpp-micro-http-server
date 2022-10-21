#include "server.h"
#include "acceptor.h"

using namespace tcp_server;

Server::Server()
{}

Server::Server(const unsigned short port, const int backlog_size)
{
    port_ = port;
    backlog_size_ = backlog_size;
}

Server::~Server(){}

void Server::start(Router& router)
{
	// create a server passive socket (acceptor) to listen for
	// incomming connection requests.
    asio::io_context io_context;
	Acceptor acceptor(io_context, port_, router, backlog_size_);


	acceptor.start();

	// run asio context processing loop
	io_context.run();

	// infinite loop
	while(true){}

}



