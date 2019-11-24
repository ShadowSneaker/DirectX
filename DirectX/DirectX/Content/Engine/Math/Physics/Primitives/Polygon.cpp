#include "Sphere.h"
#include "Box.h"
#include "AABB.h"
#include "Point.h"
#include "Line.h"
#include "Capsule.h"
#include "Polygon.h"
#include "Cylinder.h"


CPolygon::CPolygon()
	:CCollider::CCollider{}
{}


CPolygon::CPolygon(STransform InTransform)
	: CCollider::CCollider{ InTransform }
{}


bool CPolygon::CheckCollision(const CCollider* Other) const
{
	return Other->CheckCollision(this);
}


bool CPolygon::CheckCollision(const CSphere* Other) const
{
	return SATCollision(Other);
}


bool CPolygon::CheckCollision(const CBox* Other) const
{
	return SATCollision(Other);
}


bool CPolygon::CheckCollision(const CAxisAlignedBoundingBox* Other) const
{
	return SATCollision(Other);
}


bool CPolygon::CheckCollision(const CPoint* Other) const
{
	return SATCollision(Other);
}


bool CPolygon::CheckCollision(const CLine* Other) const
{
	return SATCollision(Other);
}


bool CPolygon::CheckCollision(const CCapsule* Other) const
{
	return Other->CheckCollision(this);
}


bool CPolygon::CheckCollision(const CPolygon* Other) const
{
	return SATCollision(Other);
}


bool CPolygon::CheckCollision(const CCylinder* Other) const
{
	return SATCollision(Other);
}


void CPolygon::UpdateBounds()
{
	if (Vertices)
	{
		for (uint i = 0; i < Vertices->size(); ++i)
		{
			ColliderVertices[i] = Vertices->at(i).Position;
		}
	}
}