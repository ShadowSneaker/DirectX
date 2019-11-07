#pragma once
#include "../Collider.h"


class CSphereCollider :public CCollider
{
public:
	/// Properties

	// 
	float Radius{ 1.0f };

public:
	/// Constructors

	// Constructor, Default.
	CSphereCollider();

	// Constructor, Initialises a default size based on the vertices of the mesh this collider is on.
	// @param Mesh - The reference to the mesh to create the default collider size.
	CSphereCollider(class CStaticMesh* Mesh);

	// Constructor, initiates this collider's transform.
	// @param InOwner - The object that this collider is bound to.
	// @param InTransform - The location, rotation and scale of this collider.
	CSphereCollider(class CWorldObject* InOwner, STransform InTransform);


	/// Overridables

	// Determines what collider type of collider the specified collider is
	// then checks for the collision between this collider and the inputted collider.
	// @param Other - The ambiguous collider type to test collisons against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const CCollider* Other) const override;

	// Checks the collision between this collider and a circle collider.
	// @param Other - The circle collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CSphereCollider* Other) const override;

	// Checks the collision between this collider and a square collider.
	// @param Other - The square collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const CBoxCollider* Other) const override;

	// Checks the collision between this collider and a cylinder collider.
	// @param Other - The cylinder collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CCylinderCollider* Other) const;

	// Checks the collision between this collider and a capsule collider.
	// @param Other - The capsule collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CCapsuleCollider* Other) const;

	// Checks the collision between this collider and a polygon collider.
	// @param Other - The polygon collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CPolygonCollider* Other) const;


	/// Functions

	// Displays a representation of this collider on the screen for a specified amount of time.
	virtual void DrawDebug() const override;



	/// Getters

	// 
	inline float GetRadius() const { return Radius * Transform.GetWorldScale()[X]; }
};