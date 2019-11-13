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
	return false;
}


bool CPolygon::CheckCollision(const CBox* Other) const
{
	return false;
}


bool CPolygon::CheckCollision(const CAxisAlignedBoundingBox* Other) const
{
	return false;
}


bool CPolygon::CheckCollision(const CPoint* Other) const
{
	return false;
}


bool CPolygon::CheckCollision(const CLine* Other) const
{
	return false;
}


bool CPolygon::CheckCollision(const CCapsule* Other) const
{
	return Other->CheckCollision(this);
}


bool CPolygon::CheckCollision(const CPolygon* Other) const
{
	return false;
}


bool CPolygon::CheckCollision(const CCylinder* Other) const
{
	return false;
}


void CPolygon::UpdateBounds()
{
	ColliderVertices.resize(*VertexCount);
	if (VertexCount)
	{
		for (uint i = 0; i < *VertexCount; ++i)
		{
			ColliderVertices[i] = Vertices[i]->Position;
		}
	}
}