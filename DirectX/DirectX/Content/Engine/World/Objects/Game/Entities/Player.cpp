#define USE_LEGACY_CONTROLS

#include "Player.h"
#include "../../../../Components/Graphics/Camera/CameraComponent.h"
#include "../../../../Components/CharacterComponent.h"
#include "../../../../Components/Graphics/Meshes/StaticMeshComponent.h"
//#include "../../../World.h"
#include "../../../../Graphics/Renderer.h"
#include "../../../../Font/Font.h"

#include <string.h>


CPlayer::CPlayer(SObjectBase Base)
	:CEntity::CEntity{ Base }
{
	//Mesh->SetMesh("Sphere.obj");
	Transform.Scale = 0.5f;

	SetupInput(GetInputManager());
	Camera = CreateComponent<CCameraComponent>();
	Camera->Transform.Location = SVector{ 0.0f, 0.0f, -10.0f };
	GetRenderer()->SetCamera(Camera);
	CameraOffset = SVector2{ 0.0f, 1.0f };

	Camera->Transform.Location += CameraOffset;

	ScoreText = GetRenderer()->GetScoreText();
	UpdateScore();

	CharacterComponent->MoveSpeed = 75.0f;
	Camera->UseLegacyControls = true;

	
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
}


void CPlayer::Begin()
{
	
}


void CPlayer::Update()
{
	if (!Camera->Transform.Location.NearlyEqual(Transform.Location, 0.0001f)) 
	{
		SVector Location{ Camera->Transform.Location };
		Location[X] = TMath::Lerp(Location[X], Transform.Location[X] + CameraOffset[X], CamLerpSpeed * TTime::DeltaTime);
		Location[Y] = TMath::Lerp(Location[Y], Transform.Location[Y] + CameraOffset[Y], CamLerpSpeed * TTime::DeltaTime);
		Camera->Transform.Location = Location;
	}
}


void CPlayer::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		CharacterComponent->Move(SVector::Up(), Value);
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

		CharacterComponent->Move(SVector::Right(), Value);
	}
}


void CPlayer::UpdateScore()
{
	ScoreText->SetText("Score " + std::to_string(Score));
}