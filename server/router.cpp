#include "router.h"
#include <iostream>
#include <regex>
#include <vector>

// Initialization of static class properties
std::vector<Route> Router::routes;


/*! Adds a route to the router
 *
 * \param url_regex String regex of the url path.
 * \param request_method "GET", "POST", "PUT".
 */
void Router::register_route(std::string url_regex, 
		std::string request_method, 
		void (*callback)(Request*, Response*) )
{
	// set a Route object to be pushed into the routes vector
	Route route;
	route.url_regex = url_regex;
	route.request_method = request_method;
	route.callback = callback;
	routes.push_back(route);	
}



void Router::route_request(Request* req, Response* res)
{
	for (auto& r : routes) {
		// match request path with route regex
		std::regex pat {r.url_regex};
		std::smatch match;

		if (std::regex_match(req->header.path, match, pat) 
				&& (req->header.request_method.compare(r.request_method) == 0)) {
			// call callback
			r.callback(req, res);
			delete req;
			// exit for loop
			return;
		}
	}
	
	// If no route was found we respond error 404
	res->send(404);
	delete req;
}


