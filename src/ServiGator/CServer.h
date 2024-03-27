#pragma once

#include "httplib.h"

#include <thread>
#include <mutex>

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
};
