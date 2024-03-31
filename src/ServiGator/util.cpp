#include "util.h"

#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"

void PrintObjective(const char* text)
{
	UILOG::_UILOG_SET_CACHED_OBJECTIVE(text);
	UILOG::_UILOG_PRINT_CACHED_OBJECTIVE();
	UILOG::_UILOG_CLEAR_HAS_DISPLAYED_CACHED_OBJECTIVE();
	UILOG::_UILOG_CLEAR_CACHED_OBJECTIVE();
}

Vector3 GetPlayerPos()
{
	return ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false, false);
}
