#pragma once
#include <map>
#include <string>
            
struct Header {
	std::string request_method;
	std::string path;
	std::string http_version;
	unsigned int content_lenght = 0;
	std::string cookie;
	static const std::map<unsigned int, std::string> http_status_table;
	unsigned int status_code = 200;
	std::string content_type = "text/plain";
};


