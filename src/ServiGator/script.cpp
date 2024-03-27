#include "script.h"
#include "keyboard.h"

#include "CMailbox.h"
#include "CServer.h"

#include <memory>


void DisplayObjective(const char* objective)
{
	UILOG::_UILOG_SET_CACHED_OBJECTIVE(objective);
	UILOG::_UILOG_PRINT_CACHED_OBJECTIVE();
	UILOG::_UILOG_CLEAR_HAS_DISPLAYED_CACHED_OBJECTIVE();
	UILOG::_UILOG_CLEAR_CACHED_OBJECTIVE();
}

void main()
{		
	bool bServerStarted = false;

	CServer server;
	server.Start();

	// Tick loop
	while (true)
	{
		// Display a message if the server started successfully
		if (!bServerStarted)
		{
			if (server.IsServerRunning())
			{
				bServerStarted = true;
				DisplayObjective("ServiGator up and running!");
			}
		}

		WAIT(0);
	}
}
