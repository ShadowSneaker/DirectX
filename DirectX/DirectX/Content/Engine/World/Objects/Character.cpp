#include "Character.h"
#include "../../Components/CharacterComponent.h"
//#include "../../Components/Graphics/SkeletalMesh.h"
#include "../../Components/Graphics/Meshes/StaticMeshComponent.h"
#include "../../Components/Physics/CapsuleComponent.h"


CCharacter::CCharacter(SObjectBase Core)
	:CPuppet::CPuppet{ Core }
{
	Mesh = CreateComponent<CStaticMeshComponent>();
	Mesh->SetMesh("Cube.obj");
	Mesh->SetShader("Shaders.hlsl");
	Mesh->Transform.SetParent(&Transform);

	CharacterComponent = CreateComponent<CCharacterComponent>();
	//CapsuleCollider = CreateComponent<CCapsuleComponent>();
}


CCharacter::~CCharacter()
{
	CPuppet::~CPuppet();
}


void CCharacter::Update()
{
	CPuppet::Update();
}