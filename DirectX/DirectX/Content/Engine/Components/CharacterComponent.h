#pragma once
#include "Component.h"


// The types of movement the character component can use.
enum class EMovementType
{
	Walking,
	Running,
	Sprinting,
	Flying,
	Swimming
};



// A component type that gives first person-like movement and controls to a world object.
class CCharacterComponent :public CComponent
{
private:
	/// Properties

	// The speed this object is currently moving at.
	float CurrentSpeed{ 50.0f };

	// The type of movement option this object is currently using.
	EMovementType MovementType{ EMovementType::Running };

	// The velocity this charater is moving at.
	SVector Velocity{ 0.0f };

	// Determines if this character is standing on a surface.
	bool OnGround{ false };

public:
	// The collider attached to this object.
	class CCollider* Collider;

	// How high this character jumps.
	float JumpStrength = 5.0f;

	

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

	// Determines how much this character floats in water.
	float Buoyancy{ 0.8f };


public:
	/// Constructors

	// Constructor, Default.
	CCharacterComponent(SComponentInfo Info);


	
	/// Overridables

	// Used to apply gravity onto the character.
	virtual void Update() override;

	
	
	/// Fuctions

	// Moves this character in a direction.
	// @param Direction - The normalized direction to move in.
	// @param - The strength of the movement.
	// @param ForceMove - If true, ignores the collision checks.
	void Move(SVector Direction, float Axis, bool ForceMove = false);

	// Launches the character up in the air.
	void Jump();



	/// Setters

	// Sets the type of movement this character uses.
	void SetMovementMode(EMovementType Mode);



	/// Getters

	// Returns the speed this character is currently moving at.
	INLINE float GetCurrentSpeed() const { return CurrentSpeed; }
};