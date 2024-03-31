#pragma once

#include "httplib.h"
#include "json.hpp"

#include <thread>
#include <mutex>
#include <string>
#include <memory>

class CServer
{
	httplib::Server mServer;
	httplib::Client mClient;

	std::thread mListenThread;

	void SetUpServer();

public:
	CServer();
	~CServer();

	void Start();
	void Stop();
	bool IsServerRunning() const;

	void DispatchCommand(std::shared_ptr<nlohmann::json> cmdJson);
};
