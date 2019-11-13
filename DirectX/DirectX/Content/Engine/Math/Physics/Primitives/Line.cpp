#include "Sphere.h"
#include "Box.h"
#include "AABB.h"
#include "Point.h"
#include "Line.h"
#include "Capsule.h"
#include "Polygon.h"
#include "Cylinder.h"


CLine::CLine()
	:CCollider::CCollider{}
{}


CLine::CLine(STransform InTransform)
	: CCollider::CCollider{ InTransform }
{}


CLine::CLine(STransform InTransform, SVector EndPos)
	: CCollider::CCollider{ InTransform }, EndPosition{ EndPos }
{}


bool CLine::CheckCollision(const CCollider* Other) const
{
	return Other->CheckCollision(this);
}


bool CLine::CheckCollision(const CSphere* Other) const
{
	return false;
}


bool CLine::CheckCollision(const CBox* Other) const
{
	return false;
}


bool CLine::CheckCollision(const CAxisAlignedBoundingBox* Other) const
{
	return false;
}


bool CLine::CheckCollision(const CPoint* Other) const
{
	return false;
}


bool CLine::CheckCollision(const CLine* Other) const
{
	return false;
}


bool CLine::CheckCollision(const CCapsule* Other) const
{
	return Other->CheckCollision(this);
}


bool CLine::CheckCollision(const CPolygon* Other) const
{
	return false;
}


bool CLine::CheckCollision(const CCylinder* Other) const
{
	return false;
}


void CLine::UpdateBounds()
{}