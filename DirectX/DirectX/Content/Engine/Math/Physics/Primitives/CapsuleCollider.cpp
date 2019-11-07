#include "SphereCollider.h"
#include "BoxCollider.h"
#include "CylinderCollider.h"
#include "CapsuleCollider.h"
#include "PolygonCollider.h"
#include "../../../Graphics/Meshes/StaticMesh.h"


CCapsuleCollider::CCapsuleCollider()
	:CCollider::CCollider{}
{
	Initiate();
}


CCapsuleCollider::CCapsuleCollider(class CStaticMesh* Mesh)
	:CCollider::CCollider{ Mesh }
{

}


CCapsuleCollider::CCapsuleCollider(class CWorldObject* InOwner, STransform InTransform)
	:CCollider::CCollider{ InOwner, InTransform }
{
	Initiate();
}


CCapsuleCollider::~CCapsuleCollider()
{
	delete TopSphere;
	delete BottomSphere;
	delete Body;
}


void CCapsuleCollider::Initiate()
{
	TopSphere = new CSphereCollider{};
	BottomSphere = new CSphereCollider{};
	Body = new CCylinderCollider{};

	TopSphere->Transform.SetParent(&Transform);
	BottomSphere->Transform.SetParent(&Transform);
	Body->Transform.SetParent(&Transform);

	int Y = GetBodyHeight();

	TopSphere->Radius = Radius;
	BottomSphere->Radius = Radius;
	Body->Radius = Radius;
	Body->Height = Y;

	TopSphere->Transform.Location[EAxis::Y] = Y;
	BottomSphere->Transform.Location[EAxis::Y] = -Y;
}


bool CCapsuleCollider::CheckCollision(const CCollider* Other) const
{
	return Other->CheckCollision(this);
}


bool CCapsuleCollider::CheckCollision(const CSphereCollider* Other) const
{
	if (TopSphere->CheckCollision(Other))
	{
		return true;
	}

	if (BottomSphere->CheckCollision(Other))
	{
		return true;
	}

	return Body->CheckCollision(Other);
}


bool CCapsuleCollider::CheckCollision(const CBoxCollider* Other) const
{
	if (TopSphere->CheckCollision(Other))
	{
		return true;
	}

	if (BottomSphere->CheckCollision(Other))
	{
		return true;
	}

	return Body->CheckCollision(Other);
}


bool CCapsuleCollider::CheckCollision(const CCylinderCollider* Other) const
{
	if (TopSphere->CheckCollision(Other))
	{
		return true;
	}

	if (BottomSphere->CheckCollision(Other))
	{
		return true;
	}

	return Body->CheckCollision(Other);
}


bool CCapsuleCollider::CheckCollision(const CCapsuleCollider* Other) const
{
	if (TopSphere->CheckCollision(Other))
	{
		return true;
	}

	if (BottomSphere->CheckCollision(Other))
	{
		return true;
	}

	return Body->CheckCollision(Other);
}


bool CCapsuleCollider::CheckCollision(const CPolygonCollider* Other) const
{
	if (TopSphere->CheckCollision(Other))
	{
		return true;
	}

	if (BottomSphere->CheckCollision(Other))
	{
		return true;
	}

	return Body->CheckCollision(Other);
}


void CCapsuleCollider::DrawDebug() const
{

}