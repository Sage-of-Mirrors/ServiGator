#include "CServer.h"

#include <string>

constexpr char CLIENT_ENDPOINT[] = "http://localhost:8080/navigator";

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
	mServer.Get("/hi",
		[](const httplib::Request& req, httplib::Response& res)
		{
			res.set_content("Hello World!", "text/plain");
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
