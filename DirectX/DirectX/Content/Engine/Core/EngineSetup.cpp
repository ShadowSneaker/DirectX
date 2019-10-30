#include "EngineSetup.h"
#include "../World/World.h"

CEngineSetup::CEngineSetup(HINSTANCE HandleInstance, int CommandShow)
{
	World = new CWorld{ HandleInstance, CommandShow };

	//DirectXSetup = new CDirectXSetup{};
	//if (DirectXSetup->Initialise(HandleInstance, CommandShow))
	//{
	//
	//}
}


CEngineSetup::~CEngineSetup()
{
	delete World;
}


void CEngineSetup::Startup()
{
	World->Play();

	//while (DirectXSetup->GetMessage().message != WM_QUIT)
	//{
	//	DirectXSetup->ReadMessage();
	//
	//	DirectXSetup->RenderFrame();
	//}
}