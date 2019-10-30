#include "EngineSetup.h"


int WINAPI WinMain(_In_ HINSTANCE HandleInstance, _In_opt_ HINSTANCE HPrevInstance, _In_ LPSTR LPCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(HPrevInstance);
	UNREFERENCED_PARAMETER(LPCmdLine);

	CEngineSetup* Setup = new CEngineSetup{ HandleInstance, nCmdShow };
	Setup->Startup();
	delete Setup;
	
	return 0;
}
