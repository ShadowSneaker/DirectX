#include "Character.h"
#include "../../Components/CharacterComponent.h"
//#include "../../Components/Graphics/SkeletalMesh.h"
#include "../../Components/Physics/CapsuleComponent.h"


CCharacter::CCharacter(SObjectBase Core)
	:CPuppet::CPuppet{ Core }
{
	//Mesh = CreateComponent<CSkeletalMesh>();

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