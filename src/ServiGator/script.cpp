#include "script.h"
#include "keyboard.h"
#include <restbed>

#include <memory>
#include <string>
#include <thread>
#include <sock>

void DisplayObjective(const char* objective)
{
	UILOG::_UILOG_SET_CACHED_OBJECTIVE(objective);
	UILOG::_UILOG_PRINT_CACHED_OBJECTIVE();
	UILOG::_UILOG_CLEAR_HAS_DISPLAYED_CACHED_OBJECTIVE();
	UILOG::_UILOG_CLEAR_CACHED_OBJECTIVE();
}

void get_method_handler(const std::shared_ptr<restbed::Session> session)
{
	const std::shared_ptr<const restbed::Request> request = session->get_request();

	const std::string body = "Got name: " + request->get_path_parameter("name");
	session->close(restbed::OK, body, { { "Content-Length", std::to_string(body.size()) } });
}

void run_server()
{
	std::shared_ptr<restbed::Resource> resource;
	std::shared_ptr<restbed::Settings> settings;

	resource = std::make_shared<restbed::Resource>();
	resource->set_path("/test/{name: .*}");
	resource->set_method_handler("GET", get_method_handler);

	settings = std::make_shared<restbed::Settings>();
	settings->set_port(1984);
	settings->set_default_header("Connection", "close");

	restbed::Service service;
	service.publish(resource);
	service.start(settings);
}

void main()
{		
	// Anything called above the loop will only get called once
	std::thread t(run_server);

	while (true)
	{
		// Anything called in the loop will be called every frame or tick
		WAIT(0);
	}
}
