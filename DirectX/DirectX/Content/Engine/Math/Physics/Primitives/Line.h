#pragma once
#include "../Collider.h"


class CLine :public CCollider
{
public:
	/// Components.

	// The end locatino of this line.
	SVector EndPosition{ SVector::Forward() };

public:
	/// Constructors

	// Constructor, Default.
	CLine();

	// Constructor, Initiates this collider's transform.
	// @param InTransform - The location, rotation and scale of this collider.
	CLine(STransform InTransform);

	// Constructor, Initiates this collider's transform and end position.
	// @param InTransform - The location, rotation and scale and this collider.
	// @param EndPos - The location this line will end at.
	CLine(STransform InTransform, SVector EndPos);


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


	/// Getters

	// Returns the local end position of this line.
	inline SVector GetEndPosition() const { return EndPosition * Transform.Scale; }

	// Returns the loal start position of this line.
	inline SVector GetStartPosition() const { return Transform.Location; }

	// Returns the world end position of this line.
	inline SVector GetWorldEndPosition() const { return (EndPosition + Transform.GetWorldLocation()) * Transform.GetWorldScale(); }

	// Returns the world start position of this line.
	inline SVector GetWorldStartPosition() const { return Transform.GetWorldLocation(); }
};