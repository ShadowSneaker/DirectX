#include "CharacterComponent.h"
#include "../World/Objects/WorldObject.h"


CCharacterComponent::CCharacterComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }
{

}


void CCharacterComponent::Move(SVector Direction, float Axis, bool ForceMove)
{
	SVector Location{ Direction * MoveSpeed * Axis * TTime::DeltaTime };

	if (!ForceMove)
	{
		// Do collision check
		// if (Collision)
		//{
		//	Move back the object.
		//	return;
		//}
	}

	GetOwner()->Transform.Location += Location;
}