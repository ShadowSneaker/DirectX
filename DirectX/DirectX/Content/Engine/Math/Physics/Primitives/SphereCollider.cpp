#include "SphereCollider.h"
#include "BoxCollider.h"
#include "CylinderCollider.h"
#include "CapsuleCollider.h"
#include "PolygonCollider.h"


CSphereCollider::CSphereCollider()
	:CCollider::CCollider{}
{

}


CSphereCollider::CSphereCollider(class CWorldObject* InOwner, STransform InTransform)
	:CCollider::CCollider{ InOwner, InTransform }
{

}


bool CSphereCollider::CheckCollision(const CCollider* Other) const
{
	return Other->CheckCollision(this);
}


bool CSphereCollider::CheckCollision(const CSphereCollider* Other) const
{
	SVector WorldLocation{ Transform.GetWorldLocation() };
	SVector OtherLocation{ Other->Transform.GetWorldLocation() };

	float Radi{ GetRadius() + Other->GetRadius() };
	Radi *= Radi;

	return (Radi < SVector::Distance(WorldLocation, OtherLocation));
}


bool CSphereCollider::CheckCollision(const CBoxCollider* Other) const
{
	return false;
}


bool CSphereCollider::CheckCollision(const CCylinderCollider* Other) const
{
	return false;
}


bool CSphereCollider::CheckCollision(const CCapsuleCollider* Other) const
{
	return false;
}


bool CSphereCollider::CheckCollision(const CPolygonCollider* Other) const
{
	return false;
}


void CSphereCollider::DrawDebug() const
{

}