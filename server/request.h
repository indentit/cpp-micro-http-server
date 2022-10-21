#pragma once
#include <asio.hpp>
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

	
	std::string body;

	public:
		Request(asio::ip::tcp::socket* sock);
	
		Header header;

		/*! Get a vector with the request path components
		 *
		 */
		std::vector<std::string> path_components();	
				
	private:
		
};


