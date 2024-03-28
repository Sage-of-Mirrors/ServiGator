/*
	THIS FILE IS A PART OF SCRIPTHOOK V2
				https://ragemodding.org/rdr2/scripthook/
			(C) RAGE Modding Collective 2024
*/

#pragma once

#include <windows.h>
#include <stdint.h>

#define IMPORT __declspec(dllimport)

/* keyboard */

// DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow
typedef void(*KeyboardHandler)(DWORD, WORD, BYTE, BOOL, BOOL, BOOL, BOOL);

// Register keyboard handler
// must be called on dll attach
IMPORT void keyboardHandlerRegister(KeyboardHandler handler);

// Unregister keyboard handler
// must be called on dll detach
IMPORT void keyboardHandlerUnregister(KeyboardHandler handler);

/* scripts */

IMPORT void scriptWait(DWORD time);
IMPORT void scriptRegister(HMODULE module, void(*LP_SCRIPT_MAIN)());
IMPORT void scriptRegisterAdditionalThread(HMODULE module, void(*LP_SCRIPT_MAIN)());
IMPORT void scriptUnregister(HMODULE module);
IMPORT void scriptUnregister(void(*LP_SCRIPT_MAIN)()); // deprecated

IMPORT void nativeInit(UINT64 hash);
IMPORT void nativePush64(UINT64 val);
IMPORT PUINT64 nativeCall();

static void WAIT(DWORD time) { scriptWait(time); }
static void TERMINATE() { WAIT(MAXDWORD); }

// Returns pointer to global variable
// make sure that you check game version before accessing globals because
// ids may differ between patches
IMPORT UINT64* getGlobalPtr(int globalId);
// Returns pointer to static variable in script
IMPORT UINT64* getStaticPtr(const char* scriptName, int staticId);

/* world */

// Get entities from internal pools
// return value represents filled array elements count
// can be called only in the same thread as natives
IMPORT int worldGetAllVehicles(int* arr, int arrSize);
IMPORT int worldGetAllPeds(int* arr, int arrSize);
IMPORT int worldGetAllObjects(int* arr, int arrSize);
IMPORT int worldGetAllPickups(int* arr, int arrSize);
IMPORT int worldGetAllBlips(int* arr, int arrSize);
IMPORT int worldGetAllBoxVolumes(int* arr, int arrSize);
IMPORT int worldGetAllCylinderVolumes(int* arr, int arrSize);
IMPORT int worldGetAllSphereVolumes(int* arr, int arrSize);
IMPORT int worldGetAllCams(int* arr, int arrSize);

/* misc */

// Returns base object pointer using it's script handle
// make sure that you check game version before accessing object fields because
// offsets may differ between patches
IMPORT BYTE* getScriptHandleBaseAddress(int handle);

IMPORT void* getCommandFromHash(uint64_t hash);

IMPORT void switchLabel(const char* oldLabel, const char* newLabel);

enum eGameVersion : int
{
	VER_AUTO,
	VER_1_0_1491_18_RGS,
	VER_1_0_1491_18_STEAM,
	VER_UNK = -1
};

IMPORT eGameVersion getGameVersion();
