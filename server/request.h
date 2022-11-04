#pragma once
#include <asio.hpp>
#include <cstddef>
#include <map>
#include <unordered_map>
#include <string>
#include "header.h"

/*! Class representing a http request
 */
class Request {

	asio::ip::tcp::socket* l_sock;

	/*! Map containing the http request header
	 */
	std::unordered_map<std::string, std::string> raw_header;

	std::string body_;


	public:
		Request(asio::ip::tcp::socket* sock);
	
		Header header;

		std::vector<std::string> path_components();	
		
		std::string get_body();

		void set_body(const char * body);
		
		size_t bytes_read = 0;

	private:
		
};


