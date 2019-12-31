#include "CharacterComponent.h"
#include "../World/Objects/WorldObject.h"
#include "../Math/Physics/Physics.h"
#include "Physics/CapsuleComponent.h"


CCharacterComponent::CCharacterComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }
{
	Collider = GetOwner()->FindComponent<CCapsuleComponent>();
	SetMovementMode(EMovementType::Running);
}


void CCharacterComponent::Update()
{
	SetMovementMode(MovementType);

	if (Collider)
	{
		SVector NewLocation{ GetPhysics()->Gravity * TTime::DeltaTime };
		GetOwner()->Transform.Location += NewLocation;
		std::vector<SCollision> Collisions{ GetPhysics()->QuerryCollisions(Collider) };
		if (Collisions.size() > 0)
		{
			GetOwner()->Transform.Location -= NewLocation;
		}
	}
}


void CCharacterComponent::Move(SVector Direction, float Axis, bool ForceMove)
{
	SVector Location{ Direction * CurrentSpeed * Axis * TTime::DeltaTime };

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



void CCharacterComponent::Jump()
{

}


void CCharacterComponent::SetMovementMode(EMovementType Mode)
{
	switch (Mode)
	{
	case EMovementType::Walking:
		CurrentSpeed = WalkSpeed;
		break;


	case EMovementType::Running:
		CurrentSpeed = RunSpeed;
		break;


	case EMovementType::Sprinting:
		CurrentSpeed = SprintSpeed;
		break;


	case EMovementType::Flying:
		CurrentSpeed = FlySpeed;
		break;


	case EMovementType::Swimming:
		CurrentSpeed = SwimSpeed;
		break;
	}
}