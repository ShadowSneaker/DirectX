#include "Sphere.h"
#include "Box.h"
#include "AABB.h"
#include "Point.h"
#include "Line.h"
#include "Capsule.h"
#include "Polygon.h"
#include "Cylinder.h"


CSphere::CSphere()
	:CCollider::CCollider{}
{}


CSphere::CSphere(STransform InTransform)
	: CCollider::CCollider{ InTransform }
{}


CSphere::CSphere(STransform InTransform, float InRadius)
	: CCollider::CCollider{ InTransform }, Radius{ InRadius }
{}



bool CSphere::CheckCollision(const CCollider* Other) const
{
	return Other->CheckCollision(this);
}


bool CSphere::CheckCollision(const CSphere* Other) const
{
	SVector Position{ Transform.GetWorldLocation() };
	SVector OtherPos{ Other->Transform.GetWorldLocation() };

	float Radi{ GetRadius() + Other->GetRadius() };
	Radi *= Radi;

	return (Radi > SVector::DistanceSquared(Position, OtherPos));
}


bool CSphere::CheckCollision(const CBox* Other) const
{
#ifdef USE_FAST_CHECK_WHERE_POSSIBLE
	// Check if fast check is possible.
	if (SVector::NearlyEqual(Transform.Up(), SVector::Up(), SMALL_NUMBER))
	{
		SVector BoxMin{ Other->GetMinExtents() };
		SVector BoxMax{ Other->GetMaxExtents() };
		SVector SpherePos{ Transform.GetWorldLocation() };
		SVector Max{ SVector::Max(BoxMin, SVector::Min(SpherePos, BoxMax)) };
		float Distance{ SVector::DistanceSquared(Max, SpherePos) };
		float Radi{ GetRadius() };
		Radi *= Radi;

		return Distance < Radi;
	}
#endif

	// Slow Check.
	return SATCollision(Other);
}


bool CSphere::CheckCollision(const CAxisAlignedBoundingBox* Other) const
{
	SVector BoxMin{ Other->GetMinExtents() };
	SVector BoxMax{ Other->GetMaxExtents() };
	SVector SpherePos{ Transform.GetWorldLocation() };
	SVector Max{ SVector::Max(BoxMin, SVector::Min(SpherePos, BoxMax)) };
	float Distance{ SVector::DistanceSquared(Max, SpherePos) };
	float Radi{ GetRadius() };
	Radi *= Radi;

	return Distance < Radi;
}


bool CSphere::CheckCollision(const CPoint* Other) const
{
	SVector Distance{ SVector::DistanceSquared(Transform.GetWorldLocation(), Other->Transform.GetWorldLocation()) };
	float Radius{ GetRadius() };
	Radius *= Radius;
	return (Distance < Radius);
}


bool CSphere::CheckCollision(const CLine* Other) const
{

	return false;
}


bool CSphere::CheckCollision(const CCapsule* Other) const
{
	return Other->CheckCollision(this);
}


bool CSphere::CheckCollision(const CPolygon* Other) const
{
	return SATCollision(Other);
}


bool CSphere::CheckCollision(const CCylinder* Other) const
{
#ifdef USE_FAST_CHECK_WHERE_POSSIBLE
	// Check if fast check is possible.
	if (SVector::NearlyEqual(Transform.Up(), SVector::Up(), SMALL_NUMBER))
	{


		//return false;
	}
#endif

	// Slow Check.
	return SATCollision(Other);
}


void CSphere::UpdateBounds()
{
	if (Vertices && Vertices->size() > 0)
	{
		SVector Center{ GetCenter() };
		Transform.Location = Center;

		float Distance{ 0.0f };

		for (uint i = 0; i < Vertices->size(); ++i)
		{
			SVector Temp = Vertices->at(i).Position;
			Distance = TMath::Max(Distance, SVector::DistanceSquared(Center, Vertices->at(i).Position));
		}
		Radius = TMath::Sqrt(Distance) / 4.0f;
	}
}