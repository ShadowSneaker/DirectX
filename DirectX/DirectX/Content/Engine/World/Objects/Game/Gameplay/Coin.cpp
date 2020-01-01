#include "Coin.h"
#include "../../../../Components/Graphics/Meshes/StaticMeshComponent.h"
#include "../../../../Components/Physics/SphereComponent.h"
#include "../Entities/Player.h"
#include "../../../World.h"



CCoin::CCoin(SObjectBase Core)
	:CWorldObject::CWorldObject{ Core }
{
	Mesh = CreateComponent<CStaticMeshComponent>();
	Mesh->SetTexture("SteelRough Albedo.png");
	Mesh->SetMesh("Coin.obj");
	Mesh->SetShader("Shaders.hlsl");
	Mesh->Transform.SetParent(&Transform);

	SphereCollider = CreateComponent<CSphereComponent>();
	SphereCollider->Radius = 0.1f;
	SphereCollider->Transform.SetParent(&Transform);

	SPhysicsBody* Body = GetPhysics()->GetBody(SphereCollider);
	Body->SetEnter(std::bind(&CCoin::CollisionEnter, this, std::placeholders::_1));
}



void CCoin::CollisionEnter(SCollision Collision)
{
	if (Player)
	{
		Player->AddPoints(Value);
		Transform.Location[Y] = -10000;
		//GetWorld()->DeleteObject(this);
	}
}