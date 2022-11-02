/*! \file
 * Provides functions related with routing of requests to the 
 * corresponding handler functions.
 */

#pragma once
#include <string>
#include <vector>
#include "response.h"
#include "request.h"

struct Route {
	std::string url_regex;
	std::string request_method;
	void (*callback)(Request*, Response*);
};

class Router {

	static std::vector<Route> routes;

	public:
		
		void register_route(std::string url_regex, 
				std::string request_method, 
				void (*callback)(Request*, Response*) );

		/*! Routes based on the path.
		 *
		 * It will match the path with the registered routes and call the callback
		 * to handle the specific request.
		 *
		 * \param req Request object.
		 * \param res Response object.
		 */
		void route_request(Request* req, Response* res);
};


