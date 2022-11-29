#include "response.h"
#include "header.h"
#include <asio.hpp>
#include <asio/buffer.hpp>
#include <asio/write.hpp>
#include <bits/c++config.h>
#include <string>
#include <iostream>


Response::Response(asio::ip::tcp::socket* sock)
{
    sock_ = sock;
}

Response::~Response()
{
	//if (sock_ != nullptr)
	//	delete sock_;
}

void Response::finish()
{
}


std::string Response::response_header()
{
	std::string buffer = "HTTP/1.1 ";
	buffer += header.http_status_table.at(header.status_code);

	// content type
	buffer += "\r\nContent-Type: ";
	buffer += header.content_type;
	
	// content length
	buffer += "\r\nContent-Length: ";
	buffer += std::to_string(header.content_lenght);

	// cookie
	if (!header.cookie.empty())
		buffer += "\r\nCookie: " + header.cookie;

	buffer += "\r\n\r\n";
	return buffer;
}


void Response::write(const char* buf, std::size_t num_chars)
{
	asio::async_write(*sock_,
			asio::buffer(buf, num_chars),
			[this](const asio::error_code& error, std::size_t bytes_transferred) {
				finish();
			}
		);
}


std::size_t Response::write_sync(const char* buf, std::size_t num_chars)
{
    std::size_t total_bytes_written = 0;
	// Run the loop until all data is written
	// to the socket.
	while (total_bytes_written < num_chars) {
		total_bytes_written += sock_->write_some(
			asio::buffer(buf +
			total_bytes_written,
			num_chars - total_bytes_written));
	}
	return total_bytes_written;
}


void Response::send()
{
	std::string buf = response_header().c_str();

	write(buf.c_str(), buf.length());	
}



void Response::send(unsigned int status_code)
{
	header.status_code = status_code;
	std::string buf = response_header().c_str();

	write(buf.c_str(), buf.length());	
}


void Response::send(unsigned int status_code, std::string& body)
{
	header.status_code = status_code;
	header.content_lenght = body.length();
	std::string buf = response_header().c_str();
	buf += body;
	write(buf.c_str(), buf.length());	
}


void Response::send_json(const std::string &json)
{
	header.content_type = "application/json";
	header.content_lenght = json.length();

	std::string buf = response_header().c_str();
	buf += json;

	write(buf.c_str(), buf.length());	
}


