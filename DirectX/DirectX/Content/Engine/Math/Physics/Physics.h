#pragma once

#ifndef WORLD
#define WORLD
#endif // !WORLD

#define MC_PHYSICS

#include "Collider.h"
#include "RigidBody.h"

#include <functional>
#include <thread>
#include <mutex>




// The information used for when a collision occures.
struct SCollision
{
	// A reference to the hit collider.
	CCollider* Collider;
};


// TODO:
// There are still 2 problems I see with this struct.
// A: There is no way of knowing if this object has exited a collision.
// B: There is no way of knowing if this object has entered a second collision (entering a collision while already colliding with an object).
// A way to fix B: is to remove the Colliding and alway throw a collision flag, but this makes OnStay useless.
// The best way I can think of is to store a list of objects that this collider is colliding with, and if one needs to be removed, call OnExit.
// If it stays in contact with an object then call OnStay. And if it creates a new element, call OnEnter.
struct SPhysicsBody
{
private:
	/// Properties

	// The function to call when the collision enters.
	std::function<void(SCollision)> OnEnter{ NULL };

	// The function to call when the collision exists.
	std::function<void(SCollision)> OnExit{ NULL };

	// The function to call when the collision stays.
	std::function<void(SCollision)> OnStay{ NULL };

	// A list of objects that this body is colliding with.
	std::vector<CCollider*> CollidingObjects;


public:

	// A reference to the Collider of this body.
	CCollider* Collider{ nullptr };

	// A reference to the rigid body of this body.
	CRigidbody* Rigidbody{ nullptr };



public:
	/// Constructors.

	// Constructor, Default.
	SPhysicsBody()
	{}

	// Destructor.
	~SPhysicsBody()
	{
		delete Collider;
		if (Rigidbody) delete Rigidbody;
	}


	/// Functions.

	// Updates the collision state of this body and calls the corosponding collision function.
	// @param State - The new state of the body.
	// @param Other - The collision info.
	void UpdateState(bool State, SCollision Other)
	{
		if (State)
		{
			if (Add(Other.Collider))
			{
				Enter(Other);
			}
			else
			{
				Stay(Other);
			}
		}
		else
		{
			if (Remove(Other.Collider)) Exit(Other);
		}
	}

	// Adds a collider type to the list of colliding objects.
	// @return - Returns true if the collider was added.
	INLINE bool Add(CCollider* Collider)
	{
		if (Collider)
		{
			for (uint i = 0; i < CollidingObjects.size(); ++i)
			{
				if (CollidingObjects[i] == Collider)
				{
					return false;
				}
			}
			CollidingObjects.push_back(Collider);
			return true;
		}
		return false;
	}

	// Removes a collider type from the list of colliding objects.
	INLINE bool Remove(CCollider* Collider)
	{
		if (Collider)
		{
			for (uint i = 0; i < CollidingObjects.size(); ++i)
			{
				if (CollidingObjects[i] == Collider)
				{
					CollidingObjects.erase(CollidingObjects.begin() + i);
				}
			}
			return false;
		}
	}

	// Invokes the OnCollisionEnter function.
	INLINE void Enter(SCollision Other) const { if (OnEnter) OnEnter(Other); }

	// Invokes the OnCollisionExit function.
	INLINE void Exit(SCollision Other) const { if (OnExit) OnExit(Other); }

	// Invokes the OnCollisionStay function.
	INLINE void Stay(SCollision Other) const { if (OnStay) OnStay(Other); }


	/// Setters

	// Sets the OnCollisionEnter function.
	INLINE void SetEnter(std::function<void(SCollision)> Delegate) { OnEnter = Delegate; }

	// Sets the OnCollisionExit function.
	INLINE void SetExit(std::function<void(SCollision)> Delegate) { OnExit = Delegate; }

	// Sets the OnCollisionStay function.
	INLINE void SetStay(std::function<void(SCollision)> Delegate) { OnStay = Delegate; }


	/// Getters

	// Returns true if this physics body is colliding with any objects.
	INLINE bool IsCollidingAny() const { return !CollidingObjects.empty(); }

	// Returns true if this physics body is colliding with an inputted collider.
	INLINE bool IsColliding(CCollider* Collider)
	{
		for (uint i = 0; i < CollidingObjects.size(); ++i)
		{
			if (CollidingObjects[i] == Collider)
			{
				return true;
			}
		}
	}
};




