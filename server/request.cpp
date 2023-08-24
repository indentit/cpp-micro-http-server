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


/*!
 * \return String with the request body.
 */
std::string Request::get_body()
{
	return body_;
}


void Request::set_body(const char *body)
{
	body_ = body;	
}


std::string Request::remote_ip()
{
    // get remote IP of the requesting client
    asio::ip::tcp::endpoint remote_endpoint = l_sock->remote_endpoint();
    asio::ip::address remote_address = remote_endpoint.address();
    std::string ips = remote_address.to_string();
    
    return ips;
}

		
const char* Request::bearer_token()
{
	// extract the from the Authorization header
	if (!header.authorization.empty()) {
		int pos = header.authorization.find("Bearer");
		if (pos == std::string::npos) {
			pos = header.authorization.find("bearer");
		}
		if(pos != std::string::npos) {
			bearer_token_ = header.authorization.substr(pos + 6);
			string_trim(bearer_token_);
		}
	}

	return bearer_token_.c_str();
}


void Request::string_trim(std::string& str)
{
	std::size_t pos = str.find_first_not_of(' ');
	str = str.substr(pos);
	pos = str.find_last_not_of(' ');
	str = str.substr(0, pos + 1);
}



