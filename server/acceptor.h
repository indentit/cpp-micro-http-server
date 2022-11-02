#pragma once

#include <asio.hpp>
#include <asio/error_code.hpp>
#include <asio/io_context.hpp>
#include "router.h"

class Acceptor {
    asio::io_context& io_context_;
	asio::ip::tcp::acceptor acceptor_;
	unsigned int backlog_size_;
	bool is_stopped_;


	public:
		/*! Creates a passive endpoint to listen to incomming
		 * client connection requests.
		 *
		 * \param ios io_context object
		 * \param port_num Port number to wich the passive socket
		 * will be listenning for connection requests
		 */
		Acceptor(asio::io_context& ios, unsigned short port_num) :
			io_context_(ios), // initiates the context
			acceptor_(
				io_context_,
				asio::ip::tcp::endpoint(
					asio::ip::address_v4::any(),
					port_num
					)
				), // creates the passive socket (aka, acceptor)
			is_stopped_(false)
			{}

		/*! Creates a passive endpoint to listen to incomming
		 * client connection requests.
		 *
		 * \param ios io_context object
		 * \param port_num Port number to wich the passive socket
		 * will be listenning for connection requests
		 */
		Acceptor(asio::io_context& ios, unsigned short port_num, unsigned int backlog_size) :
			io_context_(ios), // initiates the context
			acceptor_(
				io_context_,
				asio::ip::tcp::endpoint(
					asio::ip::address_v4::any(),
					port_num
					)
				), // creates the passive socket (aka, acceptor)
			backlog_size_(backlog_size),
			is_stopped_(false)
			{}

		/*! Start accepting incoming connection requests
         */
		void start();
        
        /*! Stop accepting incomming connection requests
         */
        void stop();

    private:
        /*! Creates a new active socket for a new client connection,
         * accept a new connection and calls on_accept method.
         */
        void init_accept();

		/*! Associate handle for received request and start the
		 * cycle of accepting a new coonection.
		 */
        void on_accept(const asio::error_code& error_code,
                asio::ip::tcp::socket* sock);

};
