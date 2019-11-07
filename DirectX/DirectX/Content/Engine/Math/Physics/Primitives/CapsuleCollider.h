#pragma once
#include "../Collider.h"


class CCapsuleCollider :public CCollider
{
private:
	/// Properties

	// The circle representing the top of the capsule collider.
	class CSphereCollider* TopSphere;

	// The circle representing the bottom of the capsule collider.
	class CSphereCollider* BottomSphere;

	// The box representing the connection between the top circle and bottom circle.
	class CCylinderCollider* Body;

public:
	// The total height of the capsule.
	float Height{ 2.0f };

	// The total width of the capsule.
	float Radius{ 1.0f };


public:
	/// Constructors

	// Constructor, Default.
	CCapsuleCollider();

	// Constructor, Initialises a default size based on the vertices of the mesh this collider is on.
	// @param Mesh - The reference to the mesh to create the default collider size.
	CCapsuleCollider(class CStaticMesh* Mesh);

	// Constructor, Initiates this collider's transform.
	// @param InOwner - The object that this collider is bound to.
	// @param InTransform - The location, rotation and scale of this collider.
	CCapsuleCollider(class CWorldObject* InOwner, STransform InTransform);

	// Destructor.
	~CCapsuleCollider();


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

private:
	// Initiates all the components of the capsule.
	void Initiate();
public:

	// Displays a representation of this collider on the screen for a specified amount of time.
	virtual void DrawDebug() const override;


	/// Getters

private:
	// Find the height of the body collider.
	float GetBodyHeight() const { return (Height - (Radius * 2.0f)); }
};