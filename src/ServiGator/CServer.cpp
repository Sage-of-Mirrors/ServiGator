#include "CServer.h"
#include "CMailbox.h"
#include "commandtypes.h"
#include "json.hpp"

#include <string>
#include <memory>

constexpr char CLIENT_ENDPOINT[] = "http://localhost:8080/servigator";

CServer::CServer() : mClient(CLIENT_ENDPOINT)
{

}

CServer::~CServer()
{

}

void CServer::SetUpServer()
{

}

void CServer::Start()
{
	mServer.Get("/navigator/test_print",
		[](const httplib::Request& req, httplib::Response& res)
		{
			std::shared_ptr<nlohmann::json> testPrintCmd = std::make_shared<nlohmann::json>
			(
				nlohmann::json
				{
					{ "cmd",  CMD_Print             },
				    { "text", "Test print success!" }
				}
			);

			gMailbox.PushInbox(testPrintCmd);
		}
	);

	mServer.Get("/navigator/player_pos",
		[](const httplib::Request& req, httplib::Response& res)
		{
			std::shared_ptr<nlohmann::json> getPlayerPosCmd = std::make_shared<nlohmann::json>
				(
					nlohmann::json
					{
						{ "cmd",  CMD_RequestPlayerPos  }
					}
			);
			
			gMailbox.PushInbox(getPlayerPosCmd);
		}
	);

	mServer.Post("/navigator/cmd",
		[](const httplib::Request& req, httplib::Response& res)
		{
			// Reject any non-JSON requests
			if (std::strcmp(req.get_header_value("content-type").data(), "application/json") != 0)
			{
				res.status = httplib::UnsupportedMediaType_415;
				return;
			}

			std::shared_ptr<nlohmann::json> jsonCmd = std::make_shared<nlohmann::json>(req.body);

			// Reject any malformed JSON (empty, lacking the cmd element, or has an invalid cmd element)
			if (jsonCmd->empty() || !jsonCmd->contains("cmd") || jsonCmd->at("cmd") >= CMD_Count)
			{
				res.status = httplib::BadRequest_400;
				return;
			}

			gMailbox.PushInbox(jsonCmd);
			res.status = httplib::OK_200;
		}
	);

	mListenThread = std::thread(
		[&]()
		{
			mServer.listen("localhost", 8080);
		}
	);
}

void CServer::Stop()
{
	mServer.stop();
	mListenThread.join();
}

bool CServer::IsServerRunning() const
{
	return mServer.is_running();
}

void CServer::DispatchCommand(std::shared_ptr<nlohmann::json> cmdJson)
{
	std::string jsonString = cmdJson->dump();
	mClient.Post("/servigator/cmd", jsonString, "application/json");
}
