#include "Gun.h"
#include "../../../ObjectPool.h"
#include "../../../../Components/Graphics/Meshes/StaticMeshComponent.h"
#include "Bullet.h"


CGun::CGun(SObjectBase Base)
	:CWorldObject::CWorldObject{ Base }
{
	Body = CreateComponent<CStaticMeshComponent>();
	Body->SetMesh("Sphere.obj");
	Body->SetShader("Shaders.hlsl");
	//Body->SetTexture("")

	
}


CGun::~CGun()
{
	delete BulletPool;
}


void CGun::Begin()
{
	BulletPool = new CObjectPool(GetWorld());
	BulletPool->AddType<CBullet>("Bullets", ClipSize * 2);

	BulletsRemaining = ClipSize;
}


void CGun::Fire()
{
	if (BulletsRemaining > 0)
	{
		CBullet* Bullet{ BulletPool->CheckoutObject<CBullet>("Bullets") };
		if (Bullet)
		{
			STransform WorldTransform{ Transform.GetWorldTransform() };

			Bullet->Transform = WorldTransform;
		}
	}
}