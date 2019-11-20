#include "PolygonComponent.h"
#include "../../Math/Physics/Physics.h"


CPolygonComponent::CPolygonComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CPolygon::CPolygon{}
{
	GetPhysics()->AddCollider(this);
	CPolygon::Owner = CComponent::GetOwner();
}


CPolygonComponent::~CPolygonComponent()
{
	GetPhysics()->RemoveCollider(this);
}