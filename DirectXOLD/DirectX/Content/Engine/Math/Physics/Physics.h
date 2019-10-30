#pragma once
#include "RigidBody.h"

#include <vector>
#include <thread>
#include <mutex>


// A vector of world object pointers.
typedef std::vector<class CWorldObject*> TObjectList;

// A vector of HitInfo.
typedef std::vector<SHitInfo> THitInfoList;


// The core data for storing a collider.
struct SColliderInfo
{
	/// Properties

	// The collider attached to the object.
	CCollider* Collider{ nullptr };

	// The rigid body attached to the object.
	// Note: The rigid body is not required.
	CRigidBody* RigidBody{ nullptr };


	/// Constructors

	// Constructor, Default.
	SColliderInfo()
	{}


	// Constructor, Initiates with a collider.
	// @param InCollider - The reference to the collider.
	SColliderInfo(CCollider* InCollider)
		:Collider{ InCollider }
	{}


	// Constructor, Initiates with a collider and rigid body.
	// @param InCollider - The reference to the collider.
	// @param InRigidBody - The reference to the rigid body.
	SColliderInfo(CCollider* InCollider, CRigidBody* InRigidBody)
		:Collider{ InCollider }, RigidBody{ InRigidBody }
	{}
};


struct SRaycastHit
{

};


// 
class CPhysics
{
private:
	/// Properties

	// A list of all the colliders in the world.
	std::vector<SColliderInfo> Colliders;

	// 
	std::thread PhysicsThread;

	std::mutex PhysicsMutex;

	bool RunPhysics{ true };

	float DeltaTime{ 0.0f };

	uint64 LastFrame{ 0 };

	uint64 CurrentFrame{ 0 };

	std::thread QurryThread;
	std::mutex QurryMutex;

public:
	// The direction and strength of gravity.
	SVector Gravity{ SVector{0.0f, -9.81f, 0.0f} };


public:
	/// Constructors

	// Constructor, Initiates the physics engine.
	CPhysics();

	// Destructor.
	~CPhysics();


	/// Functions

	// Initiates the core system of the physics engine.
	// Starts the the physics thread.
	void InitPhysics();


private:
	// Runs every frame.
	// Checks for any new collisions.
	void Update();

	// Safely removes all the colliders stored within this object.
	void DeleteAllColliders();


public:
	/// Functions

	// Safely deletes the inputted collider from this object.
	// @param Collider - A reference to the collider type to delete.
	void DeleteCollider(CCollider* Collider);

	// Removes the inputted collider from this object.
	// @param Collider - A reference to the collider type to remove.
	void RemoveCollider(CCollider* Collider);

	// Adds a collider to this object.
	// @param - A reference to the created collider object.
	void AddCollider(CCollider* Collider);

	// Creates a collider and adds it to this object.
	void CreateCollider();

	// Checks every object to see if they are colliding.
	// Warning - Do not use this on Update(), this function is processive intense.
	// @return - A list of all the objects collision results.
	THitInfoList QuerryCollisions() const;

	// Checks every collision against an inputted collider.
	// @param Collider - The collider to check collisions against.
	// @param IgnoreSelf - Should the collider ignore any other colliders on itself.
	// @return - A list of all the collider's collision result.
	THitInfoList QuerryCollisions(CCollider* Collider, bool IgnoreSelf = true) const;

	// Draws a line from a specified start and end location and returns the first collisions found.
	// @param Start - The starting location of the linecast.
	// @param End - The end location of the line.
	// @param DebugParams - Parameters for displaying a debug line.
	// @return - The hit result from the first object this linecast hit.
	SHitInfo Linecast(SVector Start, SVector End, SDebugColliderParams DebugParams = false) const;

	// Draws a line from a specified start and end and returns the first collision found.
	// @param Start - The starting location of the line.
	// @param End - The end location of the line.
	// @param IgnoreObjects - A list of objects that should be ignored during the check.
	// @param DebugParams - Parameters for drawing a debug line.
	// @return - The hit results from the first object this line cast hit.
	SHitInfo Linecast(SVector Start, SVector End, TObjectList IgnoreObjects, SDebugColliderParams DebugParams = false) const;

	// Shoots a line from the starting point in a direction and returns the first collider hit.
	// @param Start - The starting location of the line.
	// @param Direction - The direction the raycast should go in.
	// @param Distance - How far the raycast should go (in pixels).
	// @param DebugParams - Parameters for drawing a debug line.
	// @return - The hit results from the first object this raycast hit.
	SRaycastHit Raycast(SVector Start, SVector Direction, float Distance, SDebugColliderParams DebugParams = false) const;
	
