#include "EngineSetup.h"


CEngineSetup::CEngineSetup(HINSTANCE HandleInstance, int CommandShow)
{
	DirectXSetup = new CDirectXSetup{};
	if (DirectXSetup->Init(HandleInstance, CommandShow))
	{

	}
}


CEngineSetup::~CEngineSetup()
{
	delete DirectXSetup;
}


void CEngineSetup::MainLoop()
{
	while (DirectXSetup->GetMessage().message != WM_QUIT)
	{
		DirectXSetup->ReadMessage();
		DirectXSetup->RenderFrame();
	}
}