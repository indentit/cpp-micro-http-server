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

	std::string bearer_token_;


	public:
		Request(asio::ip::tcp::socket* sock);
	
		Header header;

		std::vector<std::string> path_components();	
	
		/*! Get the request body in string format. */
		std::string get_body();

		void set_body(const char * body);
		
		size_t bytes_read = 0;

		/*! Get the IP of the client that made the request.
		 *
		 * \return String with the IP.
		 */
		std::string remote_ip();

		/** Gets the jwt string from the Authorization header.
		 *
		 * On Error:
		 * Return an empty string;
		 */
		const char* bearer_token();

	private:

		void string_trim(std::string& str);
		
};


