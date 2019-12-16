#define USE_LEGACY_CONTROLS

#include "Player.h"
#include "../../../../Components/Graphics/Camera/CameraComponent.h"
#include "../../../../Components/CharacterComponent.h"
#include "../Weapons/Gun.h"
#include "../../../World.h"
#include "../../../../Graphics/Renderer.h"
#include "../../../../Font/Font.h"

#include <string.h>


CPlayer::CPlayer(SObjectBase Base)
	:CEntity::CEntity{ Base }
{
	SetupInput(GetInputManager());
	Camera = CreateComponent<CCameraComponent>();
	Camera->Transform.SetParent(&Transform);
	Camera->Transform.Location = SVector{ 0.0f, 0.0f, -5.0f };

	GetRenderer()->SetCamera(Camera);
	ScoreText = GetRenderer()->GetScoreText();
	UpdateScore();

	CharacterComponent->MoveSpeed = 5.0f;

	//Gun = new CGun{ Base };
	//Gun->Transform.SetParent(&Transform);
	//Gun->Transform.Location = SVector{ 0.0f, -1.0f, 5.0f };

	
}


CPlayer::~CPlayer()
{
	//GetWorld()->DeleteObject(Gun);
	delete Gun;
}


void CPlayer::SetupInput(CInputManager* Input)
{
	Input->BindAxis("MoveForward", EKey::IE_W, std::bind(&CPlayer::MoveForward, this, std::placeholders::_1));
	Input->BindAxis("MoveForward", EKey::IE_S, -1.0f);
	Input->BindAxis("MoveSideways", EKey::IE_D, std::bind(&CPlayer::MoveSideways, this, std::placeholders::_1));
	Input->BindAxis("MoveSideways", EKey::IE_A, -1.0f);
	Input->BindAxis("MoveUp", EKey::IE_E, std::bind(&CPlayer::MoveUp, this, std::placeholders::_1));
	Input->BindAxis("MoveUp", EKey::IE_Q, -1.0f);
	Input->BindAxis("Turn", EKey::IE_Right, std::bind(&CPlayer::Turn, this, std::placeholders::_1));
	Input->BindAxis("Turn", EKey::IE_Left, -1.0f);

	Input->BindAction("Shoot", EInputMode::Pressed, EKey::IE_F, std::bind(&CPlayer::Shoot, this, std::placeholders::_1));
}


void CPlayer::Begin()
{
	
}


void CPlayer::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		CharacterComponent->Move(Transform.Forward(), Value);
		//Transform.Location += SVector::Forward() * 4.0f * Value * TTime::DeltaTime;
	}
}


void CPlayer::MoveSideways(float Value)
{
	if (Value != 0.0f)
	{
		CharacterComponent->Move(Transform.Right(), Value);
		Transform.Right().Print();
	}
}


void CPlayer::MoveUp(float Value)
{
	if (Value != 0.0f)
	{
		//CharacterComponent->Move(Transform.Up(), Value);
		Transform.Location += SVector::Up() * 4.0f * Value * TTime::DeltaTime;
	}
}


void CPlayer::Turn(float Value)
{
	if (Value != 0.0f)
	{
		Camera->Rotate(0.0f, Value * 5.0f * TTime::DeltaTime, 0.0f);
	}
}


void CPlayer::Shoot(EInputMode InputMode)
{
	Gun->Fire();
}


void CPlayer::UpdateScore()
{
	ScoreText->SetText("Score " + std::to_string(Score));
}