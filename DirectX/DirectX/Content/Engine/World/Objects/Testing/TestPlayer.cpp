#include "TestPlayer.h"
#include "../../../Graphics/Camera.h"
#include "../../../Core/Systems/InputManager.h"
#include "../../../Graphics/Renderer.h"


CTestPlayer::CTestPlayer(SObjectBase Core)
	:CCharacter::CCharacter{ Core }
{
	SetupInput(GetInputManager());
	Camera = new CCamera{};
	GetRenderer()->SetCamera(Camera);
}


CTestPlayer::~CTestPlayer()
{
	delete Camera;
}


void CTestPlayer::SetupInput(CInputManager* Input)
{
	Input->BindAxis("MoveForward", EKey::IE_F11, std::bind(&CTestPlayer::MoveForward, this, std::placeholders::_1));
	Input->BindAxis("MoveForward", EKey::IE_Decimal, -1.0f);
	Input->BindAxis("MoveSideways", EKey::IE_F7, std::bind(&CTestPlayer::MoveSideways, this, std::placeholders::_1));
	Input->BindAxis("MoveSideways", EKey::IE_F10, -1.0f);
	Input->BindAxis("MoveUp", EKey::IE_NumLock, std::bind(&CTestPlayer::MoveUp, this, std::placeholders::_1));
	Input->BindAxis("MoveUp", EKey::IE_Numpad3, -1.0f);
}


void CTestPlayer::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		Camera->MoveForward(Value / 1000.0f);
	}
}


void CTestPlayer::MoveSideways(float Value)
{
	if (Value != 0.0f)
	{
		Camera->MoveRight(Value / 1000.0f);
	}
}


void CTestPlayer::MoveUp(float Value)
{
	if (Value != 0.0f)
	{
		Camera->MoveUp(Value / 1000.0f);
	}
}