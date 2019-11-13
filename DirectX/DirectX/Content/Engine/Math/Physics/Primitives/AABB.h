#pragma once
#include "../Collider.h"


// A box collider that is fixed along an axis and cannot be rotated.
// This box collider will automatically adjust its size to fit the object it is attached to.
class CAxisAlignedBoundingBox :public CCollider
{
public:
	/// Components.

	// The furthest X, Y and Z extents of this collider.
	SVector Extents{ 1.0f };

public:
	/// Constructors

	// Constructor, Default.
	CAxisAlignedBoundingBox();

	// Constructor, Initiates this collider's transform.
	// @param InTransform - The location, rotation and scale of this collider.
	CAxisAlignedBoundingBox(STransform InTransform);


	/// Overridables

	// Determines what collider type of collider the specified collider is
	// then checks for the collision between this collider and the inputted collider.
	// @param Other - The ambiguous collider type to test collisons against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const CCollider* Other) const override;

	// Checks the collision between this collider and a sphere collider.
	// @param Other - The sphere collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CSphere* Other) const override;

	// Checks the collision between this collider and a box collider.
	// @param Other - The box collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const CBox* Other) const override;

	// Checks the collision between this collider and a axis aligned bounding box collider.
	// @param Other - The bounding box collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CAxisAlignedBoundingBox* Other) const override;

	// Checks the collision between this collider and a point collider.
	// @param Other - The point collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CPoint* Other) const;

	// Checks the collision between this collider and a line collider.
	// @param Other - The line collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CLine* Other) const;

	// Checks the collision between this collider and a capsule collider.
	// @param Other - The capsule collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CCapsule* Other) const override;

	// Checks the collision between this collider and a polygon collider.
	// @param Other - The polygon collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CPolygon* Other) const override;

	// Checks the collision between this collider and a cylinder collider.
	// @param Other - The cylinder collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CCylinder* Other) const override;

	// Updates the bounding collider to cover the entire object.
	virtual void UpdateBounds() override;


	/// Setters


	/// Getters

	// Gets the cube collider's minimum extents in the worldspace.
	inline const SVector GetMinExtents() const { return ((UseLocation) ? Transform.GetWorldLocation() : Transform.Location) - ((Extents / 2) * ((UseScale) ? Transform.GetWorldScale() : Transform.Scale)); }

	// Gets the cube collider's minimum extents in the worldspace.
	inline const SVector GetMaxExtents() const { return ((UseLocation) ? Transform.GetWorldLocation() : Transform.Location) + ((Extents / 2) * ((UseScale) ? Transform.GetWorldScale() : Transform.Scale)); }
};

typedef CAxisAlignedBoundingBox CAABB;