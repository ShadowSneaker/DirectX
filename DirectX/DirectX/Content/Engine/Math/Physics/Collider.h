

/*
	* Almost all colliders have two types of collision checks, a fast and slow check.
	* Fast check will be enabled if USE_FAST_CHECK_WHERE_POSSIBLE is defined.
	* Fast check can only be used if the collider is aligned with the grid.

	* Fast check - Only runs when applicable, faster results, can't be used if the collider is rotated.
	* Slow check - Slower results, used if fast check is not applicable.

	* The Polygon collider will only use a slow check due to its unique nature of being any shape.
*/

#pragma once
#include "../DataTypes/Transform.h"
#include "../DataTypes/Vertex.h"

#ifndef WORLD
#define WORLD
#endif // !WORLD
#define USE_FAST_CHECK_WHERE_POSSIBLE


// The info that is recieved when an object collides with another.
struct SHitInfo
{
	/// Properties

	// A value determining if this object hit another.
	bool Hit;

	// A reference tot he collider this object collided with.
	class CCollider* Collider;

#ifdef WORLD
	// A reference to the owning object that was hit.
	class CWorldObject* HitObject;
#endif

	/// Operators

	// Converts the Hit Info into a bool for easy checking.
	inline operator bool() const { return Hit; }
};


// The base collider typ used to calculate collisions against other colliders.
// This is an abiguous collider type. This just stores functions holds the basic
// information for actual colliders. It also is used to store a list of colliders.
class CCollider
{
protected:
	/// Properties

	// A reference to all the vertices the bound mesh has.
	//SVertex** Vertices{ nullptr };
	std::vector<SVertex>* Vertices{ nullptr };

	// A reference to the amount of vertices the bound mesh has.
	//uint* VertexCount{ nullptr };


public:
	// The relative transform of this collider.
	STransform Transform;

#ifdef WORLD
	// A reference to this collider's owner object.
	class CWorldObject* Owner;
#endif

	// Makes this collider overlapable instead of blocking.
	bool Overlap{ false };

	// Allows this collider to check for collision types.
	bool Enable{ true };

	// Should this collider be affected by its parent's scale.
	// Note: This collider will still be affected by this collider's scale.
	bool UseScale{ true };

	// Should this collider be affected by its parent's location.
	// Note: This collider will still be affected by this collider's location.
	bool UseLocation{ true };

	// Adjusts this collider to the bounds of the attached object.
	// @note - The bounding collider will cover the entire object.
	bool AutoUpdateBounds{ false };


public:
	/// Constructors

	// Constructor, Default.
	CCollider();

	// Constructor, Initiates this collider's transform.
	// @param InTransform - The location, rotation and scale of this collider.
	CCollider(STransform InTransform);


	/// Functions

private:

	void Project(const SVector& Axis, const std::vector<SVector>& PTSet, float& MinAlong, float& MaxAlong) const;

	// 
	// @param Min1 - The minimum value of the first item.
	// @param Max1 - The maximum value of the first item.
	// @param Min2 - The minimum value of the second item.
	// @param Max2 - The maximum value of the second item.
	bool TestOverlaps(float Min1, float Max1, float Min2, float Max2) const;

	// Checks for the collision of each vertex position against the normal of the inputted vector.
	// @param Normals - A list of normals to test against.
	// @param Other - A reference to the other collider.
	bool CheckSATCollision(std::vector<SVector> Normals, const CCollider* Other) const;

protected:
	// Checks the collision between this collider and an inputted collider using their vertices.
	// @note - This collision type uses the SAT (Separating Axis Theorem).
	// @note - The vertices of this collider MUST be set in order for this to work, otherwise the return value will always be false.
	// @param Other - The collider this collider to test collisions against.
	// @return - Returns true if a collision was detected.
	bool SATCollision(const CCollider* Other) const;
public:

	// Determines what collider type of collider the specified collider is
	// then checks for the collision between this collider and the inputted collider.
	// @param Other - The ambiguous collider type to test collisons against.
	// @return - Returns true if a collision was detected.
	virtual bool CheckCollision(const CCollider* Other) const = 0;

	// Checks the collision between this collider and a sphere collider.
	// @param Other - The circle collider to test against.
	// @return - Returns true if a collision was detected.
	virtual bool CheckCollision(const class CSphere* Other) const = 0;

	// Checks the collision between this collider and a box collider.
	// @param Other - The box collider to test against.
	// @return - Returns true if a collision was detected.
	virtual bool CheckCollision(const class CBox* Other) const = 0;

	// Checks the collision between this collider and a axis aligned bounding box collider.
	// @param Other - The bounding box collider to test against.
	// @return - Returns true if a collision was detected.
	virtual bool CheckCollision(const class CAxisAlignedBoundingBox* Other) const = 0;

	// Checks the collision between this collider and a point collider.
	// @param Other - The point collider to test against.
	// @return - Returns true if a collision was detected.
	virtual bool CheckCollision(const class CPoint* Other) const = 0;

	// Checks the collision between this collider and a line collider.
	// @param Other - The line collider to test against.
	// @return - Returns true if a collision was detected.
	virtual bool CheckCollision(const class CLine* Other) const = 0;

	// Checks the collision between this collider and a capsule collider.
	// @param Other - The capsule collider to test against.
	// @return - Returns true if a collision was detected.
	virtual bool CheckCollision(const class CCapsule* Other) const = 0;

	// Checks the collision between this collider and a polygon collider.
	// @param Other - The polygon collider to test against.
	// @return - Returns true if a collision was detected.
	virtual bool CheckCollision(const class CPolygon* Other) const = 0;

	// Checks the collision between this collider and a cylinder collider.
	// @param Other - The cylinder collider to test against.
	// @return - Returns true if a collision was detected.
	virtual bool CheckCollision(const class CCylinder* Other) const = 0;




	// Updates the bounding collider to cover the entire object.
	virtual void UpdateBounds() = 0;

	/// Setters

	//inline void SetVertices(SVertex** InVertices) { Vertices = InVertices; }
	inline void SetVertices(std::vector<SVertex>* InVertices) { Vertices = InVertices; }
	//inline void SetVertexCount(uint* Count) { VertexCount = Count; }

	/// Getters

	// Returns the location of this collider (Takes UseLocation into consideration).
	inline SVector GetLocation() const { return ((UseLocation) ? Transform.GetWorldLocation() : Transform.Location); }

	// Returns the scale of this collider (Takes UseScale into consideration).
	inline SVector GetScale() const { return ((UseScale) ? Transform.GetWorldScale() : Transform.Scale); }

	// Returns the center of all the vertices.
	SVector GetCenter() const;

	std::vector<SVector> GetNormals() const;

	std::vector<SVector> GetVerticesLocations() const;
};