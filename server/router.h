/*! \file
 * Provides functions related with routing of requests to the 
 * corresponding handler functions.
 */

#pragma once
#include <string>
#include <vector>
#include "response.h"
#include "request.h"

class Router {
	struct Route {
		std::string url_regex;
		std::string request_method;
		void (*callback)(Request*, Response*);
	};

	std::vector<Route> routes;

	public:
		/*! Adds a route to the router
		 *
		 * \param url_regex String regex of the url path.
		 * \param request_method "GET", "POST", "PUT".
		 */
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


