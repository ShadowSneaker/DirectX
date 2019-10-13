#include "SphereCollider.h"
#include "BoxCollider.h"
#include "CylinderCollider.h"
#include "CapsuleCollider.h"
#include "PolygonCollider.h"


CPolygonCollider::CPolygonCollider()
	:CCollider::CCollider{}
{

}


CPolygonCollider::CPolygonCollider(class CWorldObject* InOwner, STransform InTransform)
	:CCollider::CCollider{ InOwner, InTransform }
{

}


bool CPolygonCollider::CheckCollision(const CCollider* Other) const
{
	return Other->CheckCollision(this);
}


bool CPolygonCollider::CheckCollision(const CSphereCollider* Other) const
{
	return false;
}


bool CPolygonCollider::CheckCollision(const CBoxCollider* Other) const
{
	return false;
}


bool CPolygonCollider::CheckCollision(const CCylinderCollider* Other) const
{
	return false;
}


bool CPolygonCollider::CheckCollision(const CCapsuleCollider* Other) const
{
	return false;
}


bool CPolygonCollider::CheckCollision(const CPolygonCollider* Other) const
{
	return false;
}


void CPolygonCollider::DrawDebug() const
{

}