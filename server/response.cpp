#include "response.h"
#include "header.h"
#include <bits/c++config.h>
#include <string>
#include <iostream>


Response::Response(asio::ip::tcp::socket* sock)
{
    sock_ = sock;
}



std::size_t Response::write(const char* buf, std::size_t num_chars)
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



void Response::send(unsigned int status_code)
{
	Header header;

	// Step 2. Allocating and filling the buffer.
    std::string buf = "HTTP/1.1 ";
    buf += header.http_status_table.at(status_code);
    buf += "\r\nContent-Type: text/plain\r\n";
	buf.append("Content-Length: 0");
	buf.append("\r\n");
	buf.append("\r\n");

	write(buf.c_str(), buf.length());	
}


void Response::send(unsigned int status_code, std::string& body)
{
	Header header;

	// Step 2. Allocating and filling the buffer.
    std::string buf = "HTTP/1.1 ";
    buf += header.http_status_table.at(status_code);
    buf += "\r\nContent-Type: text/plain\r\n";
	buf += "Content-Length: ";
	buf += std::to_string(body.length());
	buf += "\r\n\r\n";

	buf += body;

	write(buf.c_str(), buf.length());	
}


void Response::send_json(const std::string json)
{
	Header header;

	// headers
    std::string buf = "HTTP/1.1 ";
    buf += header.http_status_table.at(200);
    buf += "\r\nContent-Type: application/json\r\n";
	buf += "Content-Length: ";
	buf += std::to_string(json.length());
	buf += "\r\n";
	buf += "\r\n";

	// body
	buf += json;

	// write to socket
	write(buf.c_str(), buf.length());	
}


