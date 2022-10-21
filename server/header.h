#pragma once
#include <map>
#include <string>
            
struct Header {
	std::string request_method;
	std::string path;
	std::string http_version;
	int content_lenght = 0;
	static const std::map<unsigned int, std::string> http_status_table;

};


