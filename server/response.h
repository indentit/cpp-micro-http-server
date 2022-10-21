#pragma once
#include <asio.hpp>
#include <string>
#include "header.h"


class Response {
	Header header;

	public:
		Response(asio::ip::tcp::socket* sock);
		
		/*! Send response to client with empty body of text/plain
		 *
		 * \param status_code Http status code Number
		 */
		void send(unsigned int status_code);
		void send(unsigned int status_code, const char* body);
		void send(unsigned int status_code, std::string& body);
		void send(unsigned int status_code, Header* headers, const char* body);
		void send(const char* body);
		void send_json(const std::string json);
		
	private:
		asio::ip::tcp::socket* sock_;

		std::size_t write(const char* buffer, std::size_t num_chars);
};


