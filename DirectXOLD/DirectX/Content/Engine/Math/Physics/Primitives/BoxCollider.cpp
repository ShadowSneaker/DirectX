#include "SphereCollider.h"
#include "BoxCollider.h"
#include "CylinderCollider.h"
#include "CapsuleCollider.h"
#include "PolygonCollider.h"


CBoxCollider::CBoxCollider()
	:CCollider::CCollider{}
{

}


CBoxCollider::CBoxCollider(class CWorldObject* InOwner, STransform InTransform)
	:CCollider::CCollider{ InOwner, InTransform }
{

}


bool CBoxCollider::CheckCollision(const CCollider* Other) const
{
	return Other->CheckCollision(this);
}


bool CBoxCollider::CheckCollision(const CSphereCollider* Other) const
{
	return false;
}


bool CBoxCollider::CheckCollision(const CBoxCollider* Other) const
{
	return false;
}


bool CBoxCollider::CheckCollision(const CCylinderCollider* Other) const
{
	return false;
}


bool CBoxCollider::CheckCollision(const CCapsuleCollider* Other) const
{
	return false;
}


bool CBoxCollider::CheckCollision(const CPolygonCollider* Other) const
{
	return false;
}


void CBoxCollider::DrawDebug() const
{

}