// Handles physics simulations and collision detections between all physics bodies stored within it.
class CPhysics
{
private:
	// A list of all the physics bodies to simulate.
	std::vector<SPhysicsBody*> Bodies;

	// A list of objects that needs to be put into the physics engine.
	std::vector<SPhysicsBody*> InputQueue;

	// A list of objects that needs to be removed from the engine.
	std::vector<SPhysicsBody*> RemoveQueue;

	// Represents when this object is currently simulating physics.
	bool Simulate{ true };

	// The time it takes to calculate each physics frame.
	float DeltaTime{ 0.0f };

	uint Frequency{ 0 };
	uint Counter{ 0 };

	// Locks the Update function so that only one update can be running on this physics object.
	std::mutex PhysicsMutex;

	// The thread the physics update runs on.
	std::thread PhysicsThread;

public:

	// The direction and strength of gravity.
	SVector Gravity{ 0.0f, -9.81f, 0.0f };


public:
	/// Constructors

	// Constructor, Default.
	CPhysics();

	// Destructor.
	~CPhysics();


	/// Functions

private:
	// Deletes all the physics bodies in this object.
	void DeleteAllBodies();


	// Simulates all stored objects.
	void Update();

	void UpdateList();

	void AddToSimulation(SPhysicsBody* Body);

	void RemoveFromSimulation(SPhysicsBody* Body);

public:
	// Adds a physics body to this object.
	// @param Body - The pre-created physics body to add.
	void AddPhysicsBody(SPhysicsBody* Body);

	// Removes a physics body from this object.
	// @note - This does not delete the reference of the physics body.
	// @param Body - A reference to the physics body to remove.
	void RemovePhysicsBody(SPhysicsBody* Body);

	// Deletes a physics body from memory.
	// @param Body - The body to be deleted.
	void DeletePhysicsBody(SPhysicsBody* Body);

	// Creates a physics body and adds it to this object.
	// @param Collider - Initiates the physics body with this collider.
	// @return - The created physics body object.
	SPhysicsBody* CreatePhysicsBody(CCollider* Collider, CRigidbody* Rigid = nullptr);

	// Creates a physics body and adds an inputted collider to it and adds it to this object.
	// @param Collider - The collider to create a physics body around.
	void AddCollider(CCollider* Collider);

	// Removes a physics body containing an inputted collider from this object.
	// @param Collider - The collider used to find the body to remove.
	void RemoveCollider(CCollider* Collider);

	// Deletes a physics body containing an inputted collider from this object and deletes the collider.
	// @param Collider - The reference to the collider to delete.
	void DeleteCollider(CCollider* Collider);

	// Checks collisions against all colliders against every other collider.
	// @note - This is very performance heavy and should not be ran on Update().
	// @return - A list of all the objects collision results.
	std::vector<SCollision> QuerryAllCollisions() const;

	// Checks if a collider is colliding with an object.
	// @param Collider - The collider to check collisions against.
	// @param IgnoreSelf - Should the collider ignore any other colliders on itself.
	// @return - A list of all the collider's collision results.
	std::vector<SCollision> QuerryCollisions(CCollider* Collider, bool IgnoreSelf = true) const;

	// Sends out a line in a direction and returns the first object it hits.
	// @param Origin - The starting location of the raycast.
	// @param Direction - Where the raycast is pointing.
	// @param Distance - How far the raycast goes.
	// @return - The hit information on the first object hit.
	SHitInfo Raycast(SVector Origin, SVector Direction, float Distance);

#ifdef WORLD
	// Sends out a line in a direction and returns the first object it hits.
	// @param Origin - The starting location of the raycast.
	// @param Direction - Where the raycast is pointing.
	// @param Distance - How far the raycast goes.
	// @param IgnoreObjects - A list of objects this raycast ignores.
	// @return - The hit information on the first object hit.
	SHitInfo Raycast(SVector StartPosition, SVector Direction, float Distance, std::vector<class CWorldObject*> IgnoreObjects);
#endif

