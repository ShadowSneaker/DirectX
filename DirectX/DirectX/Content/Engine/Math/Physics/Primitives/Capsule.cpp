#include "Sphere.h"
#include "Box.h"
#include "AABB.h"
#include "Point.h"
#include "Line.h"
#include "Capsule.h"
#include "Polygon.h"
#include "Cylinder.h"


// TODO:
// Replace the CBox with a CCylider.


CCapsule::CCapsule()
	:CCollider::CCollider{}
{
	InitiateCapsule();
	UpdateCapsule();
}


CCapsule::CCapsule(STransform InTransform)
	:CCollider::CCollider{ InTransform }
{
	InitiateCapsule();
	UpdateCapsule();
}


CCapsule::CCapsule(STransform InTransform, float InRadius, float InHeight)
	:CCollider::CCollider{ InTransform }, Radius{ InRadius }, Height{ InHeight }
{
	InitiateCapsule();
	UpdateCapsule();
}


void CCapsule::InitiateCapsule()
{
	TopSphere = new CSphere{};
	BottomSphere = new CSphere{};
	Body = new CCylinder{};

	TopSphere->Transform.SetParent(&Transform);
	BottomSphere->Transform.SetParent(&Transform);
	Body->Transform.SetParent(&Transform);
}


CCapsule::~CCapsule()
{
	delete TopSphere;
	delete BottomSphere;
	delete Body;
}


bool CCapsule::CheckCollision(const CCollider* Other) const
{
	return Other->CheckCollision(this);
}


bool CCapsule::CheckCollision(const CSphere* Other) const
{
	if (TopSphere->CheckCollision(Other))
	{
		return true;
	}

	if (BottomSphere->CheckCollision(Other))
	{
		return true;
	}

	return (Body->CheckCollision(Other));
}


bool CCapsule::CheckCollision(const CBox* Other) const
{
	if (TopSphere->CheckCollision(Other))
	{
		return true;
	}

	if (BottomSphere->CheckCollision(Other))
	{
		return true;
	}

	return (Body->CheckCollision(Other));
}


bool CCapsule::CheckCollision(const CAxisAlignedBoundingBox* Other) const
{
	if (TopSphere->CheckCollision(Other))
	{
		return true;
	}

	if (BottomSphere->CheckCollision(Other))
	{
		return true;
	}

	return (Body->CheckCollision(Other));
}


bool CCapsule::CheckCollision(const CPoint* Other) const
{
	if (TopSphere->CheckCollision(Other))
	{
		return true;
	}

	if (BottomSphere->CheckCollision(Other))
	{
		return true;
	}

	return (Body->CheckCollision(Other));
}


bool CCapsule::CheckCollision(const CLine* Other) const
{
	if (TopSphere->CheckCollision(Other))
	{
		return true;
	}

	if (BottomSphere->CheckCollision(Other))
	{
		return true;
	}

	return (Body->CheckCollision(Other));
}


bool CCapsule::CheckCollision(const CCapsule* Other) const
{
	if (TopSphere->CheckCollision(Other))
	{
		return true;
	}

	if (BottomSphere->CheckCollision(Other))
	{
		return true;
	}

	return (Body->CheckCollision(Other));
}


bool CCapsule::CheckCollision(const CPolygon* Other) const
{
	if (TopSphere->CheckCollision(Other))
	{
		return true;
	}

	if (BottomSphere->CheckCollision(Other))
	{
		return true;
	}

	return (Body->CheckCollision(Other));
}


bool CCapsule::CheckCollision(const CCylinder* Other) const
{
	if (TopSphere->CheckCollision(Other))
	{
		return true;
	}

	if (BottomSphere->CheckCollision(Other))
	{
		return true;
	}

	return (Body->CheckCollision(Other));
}


void CCapsule::UpdateBounds()
{
	if (VertexCount && *VertexCount > 0)
	{
		SVector Center{ GetCenter() };
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
		UpdateCapsule();
	}
}


void CCapsule::UpdateCapsule()
{
	float BodyHeight{ GetBodyHeight() };

	TopSphere->Radius = Radius;
	BottomSphere->Radius = Radius;
	Body->Radius = Radius;
	Body->Height = BodyHeight;

	TopSphere->Transform.Location[Y] = BodyHeight;
	BottomSphere->Transform.Location[Y] = -BodyHeight;
}