#pragma once
#include "Component.h"


enum class EMovementType
{
	Walking,
	Running,
	Sprinting,
	Flying,
	Swimming
};


class CCharacterComponent :public CComponent
{
private:
	/// Properties

	// The speed this object is currently moving at.
	float CurrentSpeed{ 50.0f };

	// The type of movement option this object is currently using.
	EMovementType MovementType{ EMovementType::Running };

public:
	// The collider attached to this object.
	class CCapsuleComponent* Collider;

	

	// How much this object reacts to gravity.
	float GravityScale{ 1.0f };



	/// Walking Properties

	// The speed this character moves at in the walking state.
	float WalkSpeed{ 40.0f };



	/// Running Properties

	// The speed this character moves at in the running state.
	float RunSpeed{ 50.0f };



	/// Sprinting Properties

	// The speed this character moves at in the sprinting state.
	float SprintSpeed{ 70.0f };



	/// Flying Properties

	// The speed this character moves at in the flying state.
	float FlySpeed{ 50.0f };



	/// Swimming Properties

	// The speed this character moves at in the swimming state.
	float SwimSpeed{ 30.0f };

	// 
	float Buoyancy{ 0.8f };


public:
	/// Constructors

	CCharacterComponent(SComponentInfo Info);


	
	/// Overridables

	// Used to apply gravity onto the character.
	virtual void Update() override;

	
	
	/// Fuctions

	void Move(SVector Direction, float Axis, bool ForceMove = false);

	void Jump();



	/// Setters

	void SetMovementMode(EMovementType Mode);

	/// Getters

	// Returns the speed this character is currently moving at.
	INLINE float GetCurrentSpeed() const { return CurrentSpeed; }
};