#include "acceptor.h"
#include <asio/error_code.hpp>
#include "http_service.h"
#include <iostream>

void Acceptor::start()
{
    acceptor_.listen();
    init_accept();
}


void Acceptor::stop()
{
    is_stopped_ = true;
}


void Acceptor::init_accept()
{
    // create a new active socket pointer
    asio::ip::tcp::socket* sock = new asio::ip::tcp::socket (io_context_);

    // accept a new connection
    acceptor_.async_accept(*sock, [this, sock](const asio::error_code& error)
            {
                on_accept(error, sock);
            });
}


void Acceptor::on_accept(const asio::error_code& ec,
        asio::ip::tcp::socket* sock)
{
    if (!ec) {
		// service the request
        (new HttpService(sock))->handle_request(router_);
    } else {
        std::cout << "Error occured! Error code = "
            << ec.value() << ". Message: " << ec.message() << std::endl;
    }

	// Init next async accept operation if
	// acceptor has not been stopped yet.
	if (!is_stopped_) {
		init_accept();
	}
	else {
		// Stop accepting incoming connections
		// and free allocated resources.
		acceptor_.close();
	}
}





