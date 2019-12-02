#define USE_LEGACY_CONTROLS


#include "TestPlayer.h"
#include "../../../Components/Graphics/Camera/CameraComponent.h"

#include "../../../Graphics/Renderer.h"
#include "../../World.h"


CTestPlayer::CTestPlayer(SObjectBase Core)
	:CCharacter::CCharacter{ Core }
{
	SetupInput(GetInputManager());
	Camera = CreateComponent<CCameraComponent>();
	Camera->Transform.SetParent(&Transform);

	Camera->UseLegacyControls = true;
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
	Input->BindAxis("LookUp", EKey::IE_Up, std::bind(&CTestPlayer::LookUp, this, std::placeholders::_1));
	Input->BindAxis("LookUp", EKey::IE_Down, -1.0f);

	Input->BindAction("Close", EInputMode::Pressed, EKey::IE_Escape, std::bind(&CTestPlayer::CloseGame, this, std::placeholders::_1));

	Input->BindAction("SpeedUp", EInputMode::Pressed, EKey::IE_LShift, std::bind(&CTestPlayer::SpeedUp, this, std::placeholders::_1));
	Input->BindAction("SpeedUp", EInputMode::Released, EKey::IE_LShift);
}


void CTestPlayer::Update()
{
	//Transform.Rotation.Y += 0.01f;
}


void CTestPlayer::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		Transform.Location += Transform.Forward() * Value * Speed * TTime::DeltaTime;
		//Camera->MoveForward(Value * Speed * TTime::DeltaTime);
	}
}


void CTestPlayer::MoveSideways(float Value)
{
	if (Value != 0.0f)
	{
		Transform.Location += Transform.Right() * Value * Speed * TTime::DeltaTime;
		//Camera->MoveRight(Value * Speed * TTime::DeltaTime);
	}
}


void CTestPlayer::MoveUp(float Value)
{
	if (Value != 0.0f)
	{
		Transform.Location += SVector::Up() * Value * Speed * TTime::DeltaTime;
		//Camera->MoveUp(Value * Speed * TTime::DeltaTime);
	}
}


void CTestPlayer::Turn(float Value)
{
	if (Value != 0.0f)
	{
		//Transform.Rotation.Y += TMath::ToRadians(Value * Speed * 10.0f * TTime::DeltaTime);
		Camera->Rotate(0.0f, TO_RADIAN(Value * Speed * 10.0f * TTime::DeltaTime), 0.0f);
		//Camera->Rotate(0.0f, Value * Speed * TTime::DeltaTime, 0.0f);
	}
}


void CTestPlayer::LookUp(float Value)
{
	if (Value != 0.0f)
	{
		Camera->Rotate(0.0f, 0.0f, Value * Speed * TTime::DeltaTime);
	}
}


void CTestPlayer::CloseGame(EInputMode InputMode)
{
	GetWorld()->Quit();
}


void CTestPlayer::SpeedUp(EInputMode InputMode)
{
	if (InputMode == EInputMode::Pressed)
	{
		Speed = 100.0f;
	}
	else if (InputMode == EInputMode::Released)
	{
		Speed = 500.0f;
	}
}