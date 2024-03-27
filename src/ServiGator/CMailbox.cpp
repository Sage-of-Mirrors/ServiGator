#include "CMailbox.h"


CMailbox gMailbox;


CMailbox::CMailbox()
{

}

CMailbox::~CMailbox()
{

}

bool CMailbox::CheckInbox()
{
	mMailboxMutex.lock();
	bool bInboxNotEmpty = !mInbox.empty();

	mMailboxMutex.unlock();
	return bInboxNotEmpty;
}

bool CMailbox::CheckOutbox()
{
	mMailboxMutex.lock();
	bool bOutboxNotEmpty = !mOutbox.empty();

	mMailboxMutex.unlock();
	return bOutboxNotEmpty;
}

void CMailbox::PushInbox(std::shared_ptr<nlohmann::json> item)
{
	mMailboxMutex.lock();

	mInbox.push(item);

	mMailboxMutex.unlock();
}

std::shared_ptr<nlohmann::json> CMailbox::PopInbox()
{
	mMailboxMutex.lock();

	std::shared_ptr<nlohmann::json> item = mInbox.top();
	mInbox.pop();

	mMailboxMutex.unlock();
	return item;
}

void CMailbox::PushOutbox(std::shared_ptr<nlohmann::json> item)
{
	mMailboxMutex.lock();

	mOutbox.push(item);

	mMailboxMutex.unlock();
}

std::shared_ptr<nlohmann::json> CMailbox::PopOutbox()
{
	mMailboxMutex.lock();

	std::shared_ptr<nlohmann::json> item = mOutbox.top();
	mOutbox.pop();

	mMailboxMutex.unlock();
	return item;
}
