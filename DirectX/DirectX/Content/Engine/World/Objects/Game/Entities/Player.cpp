#include "Player.h"
#include "../../../../Components/Graphics/Camera/CameraComponent.h"
#include "../../../../Components/CharacterComponent.h"
#include "../Weapons/Gun.h"
#include "../../../World.h"


CPlayer::CPlayer(SObjectBase Base)
	:CEntity::CEntity{ Base }
{
	SetupInput(GetInputManager());
	Camera = CreateComponent<CCameraComponent>();

	Gun = new CGun{ Base };
	Gun->Transform.SetParent(&Transform);
	Gun->Transform.Location = SVector{ 0.0f, 0.0f, 1.0f };

	
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
	}
}


void CPlayer::MoveSideways(float Value)
{
	if (Value != 0.0f)
	{
		CharacterComponent->Move(Transform.Right(), Value);
	}
}


void CPlayer::Shoot(EInputMode InputMode)
{
	Gun->Fire();
}