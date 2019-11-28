#include "TestMove.h"
#include "../../../Components/Physics/SphereComponent.h"
#include "../../../Components/Graphics/Meshes/StaticMeshComponent.h"
#include "../../../Math/Physics/Physics.h"
#include "../../../Components/Physics/RigidbodyComponent.h"


CTestMove::CTestMove(SObjectBase Base)
	:CCharacter::CCharacter{ Base }
{

	Mesh = CreateComponent<CStaticMeshComponent>();
	Mesh->SetMesh("Cube.obj");
	Mesh->SetShader("Shaders.hlsl");
	Mesh->Transform.Scale = 0.05f;
	Mesh->Transform.SetParent(&Transform);
	
	SphereCollider = CreateComponent<CSphereComponent>();
	SphereCollider->SetOwner(this);
	SphereCollider->Transform.SetParent(&Transform);
	SphereCollider->Radius = 0.725f;

	//Rigid = CreateComponent<CRigidbodyComponent>();
	//Rigid->AttachCollider(SphereCollider);

	

	SphereCollider->SetVertices(&Mesh->Vertices);
	SphereCollider->UpdateBounds();

	//SphereCollider->Radius = 100.0f;
	

	SetupInput(GetInputManager());
}


void CTestMove::SetupInput(CInputManager* Input)
{
#ifndef INPUT_ENABLED
	//Input->BindAxis("AAA", EKey::IE_I, std::bind(&CTestMove::TMoveForward, this, std::placeholders::_1));
	//Input->BindAxis("AAA", EKey::IE_K, -1.0f);
	//
	//Input->BindAxis("BBB", EKey::IE_J, std::bind(&CTestMove::TMoveSideways, this, std::placeholders::_1));
	//Input->BindAxis("BBB", EKey::IE_L, -1.0f);
#endif
}


void CTestMove::Update()
{
	Transform.Rotation += TTime::DeltaTime * 1.0f;
}


void CTestMove::TMoveForward(float Value)
{
	if (Value != 0.0f && AllowMovement)
	{
		Transform.Location[X] += Value * TTime::DeltaTime;
		
		std::vector<SCollision> Info = GetPhysics()->QuerryCollisions(SphereCollider);
		for (uint i = 0; i < Info.size(); ++i)
		{
			if (Info[i].Collider)
			{
				Transform.Location[X] -= Value * TTime::DeltaTime;
				break;
			}
		}
	}
}


void CTestMove::TMoveSideways(float Value)
{
	if (Value != 0.0f && AllowMovement)
	{
		Transform.Location[Z] += Value * TTime::DeltaTime;

		std::vector<SCollision> Info = GetPhysics()->QuerryCollisions(SphereCollider);
		for (uint i = 0; i < Info.size(); ++i)
		{
			if (Info[i].Collider)
			{
				Transform.Location[Z] -= Value * TTime::DeltaTime;
				break;
			}
		}
	}
}