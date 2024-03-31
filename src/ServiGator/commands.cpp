#include "commands.h"
#include "commandTypes.h"
#include "CMailbox.h"
#include "util.h"
#include "../../inc/types.h"

#include "json.hpp"

#include <stdint.h>
#include <string>
#include <memory>

void ProcPrintCommand(std::shared_ptr<nlohmann::json> cmd)
{
	std::string text = (*cmd)["text"];
	PrintObjective(text.data());
}

void ProcPlayerPosCommand()
{
	Vector3 playerPos = GetPlayerPos();
	std::shared_ptr<nlohmann::json> playerPosResponse = std::make_shared<nlohmann::json>
		(
			nlohmann::json
			{
				{ "cmd",  CMD_RequestPlayerPos  } ,
				{
					"pos",
					{
						{ "x", playerPos.x },
			            { "y", playerPos.y },
			            { "z", playerPos.z }
			        }
				}
			}
	);

	gMailbox.PushOutbox(playerPosResponse);
}

void ProcessCommand(std::shared_ptr<nlohmann::json> cmd)
{
	uint32_t commandType = CMD_Count;
	cmd->at("cmd").get_to(commandType);

	switch (commandType)
	{
		case CMD_Print:
			ProcPrintCommand(cmd);
			break;
		case CMD_RequestPlayerPos:
			ProcPlayerPosCommand();
			break;
		default:
			break;
	}
}
