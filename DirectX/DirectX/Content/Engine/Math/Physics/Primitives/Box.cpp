#include "Sphere.h"
#include "Box.h"
#include "AABB.h"
#include "Point.h"
#include "Line.h"
#include "Capsule.h"
#include "Polygon.h"
#include "Cylinder.h"


CBox::CBox()
	:CCollider::CCollider{}
{}


CBox::CBox(STransform InTransform)
	: CCollider::CCollider{ InTransform }
{}


CBox::CBox(STransform InTransform, SVector InExtents)
	: CCollider::CCollider{ InTransform }, Extents{ InExtents }
{}


bool CBox::CheckCollision(const CCollider* Other) const
{
	return Other->CheckCollision(this);
}


bool CBox::CheckCollision(const CSphere* Other) const
{
#ifdef USE_FAST_CHECK_WHERE_POSSIBLE
	// Check if fast check is possible.
	if (SVector::NearlyEqual(Transform.Up(), SVector::Up(), SMALL_NUMBER))
	{
		SVector BoxMin{ GetMinExtents() };
		SVector BoxMax{ GetMaxExtents() };
		SVector SpherePos{ Other->Transform.GetWorldLocation() };
		SVector Max{ SVector::Max(BoxMin, SVector::Min(SpherePos, BoxMax)) };
		float Distance{ SVector::DistanceSquared(Max, SpherePos) };
		float Radi{ Other->GetRadius() };
		Radi *= Radi;

		return Distance < Radi;
	}
#endif

	// Slow Check.
	return SATCollision(Other);
}


bool CBox::CheckCollision(const CBox* Other) const
{
#ifdef USE_FAST_CHECK_WHERE_POSSIBLE
	// Check if fast check is possible.
	if (SVector::NearlyEqual(Transform.Up(), SVector::Up(), SMALL_NUMBER))
	{
		if (SVector::NearlyEqual(Other->Transform.Up(), SVector::Up(), SMALL_NUMBER))
		{

		}
	}
#endif

	// Slow Check.
	return SATCollision(Other);
}


bool CBox::CheckCollision(const CAxisAlignedBoundingBox* Other) const
{
#ifdef USE_FAST_CHECK_WHERE_POSSIBLE
	// Check if fast check is possible.
	if (SVector::NearlyEqual(Transform.Up(), SVector::Up(), SMALL_NUMBER))
	{
		SVector Dist1{ (Other->GetMinExtents() - GetMaxExtents()) };
		SVector Dist2{ (GetMinExtents() - Other->GetMaxExtents()) };

		SVector Distance{ SVector::Max(Dist1, Dist2) };
		float MaxDistance{ Distance.MaxComp() };

		return (MaxDistance < 0.0f);
	}
#endif

	// Slow Check.
	return SATCollision(Other);
}


bool CBox::CheckCollision(const CPoint* Other) const
{
	return false;
}


bool CBox::CheckCollision(const CLine* Other) const
{
	return false;
}


bool CBox::CheckCollision(const CCapsule* Other) const
{
	return Other->CheckCollision(this);
}


bool CBox::CheckCollision(const CPolygon* Other) const
{
	return SATCollision(Other);
}


bool CBox::CheckCollision(const CCylinder* Other) const
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


void CBox::UpdateBounds()
{
	if (Vertices && Vertices->size() > 0)
	{
		SVector Center{ GetCenter() };
		float Distance{ 0.0f };
		uint HighestIndex{ 0 };
		for (uint i = 0; i < Vertices->size(); ++i)
		{
			float Dist{ TMath::Max(Distance, SVector::DistanceSquared(Center, Vertices->at(i).Position)) };
			if (Dist > Distance)
			{
				Distance = Dist;
				HighestIndex = i;
			}
		}
		Extents = Vertices->at(HighestIndex).Position * 2.0f;
	}
}