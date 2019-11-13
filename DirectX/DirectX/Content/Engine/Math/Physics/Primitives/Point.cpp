#include "Sphere.h"
#include "Box.h"
#include "AABB.h"
#include "Point.h"
#include "Line.h"
#include "Capsule.h"
#include "Polygon.h"
#include "Cylinder.h"


CPoint::CPoint()
	:CCollider::CCollider{}
{}


CPoint::CPoint(STransform InTransform)
	: CCollider::CCollider{ InTransform }
{}


bool CPoint::CheckCollision(const CCollider* Other) const
{
	return Other->CheckCollision(this);
}


bool CPoint::CheckCollision(const CSphere* Other) const
{
	SVector Distance{ SVector::DistanceSquared(Transform.GetWorldLocation(), Other->Transform.GetWorldLocation()) };
	float Radius{ Other->GetRadius() };
	Radius *= Radius;
	return (Distance < Radius);
}


bool CPoint::CheckCollision(const CBox* Other) const
{
	return false;
}


bool CPoint::CheckCollision(const CAxisAlignedBoundingBox* Other) const
{
	return TMath::Range(Other->GetMinExtents(), Other->GetMaxExtents(), Transform.GetWorldLocation());
}


bool CPoint::CheckCollision(const CPoint* Other) const
{
	return SVector::NearlyEqual(Transform.GetWorldLocation(), Other->Transform.GetWorldLocation(), SMALL_NUMBER);
}


bool CPoint::CheckCollision(const CLine* Other) const
{
	return false;
}


bool CPoint::CheckCollision(const CCapsule* Other) const
{
	return Other->CheckCollision(this);
}


bool CPoint::CheckCollision(const CPolygon* Other) const
{
	return false;
}


bool CPoint::CheckCollision(const CCylinder* Other) const
{
	SVector Position{ Transform.GetWorldLocation() };
	SVector OtherPos{ Other->Transform.GetWorldLocation() };

	// Only continue if the point is within the bottom and top of the cylinder, no need to calculate the rest if it's not.
	float Height{ Other->GetHeight() };
	if (TMath::Range(OtherPos[Y] - Height, OtherPos[Y] + Height, Position[Y]))
	{
		SVectorControl Control{ true, false, true };

		SVector Distance{ SVector::DistanceSquared(SVector::Select(Position, SVector{ 0.0f }, Control), SVector::Select(OtherPos, SVector{ 0.0f }, Control)) };
		float Radius{ Other->GetRadius() };
		Radius *= Radius;

		return (Distance < Radius);
	}
	return false;
}


void CPoint::UpdateBounds()
{}