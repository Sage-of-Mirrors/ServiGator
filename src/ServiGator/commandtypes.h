#pragma once

#include <stdint.h>

enum ECommandType : uint32_t
{
	CMD_Print,
	CMD_RequestPlayerPos,
	CMD_InitTrainTrack,
	CMD_UpdateTrainTrack,
	CMD_Count
};
