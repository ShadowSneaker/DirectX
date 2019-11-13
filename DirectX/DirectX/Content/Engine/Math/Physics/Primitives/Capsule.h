#pragma once
#include "../Collider.h"


// TODO:
// There will need to be a way for the collider's components to be updated using UpdateCapsule() when
// a collision is being calculated.
// Although, instead I could just simply have a SetSize() or SetHeight functions that updates it there instead of having public size and height.

class CCapsule :public CCollider
{
private:
	// The sphere located at the top of the collider.
	class CSphere* TopSphere;

	// The sphere located at the bottom of the collider.
	class CSphere* BottomSphere;

	// The main body componet of this cylinder.
	class CCylinder* Body;

	// The radius of the capsule collider.
	float Radius{ 1.0f };

	// Total height of the capsule (from the top of the capsule to the bottom).
	float Height{ 1.0f };


public:
	/// Constructors

	// Constructor, Default.
	CCapsule();

	// Constructor, Initiates this collider's transform.
	// @param InTransform - The location, rotation and scale of this collider.
	CCapsule(STransform InTransform);

	// Constructor, Initiates this collider's transform.
	// @param InTransform - The location, rotation and scale of this collider.
	// @param InRadius - The radius of this capsule.
	// @param InHeight - The height of this capsule.
	CCapsule(STransform InTransform, float InRadius, float InHeight);

	// Destructor.
	~CCapsule();


private:
	// Initiates the capsule components. This should only be ran once at the start of every constructor.
	void InitiateCapsule();
public:


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
	virtual bool CheckCollision(const CCapsule* Other) const override;

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


private:

	// Updates all the components of the capsule collider so that they are the correct sizes.
	void UpdateCapsule();
public:


	/// Setters

	// Sets the radius of the capsule collider.
	inline void SetRadius(float NewRadius) { Radius = NewRadius; UpdateCapsule(); }

	// Sets the total height of the capsule collider.
	inline void SetHeight(float NewHeight) { Height = NewHeight; UpdateCapsule(); }


	/// Getters

	// Returns the height of the Cylinder component (The hight of the capsule minus the top and bottom spheres).
	inline float GetBodyHeight() const { return ((Radius * 2) - Height) * GetScale()[Y]; }

	// Returns the total height of the capsule collider.
	inline float GetHeight() const { return Height; }

	// Returns the radius of this capsule.
	inline float GetRadius() const { return Radius; }
};