#include "PolygonComponent.h"
#include "../../Math/Physics/Physics.h"


CPolygonComponent::CPolygonComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CPolygonCollider::CPolygonCollider{}
{
	GetPhysics()->AddCollider(this);
}


CPolygonComponent::~CPolygonComponent()
{
	GetPhysics()->RemoveCollider(this);
}