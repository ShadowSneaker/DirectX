#include "Sphere.h"
#include "Box.h"
#include "AABB.h"
#include "Point.h"
#include "Line.h"
#include "Capsule.h"
#include "Polygon.h"
#include "Cylinder.h"


CCylinder::CCylinder()
	:CCollider::CCollider{}
{}


CCylinder::CCylinder(STransform InTransform)
	: CCollider::CCollider{ InTransform }
{}


CCylinder::CCylinder(STransform InTransform, float InRadius, float InHeight)
	: CCollider::CCollider{ InTransform }, Radius{ InRadius }, Height{ InHeight }
{}


bool CCylinder::CheckCollision(const CCollider* Other) const
{
	return Other->CheckCollision(this);
}


bool CCylinder::CheckCollision(const CSphere* Other) const
{
#ifdef USE_FAST_CHECK_WHERE_POSSIBLE
	// Check if fast check is possible.
	//if (SVector::NearlyEqual(Transform.Up(), SVector::Up(), SMALL_NUMBER))
	//{
	//
	//
	//	return false;
	//}
#endif

	// Slow Check.
	return false;
}


bool CCylinder::CheckCollision(const CBox* Other) const
{
#ifdef USE_FAST_CHECK_WHERE_POSSIBLE
	// Check if fast check is possible.
	//if (SVector::NearlyEqual(Transform.Up(), SVector::Up(), SMALL_NUMBER))
	//{
	//
	//
	//	return false;
	//}
#endif

	// Slow Check.
	return false;
}


bool CCylinder::CheckCollision(const CAxisAlignedBoundingBox* Other) const
{
#ifdef USE_FAST_CHECK_WHERE_POSSIBLE
	// Check if fast check is possible.
	//if (SVector::NearlyEqual(Transform.Up(), SVector::Up(), SMALL_NUMBER))
	//{
	//
	//
	//	return false;
	//}
#endif

	// Slow Check.
	return false;
}


bool CCylinder::CheckCollision(const CPoint* Other) const
{
#ifdef USE_FAST_CHECK_WHERE_POSSIBLE
	// Check if fast check is possible.
	//if (SVector::NearlyEqual(Transform.Up(), SVector::Up(), SMALL_NUMBER))
	//{
	SVector Position{ Transform.GetWorldLocation() };
	SVector OtherPos{ Other->Transform.GetWorldLocation() };

	// Only continue if the point is within the bottom and top of the cylinder, no need to calculate the rest if it's not.
	float ThisHeight{ GetHeight() };
	if (TMath::Range(Position[Y] - ThisHeight, Position[Y] + ThisHeight, OtherPos[Y]))
	{
		SVectorControl Control{ true, false, true };

		SVector Distance{ SVector::DistanceSquared(SVector::Select(Position, SVector{ 0.0f }, Control), SVector::Select(OtherPos, SVector{ 0.0f }, Control)) };
		float Radius{ GetRadius() };
		Radius *= Radius;

		return (Distance < Radius);
	}
	return false;
	//}
#endif

	// Slow check

}


bool CCylinder::CheckCollision(const CLine* Other) const
{

	return false;
}


bool CCylinder::CheckCollision(const CCapsule* Other) const
{
	return Other->CheckCollision(this);
}


bool CCylinder::CheckCollision(const CPolygon* Other) const
{
#ifdef USE_FAST_CHECK_WHERE_POSSIBLE
	// Check if fast check is possible.
	//if (SVector::NearlyEqual(Transform.Up(), SVector::Up(), SMALL_NUMBER))
	//{
	//
	//
	//	return false;
	//}
#endif

	// Slow Check.
	return false;
}


bool CCylinder::CheckCollision(const CCylinder* Other) const
{
#ifdef USE_FAST_CHECK_WHERE_POSSIBLE
	// Check if fast check is possible.
	//if (SVector::NearlyEqual(Transform.Up(), SVector::Up(), SMALL_NUMBER))
	//{
	//
	//
	//	return false;
	//}
#endif

	// Slow Check.
	return false;
}


void CCylinder::UpdateBounds()
{
	if (VertexCount && *VertexCount > 0)
	{
		SVector Center{ GetCenter() };
		Transform.Location = Center;

		SVector Max{ 0.0f };
		SVector Min{ 0.0f };
		for (uint i = 0; i < *VertexCount; ++i)
		{
			Max = SVector::Max(Max, Vertices[i]->Position);
			Min = SVector::Min(Min, Vertices[i]->Position);
		}

		Vector<3, bool> ControlX{ true, false, true };
		Vector<3, bool> ControlY{ false, true, false };

		float DistX{ 0.0f };
		float DistY{ 0.0f };
		for (uint i = 0; i < *VertexCount; ++i)
		{
			DistX = SVector::Distance(Center, SVector::Select(Vertices[i]->Position, Center, ControlX));
			DistY = SVector::Distance(Center, SVector::Select(Vertices[i]->Position, Center, ControlY));
		}

		Radius = DistX;
		Height = DistY;
	}
}