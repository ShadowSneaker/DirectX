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
		if (TTime::DeltaTime < 1.0f)
		{
			//SVector NewLocation{ (GetPhysics()->Gravity + Velocity) * TTime::DeltaTime };
			Velocity += GetPhysics()->Gravity * TTime::DeltaTime;
			GetOwner()->Transform.Location += Velocity * TTime::DeltaTime;
			std::vector<SCollision> Collisions{ GetPhysics()->QuerryCollisions(Collider) };
			if (Collisions.size() > 0)
			{
				GetOwner()->Transform.Location -= Velocity * TTime::DeltaTime;
				Velocity[Y] = 0.0f;
				OnGround = true;
			}
		}
	}
}


void CCharacterComponent::Move(SVector Direction, float Axis, bool ForceMove)
{
	SVector Location{ Direction * CurrentSpeed * Axis * TTime::DeltaTime };

	if (!ForceMove)
	{
		GetOwner()->Transform.Location += Location;
		std::vector<SCollision> Collisions{ GetPhysics()->QuerryCollisions(Collider)};
		if (Collisions.size() > 0)
		{
			GetOwner()->Transform.Location -= Location;
		}
	}
	else
	{
		GetOwner()->Transform.Location += Location;
	}

}



void CCharacterComponent::Jump()
{
	if (OnGround)
	{
		Velocity[Y] = JumpStrength;
		OnGround = false;
	}
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