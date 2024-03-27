#pragma once

#include "json.hpp"

#include <thread>
#include <memory>
#include <stack>
#include <mutex>

class CMailbox
{
	std::mutex mMailboxMutex;

	std::stack<std::shared_ptr<nlohmann::json>> mInbox;
	std::stack<std::shared_ptr<nlohmann::json>> mOutbox;

public:
	CMailbox();
	~CMailbox();

	bool CheckInbox();
	bool CheckOutbox();

	void PushInbox(std::shared_ptr<nlohmann::json> item);
	std::shared_ptr<nlohmann::json> PopInbox();

	void PushOutbox(std::shared_ptr<nlohmann::json> item);
	std::shared_ptr<nlohmann::json> PopOutbox();
};

extern CMailbox gMailbox;
