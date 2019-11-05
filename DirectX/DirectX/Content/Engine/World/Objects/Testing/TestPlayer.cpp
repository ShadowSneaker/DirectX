#include "TestPlayer.h"
#include "../../../Components/Graphics/Camera/CameraComponent.h"
#include "../../../Core/Systems/InputManager.h"
#include "../../../Graphics/Renderer.h"


CTestPlayer::CTestPlayer(SObjectBase Core)
	:CCharacter::CCharacter{ Core }
{
	SetupInput(GetInputManager());
	Camera = CreateComponent<CCameraComponent>();
	Camera->Transform.SetParent(&Transform);
}


CTestPlayer::~CTestPlayer()
{
}


void CTestPlayer::SetupInput(CInputManager* Input)
{
	Input->BindAxis("MoveForward", EKey::IE_W, std::bind(&CTestPlayer::MoveForward, this, std::placeholders::_1));
	Input->BindAxis("MoveForward", EKey::IE_S, -1.0f);
	Input->BindAxis("MoveSideways", EKey::IE_D, std::bind(&CTestPlayer::MoveSideways, this, std::placeholders::_1));
	Input->BindAxis("MoveSideways", EKey::IE_A, -1.0f);
	Input->BindAxis("MoveUp", EKey::IE_E, std::bind(&CTestPlayer::MoveUp, this, std::placeholders::_1));
	Input->BindAxis("MoveUp", EKey::IE_Q, -1.0f);

	Input->BindAxis("Turn", EKey::IE_Right, std::bind(&CTestPlayer::Turn, this, std::placeholders::_1));
	Input->BindAxis("Turn", EKey::IE_Left, -1.0f);
}


void CTestPlayer::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		Camera->MoveForward(Value / 100.0f);
	}
}


void CTestPlayer::MoveSideways(float Value)
{
	if (Value != 0.0f)
	{
		Camera->MoveRight(Value / 100.0f);
	}
}


void CTestPlayer::MoveUp(float Value)
{
	if (Value != 0.0f)
	{
		Camera->MoveUp(Value / 100.0f);
	}
}


void CTestPlayer::Turn(float Value)
{
	if (Value != 0.0f)
	{
		Camera->Rotate(TO_RADIAN(Value / 10.0f));
	}
}