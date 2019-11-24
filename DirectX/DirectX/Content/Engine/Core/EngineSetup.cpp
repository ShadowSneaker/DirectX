#define _CRT_SECURE_NO_WARNINGS

#include "EngineSetup.h"
#include "../World/World.h"

CEngineSetup::CEngineSetup(HINSTANCE HandleInstance, int CommandShow)
{
	// Temporary stuff until I can find a better way to get a debug log with DirectX.
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);

	World = new CWorld{ HandleInstance, CommandShow };
}


CEngineSetup::~CEngineSetup()
{
	delete World;
}


void CEngineSetup::Startup()
{
	World->Play();
}