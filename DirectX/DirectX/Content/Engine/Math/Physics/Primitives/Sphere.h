#pragma once
#include "../Collider.h"


// 
class CSphere :public CCollider
{
public:
	/// Properties

	// The radius of the sphere.
	float Radius{ 1.0f };


public:
	/// Constructors

	// Constructor, Default.
	CSphere();

	// Constructor, Initiates this collider's transform.
	// @param InTransform - The location, rotation and scale of this collider.
	CSphere(STransform InTransform);

	// Constructor, Initiates this collider's transform and radius.
	// @param InTransform - The location, rotation and scale of this collider.
	// @param InRadius - The radius of the sphere
	CSphere(STransform InTransform, float InRadius);


	/// Overridables

	// Determines what collider type of collider the specified collider is
	// then checks for the collision between this collider and the inputted collider.
	// @param Other - The ambiguous collider type to test collisons against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const CCollider* Other) const override;

	// Checks the collision between this collider and a sphere collider.
	// @param Other - The sphere collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const CSphere* Other) const override;

	// Checks the collision between this collider and a box collider.
	// @param Other - The box collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CBox* Other) const override;

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

	// Returns the radius after scaling (Note scale is determined by the highest scale component in the owner).
	inline float GetRadius() const { return Radius * ((UseScale) ? Transform.GetWorldScale().MaxComp() : Transform.Scale.MaxComp()); }
};