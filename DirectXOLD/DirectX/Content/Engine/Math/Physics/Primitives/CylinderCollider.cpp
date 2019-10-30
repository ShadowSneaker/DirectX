#include "SphereCollider.h"
#include "BoxCollider.h"
#include "CylinderCollider.h"
#include "CapsuleCollider.h"
#include "PolygonCollider.h"


CCylinderCollider::CCylinderCollider()
	:CCollider::CCollider{}
{

}


CCylinderCollider::CCylinderCollider(class CWorldObject* InOwner, STransform InTransform)
	:CCollider::CCollider{ InOwner, InTransform }
{

}


bool CCylinderCollider::CheckCollision(const CCollider* Other) const
{
	return Other->CheckCollision(this);
}


bool CCylinderCollider::CheckCollision(const CSphereCollider* Other) const
{
	return false;
}


bool CCylinderCollider::CheckCollision(const CBoxCollider* Other) const
{
	return false;
}


bool CCylinderCollider::CheckCollision(const CCylinderCollider* Other) const
{
	return false;
}


bool CCylinderCollider::CheckCollision(const CCapsuleCollider* Other) const
{
	return false;
}


bool CCylinderCollider::CheckCollision(const CPolygonCollider* Other) const
{
	return false;
}


void CCylinderCollider::DrawDebug() const
{

}