#include "TestMove.h"
#include "../../../Components/Colliders/SphereComponent.h"
#include "../../../Components/Graphics/Meshes/StaticMeshComponent.h"
#include "../../../Math/Physics/Physics.h"


CTestMove::CTestMove(SObjectBase Base)
	:CCharacter::CCharacter{ Base }
{
	SphereCollider = CreateComponent<CSphereComponent>();
	SphereCollider->SetOwner(this);
	SphereCollider->Transform.SetParent(&Transform);
	SphereCollider->Radius = 0.75f;

	Mesh = CreateComponent<CStaticMeshComponent>();
	Mesh->SetMesh("Sphere.obj");
	Mesh->SetShader("Shaders.hlsl");
	Mesh->Transform.Scale = 0.25f;
	Mesh->Transform.SetParent(&Transform);

	SetupInput(GetInputManager());
}


void CTestMove::SetupInput(CInputManager* Input)
{
#ifndef INPUT_ENABLED
	Input->BindAxis("AAA", EKey::IE_I, std::bind(&CTestMove::TMoveForward, this, std::placeholders::_1));
	Input->BindAxis("AAA", EKey::IE_K, -1.0f);

	Input->BindAxis("BBB", EKey::IE_J, std::bind(&CTestMove::TMoveSideways, this, std::placeholders::_1));
	Input->BindAxis("BBB", EKey::IE_L, -1.0f);
#endif
}


void CTestMove::TMoveForward(float Value)
{
	if (Value != 0.0f && AllowMovement)
	{
		Transform.Location[X] += Value * 0.01f;
		
		THitInfoList Info = GetPhysics()->QuerryCollisions(SphereCollider);
		for (uint i = 0; i < Info.size(); ++i)
		{
			if (Info[i].Hit)
			{
				Transform.Location[X] -= Value * 0.01f;
				break;
			}
		}

	}
}


void CTestMove::TMoveSideways(float Value)
{
	if (Value != 0.0f && AllowMovement)
	{
		Transform.Location[Z] += Value * 0.01f;

		THitInfoList Info = GetPhysics()->QuerryCollisions(SphereCollider);
		for (uint i = 0; i < Info.size(); ++i)
		{
			if (Info[i].Hit)
			{
				Transform.Location[Z] -= Value * 0.01f;
				break;
			}
		}
	}
}