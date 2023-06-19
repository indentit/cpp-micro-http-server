#include "http_service.h"
#include "header.h"
#include "request.h"
#include "response.h"
#include "router.h"
#include <asio/buffer.hpp>
#include <asio/completion_condition.hpp>
#include <asio/error_code.hpp>
#include <asio/read.hpp>
#include <bits/c++config.h>
#include <cstring>
#include <exception>
#include <ios>
#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>



HttpService::HttpService(asio::ip::tcp::socket* sock)
{
    sock_ = sock;
	req_ = new Request(sock_);
	res_ = new Response(sock_);
}


HttpService::~HttpService()
{
	if (body_buffer != nullptr) {
		delete [] body_buffer;
	}
	if (req_ != nullptr) {
		delete req_;
	}
	if (res_ != nullptr) {
		delete res_;
	}
	if (sock_) {
		delete sock_;
	}
}

void HttpService::finish()
{
    delete this; // calls the class destructor
}


void HttpService::handle_request()
{
    // Start the process by reading http header from request.
	// The call back will deal with the rest of the flow.
	asio::async_read_until(*sock_, request_buf_, 
			"\r\n\r\n", 
			[this](const asio::error_code& error, std::size_t bytes_transfered) {
				req_->bytes_read += bytes_transfered;	
				// parse the request header
				std::istream input(&request_buf_);
				try {
					
					/* Parse request */
					parse_request(bytes_transfered, input);
					

				} catch (std::exception& e) {
					// log error
					std::cout << "Error: " << e.what() << std::endl;
					// send response back to client
					Response res(sock_);
					res.send(400);	
					//delete req_;
					//delete res_;
					//delete sock_;
					finish();
				}

		});
}

void HttpService::parse_request(std::size_t n, std::istream& input)
{
	/*
	//debug
	input.seekg(0, input.beg);
	std::cout << "tellg=" << input.tellg() << "\n";
	input.seekg(0, input.end);
	
	int length = input.tellg();
	input.seekg(0, input.beg);
	std::cout << length << " END OF REQUEST\n";
	*/

	//std::string s(std::istreambuf_iterator<char>(input), {});
	//std::cout << s << "\n";


    int count = 0;
   
    // request method
    char line[300];

    input.getline(line, 300, '\r');
    count += input.gcount();

    input.get(); // remove \n from input stream buffer
	count++;

    std::string ls = line;
    std::string request_method;
    std::istringstream line_stream(ls);
    line_stream >> request_method;
  
    if (request_method.compare("POST") == 0)
        req_->header.request_method = "POST";
    else if (request_method.compare("GET") == 0)
        req_->header.request_method = "GET";
    else if (request_method.compare("PUT") == 0)
        req_->header.request_method = "PUT";
    else
		// throw exception
		throw std::runtime_error("Invalid request method");


    // parse path
	std::string tmp;
    line_stream >> tmp;
    req_->header.path = tmp.c_str();
    
    // parse http version
    line_stream >> tmp;
    req_->header.http_version = tmp.c_str();

	// Go through the remaing header lines and extract the
	// header fields.
	while (count < (n - 1)) {
		input.getline(line, 300, '\r');
		count += input.gcount();
		input.get(); // remove \n from input stream buffer
		count++;
		tmp = line;
		// Check the header field and set it in this object.
		std::size_t pos = tmp.find(':');
		if (pos != std::string::npos) {
			std::string field_name;
			std::string field_value;
			
			field_name = tmp.substr(0, pos);
			string_trim(field_name);
			
			field_value = tmp.substr(pos + 1);
			string_trim(field_value);

			if (field_name.compare("Content-Length") == 0 || field_name.compare("content-length") == 0) {
				req_->header.content_lenght = std::stoi(field_value); // convert string to int	
			} else if (field_name.compare("Cookie") == 0 || field_name.compare("cookie") == 0) {
				req_->header.cookie = field_value;
			} else if(field_name.compare("Content-Type") == 0 || field_name.compare("content-type") == 0) {
				req_->header.content_type = field_value;
			}
		}
	} 

	// Get remaining data in input stream
	std::string s(std::istreambuf_iterator<char>(input), {});
	//std::cout << s << "\n";
	//std::cout << s.length() << "\n";
	body_buffer = new char[req_->header.content_lenght];
	std::strcpy(body_buffer, s.c_str());
	body_bytes_count = s.length();
	
	
	// If there is still incomming data then must read_some until all data is received
	

	if ((req_->header.content_lenght - s.length()) > 0 ) {
		receive_more();
		
	} else {
		req_->set_body(body_buffer);
		//std::cout << "DEBUG body:" << req_->get_body() << "\n";
		/* Route request */
		Router router;
		router.route_request(req_, res_);
		finish();

	}
		
		
}


void HttpService::receive_more()
{
				
	// ensure that no buffer overflow occurs
	if (req_->header.content_lenght - body_bytes_count > 0) {
		
		sock_->async_read_some(
			asio::buffer(body_buffer + body_bytes_count,
			req_->header.content_lenght - body_bytes_count),
			[this](const asio::error_code& error, std::size_t bytes_transfered) {
				
				body_bytes_count += bytes_transfered;

				if (body_bytes_count >= req_->header.content_lenght) {
					req_->set_body(body_buffer);
					/* Route request */
					Router router;
					router.route_request(req_, res_);
					finish();
					} else {
						receive_more();
					}
			});
	}
}



std::string HttpService::get_remote_ip()
{
    // get remote IP of the requesting client
    asio::ip::tcp::endpoint remote_endpoint = sock_->remote_endpoint();
    asio::ip::address remote_address = remote_endpoint.address();
    std::string ips = remote_address.to_string();
    
    return ips;
}


void HttpService::string_trim(std::string& str)
{
	std::size_t pos = str.find_first_not_of(' ');
	str = str.substr(pos);
	pos = str.find_last_not_of(' ');
	str = str.substr(0, pos + 1);
}



