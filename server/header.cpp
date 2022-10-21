#include "header.h"


const std::map<unsigned int, std::string> Header::http_status_table =
{
     { 200, "200 OK" },
     { 400, "400 Bad Request" },
     { 404, "404 Not Found" },
     { 413, "413 Request Entity Too Large" },
     { 500, "500 Server Error" },
     { 501, "501 Not Implemented" },
     { 505, "505 HTTP Version Not Supported" }
};