	// Shoots a line from the starting point in a direction and returns the first collider hit.
	// @param Start - The starting location of the line.
	// @param Direction - The direction the raycast should go in.
	// @param Distance - How far the raycast should go (in pixels).
	// @param IgnoreObjects - A list of objects that should be ignored during the check.
	// @param DebugParams - Parameters for drawing a debug line.
	// @return - The hit results from the first object this raycast hit.
	SRaycastHit Raycast(SVector Start, SVector Direction, float Distance, TObjectList IgnoreObjects, SDebugColliderParams DebugParams = false) const;

	// Shoots a line from the starting point in a direction and returns the first collider hit.
	// @param Start - The starting location of the line.
	// @param Direction - The direction the raycast should go in.
	// @param Distance - How far the raycast should go (in pixels).
	// @param HitInfo - The list of hit results to assign the return results.
	// @param DebugParams - Parameters for drawing a debug line.
	// @return - The hit results from the first object this raycast hit.
	SRaycastHit Raycast(SVector Start, SVector Direction, float Distance, SRaycastHit& HitInfo, SDebugColliderParams DebugParams = false) const;

	// Shoots a line from the starting point in a direction and returns the first collider hit.
	// @param Start - The starting location of the line.
	// @param Direction - The direction the raycast should go in.
	// @param Distance - How far the raycast should go (in pixels).
	// @param IgnoreObjects - A list of objects that should be ignored during the check.
	// @param HitInfo - The list of hit results to assign the return results.
	// @param DebugParams - Parameters for drawing a debug line.
	// @return - The hit results from the first object this raycast hit.
	SRaycastHit Raycast(SVector Start, SVector Direction, float Distance, TObjectList IgnoreObjects, SRaycastHit& HitInfo, SDebugColliderParams DebugParams = false) const;

	// Draws a line from a specified start and end and returns all the collisions found.
	// @param Start - The starting location of the line.
	// @param End - The end location of the line.
	// @param DebugParams - Parameters for drawing a debug line.
	// @return - The hit results from all objects this line cast hit.
	THitInfoList LinecastMulti(SVector Start, SVector End, SDebugColliderParams DebugParams = false) const;
	
	// Draws a line from a specified start and end and returns all the collisions found.
	// @param Start - The starting location of the line.
	// @param End - The end location of the line.
	// @param IgnoreObjects - A list of objects that should be ignored during the check.
	// @param DebugParams - Parameters for drawing a debug line.
	// @return - The hit results from all objects this line cast hit.
	THitInfoList LinecastMulti(SVector Start, SVector End, TObjectList IgnoreObjects, SDebugColliderParams DebugParams = false) const;

	// Shoots a line from the starting point in a direction and returns any colliders hit.
	// @param Start - The starting location of the line.
	// @param Direction - The direction the raycast should go in.
	// @param Distance - How far the raycast should go (in pixels).
	// @param DebugParams - Parameters for drawing a debug line.
	// @return - The hit results from all objects this raycast hit.
	std::vector<SRaycastHit> RaycastMulti(SVector Start, SVector Direction, float Distance, SDebugColliderParams DebugParams = false) const;

	// Shoots a line from the starting point in a direction and returns any colliders hit.
	// @param Start - The starting location of the line.
	// @param Direction - The direction the raycast should go in.
	// @param Distance - How far the raycast should go (in pixels).
	// @param IgnoreObjects - A list of objects that should be ignored during the check.
	// @param DebugParams - Parameters for drawing a debug line.
	// @return - The hit results from all objects this raycast hit.
	std::vector<SRaycastHit> RaycastMulti(SVector Start, SVector Direction, float Distance, TObjectList IgnoreObjects, SDebugColliderParams DebugParams = false) const;

	// Shoots a line from the starting point in a direction and returns any colliders hit.
	// @param Start - The starting location of the line.
	// @param Direction - The direction the raycast should go in.
	// @param Distance - How far the raycast should go (in pixels).
	// @param HitInfo - The list of hit results to assign the return results.
	// @param DebugParams - Parameters for drawing a debug line.
	// @return - The hit results from all objects this raycast hit.
	std::vector<SRaycastHit> RaycastMulti(SVector Start, SVector Direction, float Distance, std::vector<SRaycastHit>& HitInfo, SDebugColliderParams DebugParams = false) const;

	// Shoots a line from the starting point in a direction and returns any colliders hit.
	// @param Start - The starting location of the line.
	// @param Direction - The direction the raycast should go in.
	// @param Distance - How far the raycast should go (in pixels).
	// @param IgnoreObjects - A list of objects that should be ignored during the check.
	// @param HitInfo - The list of hit results to assign the return results.
	// @param DebugParams - Parameters for drawing a debug line.
	// @return - The hit results from all objects this raycast hit.
	std::vector<SRaycastHit> RaycastMulti(SVector Start, SVector Direction, float Distance, TObjectList IgnoreObjects, std::vector<SRaycastHit>& HitInfo, SDebugColliderParams DebugParams = false) const;

};