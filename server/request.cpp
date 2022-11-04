#include "request.h"
#include "header.h"
#include <asio/error_code.hpp>
#include <bits/c++config.h>
#include <exception>
#include <iostream>
#include <ostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>



Request::Request(asio::ip::tcp::socket* sock)
{
    l_sock = sock;
}


/*! Get a vector with the request path components
 *
 */
std::vector<std::string> Request::path_components()
{
	// Get subcomponents of the request path
	std::string path = header.path;

	std::vector<std::string> out;
	
	std::size_t pos = path.find('/');
	std::size_t len = path.length();
	
	while (pos + 1 < len) {

		std::size_t orig = pos + 1;	
		pos = path.find('/', orig);
		
		if (pos == std::string::npos) {
			if (orig < len) 
				out.push_back(path.substr(orig, len));

			return out;
		}
		
		out.push_back(path.substr(orig, pos-1));
	}

	return out;
}



std::string Request::get_body()
{
	return body_;
}


void Request::set_body(const char *body)
{
	body_ = body;	
}