	// Sends out a line in a direction and returns the first object it hits.
	// @param Origin - The starting location of the raycast.
	// @param Direction - Where the raycast is pointing.
	// @param Distance - How far the raycast goes.
	// @param HitInfo - Used to get the results of the raycast.
	// @return - The hit information on the first object hit.
	SHitInfo Raycast(SVector Origin, SVector Direction, float Distance, SHitInfo& HitInfo);

#ifdef WORLD
	// Sends out a line in a direction and returns the first object it hits.
	// @param Origin - The starting location of the raycast.
	// @param Direction - Where the raycast is pointing.
	// @param Distance - How far the raycast goes.
	// @param IgnoreObjects - A list of objects this raycast ignores.
	// @param HitInfo - Used to get the results of the raycast.
	// @return - The hit information on the first object hit.
	SHitInfo Raycast(SVector StartPosition, SVector Direction, float Distance, std::vector<class CWorldObject*> IgnoreObjects, SHitInfo& HitInfo);
#endif

	// Sends out a line in a direction and returns all objects hit.
	// @param Origin - The starting location of the raycast.
	// @param Direction - Where the raycast is pointing.
	// @param Distance - How far the raycast goes.
	// @return - The hit information on the first object hit.
	std::vector<SHitInfo> RaycastMulti(SVector Origin, SVector Direction, float Distance);

#ifdef WORLD
	// Sends out a line in a direction and returns all objects hit.
	// @param Origin - The starting location of the raycast.
	// @param Direction - Where the raycast is pointing.
	// @param Distance - How far the raycast goes.
	// @param IgnoreObjects - A list of objects this raycast ignores.
	// @return - The hit information on the first object hit.
	std::vector<SHitInfo> RaycastMulti(SVector Origin, SVector Direction, float Distance, std::vector<class CWorldObject*> IgnoreObjects);
#endif

	// Sends out a line in a direction and returns all objects hit.
	// @param Origin - The starting location of the raycast.
	// @param Direction - Where the raycast is pointing.
	// @param Distance - How far the raycast goes.
	// @param HitInfo - Used to get the results of the raycast.
	// @return - The hit information on the first object hit.
	std::vector<SHitInfo> RaycastMulti(SVector Origin, SVector Direction, float Distance, std::vector<SHitInfo>& HitInfo);

#ifdef WORLD
	// Sends out a line in a direction and returns all objects hit.
	// @param Origin - The starting location of the raycast.
	// @param Direction - Where the raycast is pointing.
	// @param Distance - How far the raycast goes.
	// @param IgnoreObjects - A list of objects this raycast ignores.
	// @param HitInfo - Used to get the results of the raycast.
	// @return - The hit information on the first object hit.
	std::vector<SHitInfo> RaycastMulti(SVector Origin, SVector Direction, float Distance, std::vector<class CWorldObject*> IgnoreObjects, std::vector<SHitInfo>& HitInfo);
#endif

	// Creates a line and checks to see if it is colliding with anything.
	// @param StartPosition - The location this linecast starts at.
	// @param EndPosition - The location this linecast ends at.
	// @return - Returns true if this line intersects with anything.
	bool Linecast(SVector StartPosition, SVector EndPosition);

#ifdef WORLD
	// Creates a line and checks to see if it is colliding with anything.
	// @param StartPosition - The location this linecast starts at.
	// @param EndPosition - The location this linecast ends at.
	// @param IgnoreObjects - A list of objects this linecast ignores.
	// @return - Returns true if this line intersects with anything.
	bool Linecast(SVector StartPosition, SVector EndPosition, std::vector<class CWorldObject*> IgnoreObjects);
#endif

	// Creates a line and checks to see if it is colliding with anything.
	// @param StartPosition - The location this linecast starts at.
	// @param EndPosition - The location this linecast ends at.
	// @param HitInfo - A list of hit results from this linecast.
	// @return - Returns true if this line intersects with anything.
	bool Linecast(SVector StartPosition, SVector EndPosition, std::vector<SHitInfo>& HitInfo);

#ifdef WORLD
	// Creates a line and checks to see if it is colliding with anything.
	// @param StartPosition - The location this linecast starts at.
	// @param EndPosition - The location this linecast ends at.
	// @param IgnoreObjects - A list of objects this linecast ignores.
	// @param HitInfo - A list of hit results from this linecast.
	// @return - Returns true if this line intersects with anything.
	bool Linecast(SVector StartPosition, SVector EndPosition, std::vector<class CWorldObject*> IgnoreObjects, std::vector<SHitInfo>& HitInfo);
#endif


	/// Setters


	/// Getters

	// Returns the physics body the inputted collider is attached to.
	SPhysicsBody* GetBody(CCollider* Collider) const;

	// Returns the physics body the inputted rigid body is attached to. 
	SPhysicsBody* GetBody(CRigidbody* Rigid) const;
};