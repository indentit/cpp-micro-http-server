#pragma once
#include <asio.hpp>
#include <string>
#include "header.h"


class Response {

	public:
		Response(asio::ip::tcp::socket* sock);
		~Response();
	
		Header header;
		
		/*! Send response to client with empty body of text/plain
		 *
		 * \param status_code Http status code Number
		 */
		void send();
		void send(unsigned int status_code);
		void send(unsigned int status_code, std::string& body);
		void send(unsigned int status_code, Header* headers, const char* body);
		void send(const char* body);
		void send_json(const std::string &json);
		
	private:
		asio::ip::tcp::socket* sock_;

		void write(const char* buffer, std::size_t num_chars);
		std::size_t write_sync(const char* buffer, std::size_t num_chars);

		void finish();

		/*! Composes the HTTP header for the response based on the
		 * header property fields.
		 */
		std::string response_header();
};


