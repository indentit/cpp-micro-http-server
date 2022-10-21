#pragma once
#include <asio.hpp>
#include <bits/c++config.h>
#include <map>
#include <unordered_map>
#include <string>
#include "router.h"
#include "header.h"
#include "response.h"
#include "request.h"


class HttpService {
	asio::ip::tcp::socket* sock_;
	asio::streambuf request_buf_;
	Request* req_;
	Response* res_;
	
	public:
		HttpService(asio::ip::tcp::socket* sock);
		~HttpService();

		/*! Handles the http request and routes it.
		 *
		 * Reads the header, parses it and reads the body if exists.
		 *
		 */
		void handle_request(Router& router);
	   
		/*! Get the IP of the client who sent the request.
		 *
		 * \return IP string.
		 */
		std::string get_remote_ip();

	private:
		/*! Parse client request
		 *
		 * Before calling this method the request header must be read
		 * from the active socket connecto to the client.
		 *
		 * This method will then parse the request header and read the
		 * body if one exists.
		 *
		 * \param num_chars Number of chars/bytes representing the 
		 * size of the request header.
		 * \param header_stream Input stream with the request header.
		 * \param callback Callback function pointer to be called once the 
		 * request is received and parsed, including the body. 
		 */
		void parse_request(std::size_t header_num_bytes, std::istream& header_stream);

		void string_trim(std::string&);

		void finish();
};



