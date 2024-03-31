#include "script.h"
#include "keyboard.h"

#include "CMailbox.h"
#include "CServer.h"
#include "commands.h"

CServer gServer;

void updateMailbox()
{
	if (gMailbox.CheckInbox())
	{
		ProcessCommand(gMailbox.PopInbox());
	}

	if (gMailbox.CheckOutbox())
	{
		gServer.DispatchCommand(gMailbox.PopOutbox());
	}
}

void main()
{		
	bool bServerStarted = false;
	gServer.Start();

	// Tick loop
	while (true)
	{
		updateMailbox();

		WAIT(0);
	}
}

void scriptShutdown()
{
	gServer.Stop();
}
