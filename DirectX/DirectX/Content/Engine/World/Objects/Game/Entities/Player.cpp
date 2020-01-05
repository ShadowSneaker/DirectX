#define USE_LEGACY_CONTROLS

#include "Player.h"
#include "../../../../Components/Graphics/Camera/CameraComponent.h"
#include "../../../../Components/CharacterComponent.h"
#include "../../../../Components/Graphics/Meshes/StaticMeshComponent.h"
#include "../../../../Components/Physics/BoxComponent.h"
//#include "../../../World.h"
#include "../../../../Graphics/Renderer.h"
#include "../../../../Font/Font.h"

#include <string.h>


CPlayer::CPlayer(SObjectBase Base)
	:CEntity::CEntity{ Base }
{
	//Mesh->SetMesh("Sphere.obj");
	Mesh->SetShader("Shaders.hlsl");
	BoxCollider->SetVertices(&Mesh->Vertices);

	Transform.Scale = 0.5f;

	SetupInput(GetInputManager());
	Camera = CreateComponent<CCameraComponent>();
	Camera->Transform.Location = SVector{ 0.0f, 0.0f, -10.0f };
	GetRenderer()->SetCamera(Camera);

	ScoreText = GetRenderer()->GetScoreText();
	UpdateScore();

	CharacterComponent->RunSpeed = 10.0f;
	CharacterComponent->GravityScale = 1.0f;
	
}


CPlayer::~CPlayer()
{
}


void CPlayer::SetupInput(CInputManager* Input)
{
	Input->BindAxis("MoveForward", EKey::IE_W, std::bind(&CPlayer::MoveForward, this, std::placeholders::_1));
	Input->BindAxis("MoveForward", EKey::IE_S, -1.0f);
	Input->BindAxis("MoveSideways", EKey::IE_D, std::bind(&CPlayer::MoveSideways, this, std::placeholders::_1));
	Input->BindAxis("MoveSideways", EKey::IE_A, -1.0f);

	Input->BindAxis("Turn", EKey::IE_Right, std::bind(&CPlayer::Turn, this, std::placeholders::_1));
	Input->BindAxis("Turn", EKey::IE_Left, -1.0f);

	Input->BindAction("Jump", EInputMode::Pressed, EKey::IE_Space, std::bind(&CPlayer::Jump, this, std::placeholders::_1));
}


void CPlayer::Begin()
{
	Transform.Location[Y] = 1.0f;
}


void CPlayer::Update()
{
	CEntity::Update();
	Camera->Transform.Location = Transform.Location;
}


void CPlayer::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		CharacterComponent->Move(Camera->GetForward(), Value);
		//Transform.Location += SVector::Forward() * 4.0f * Value * TTime::DeltaTime;
	}
}


void CPlayer::MoveSideways(float Value)
{
	if (Value != 0.0f)
	{
		// Based off testing, I think the problem I have with my camera is not so much to do with the camera, but the math involved.
		// Currently I am rotating the player instead of the camera, and that visually looks correct. The world rotates around the player correctly.
		// However, doing this messes up the Transform.Right() and transform.Forward() functions. I Should look at those functions to possibly fix this.
		// For now, I recommend just replacing Transform.Right() and transform.Forward() to use the cross product using SVector::Up().

		CharacterComponent->Move(Camera->GetRight(), Value);
	}
}


void CPlayer::Turn(float Value)
{
	if (Value != 0.0f)
	{
		Camera->Rotate(0.0f, RotationSpeed * Value * TTime::DeltaTime, 0.0f);
	}
}


void CPlayer::Jump(EInputMode InputMode)
{
	CharacterComponent->Jump();
}


void CPlayer::UpdateScore()
{
	ScoreText->SetText("Score " + std::to_string(Score));
}


void CPlayer::AddPoints(uint Amount)
{
	Score += Amount;
	UpdateScore();
}