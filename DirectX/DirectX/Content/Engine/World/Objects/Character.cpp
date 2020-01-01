#include "Character.h"
#include "../../Components/CharacterComponent.h"
//#include "../../Components/Graphics/SkeletalMesh.h"
#include "../../Components/Graphics/Meshes/StaticMeshComponent.h"
#include "../../Components/Physics/BoxComponent.h"


CCharacter::CCharacter(SObjectBase Core)
	:CPuppet::CPuppet{ Core }
{
	Mesh = CreateComponent<CStaticMeshComponent>();
	Mesh->SetMesh("Sphere.obj");
	Mesh->SetShader("Shaders.hlsl");
	Mesh->Transform.SetParent(&Transform);

	CharacterComponent = CreateComponent<CCharacterComponent>();
	BoxCollider = CreateComponent<CBoxComponent>();
	BoxCollider->Transform.SetParent(&Transform);
	BoxCollider->SetVertices(&Mesh->Vertices);
	BoxCollider->Extents = SVector{ 1.0f, 2.0f, 1.0f };
	CharacterComponent->Collider = BoxCollider;
}


CCharacter::~CCharacter()
{
	CPuppet::~CPuppet();
}


void CCharacter::Update()
{
	CPuppet::Update();
}