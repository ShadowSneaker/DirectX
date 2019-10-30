#pragma once
#include "../DataTypes/Transform.h"
#include "../MathStatics.h"

#include <functional>


// The info gathered whena collision occures.
struct SHitInfo
{
public:
	/// Properties

	// Represents if the collision hit.
	bool Hit{ false };

	// A reference to the collider that was hit
	class CCollider* Collider{ nullptr };

	// A reference to the world object that owned the hit collider.
	class CWorldObject* HitObject{ nullptr };


	/// Constructors

	// Constructor, Default.
	SHitInfo()
	{}

	// Constructor, Initiates the hit result and hit collider.
	SHitInfo(bool InHit, class CCollider* HitCollider)
		:Hit{ InHit }, Collider{ HitCollider }
	{}

	// Constructor, Initaies every component of the struct.
	SHitInfo(bool InHit, class CCollider* HitCollider, class CWorldObject* InHitObject)
		:Hit{ InHit }, Collider{ HitCollider }, HitObject{ InHitObject }
	{}


	/// Operators

	// Returns the hit component.
	// Used for easy testing weather or not objects were hit.
	inline operator bool() const { return Hit; }
};


// Used to draw the collider outline for debug.
struct SDebugColliderParams
{
	/// Properties

	// Represents if the debug outline should be drawn.
	bool Enable{ false };

	// Determines how long the line should be displayed for (in seconds).
	float DisplayDuration{ 5.0f };

	// The colour that the debug line should be drawn in.
	// SColour DisplayColour{ SColour::Yellow() };


	/// Constructors

	// Constructor, Default.
	// Note: using this constructor will not allow the debug draw.
	SDebugColliderParams()
	{}


	// 
	SDebugColliderParams(bool SetEnabled)
		:Enable{ SetEnabled }
	{}


	// 
	SDebugColliderParams(bool SetEnabled, float Duration/*, SColour Colour*/)
		:Enable{ SetEnabled }, DisplayDuration{ Duration }/*, DisplayColour{ Colour }*/
	{}
};


//  
class CCollider
{
private:
	/// Properties

	// The delegate to the function that should be called when a collision occures.
	std::function<void(SHitInfo)> BoundFunction;

public:
	// Should this collider allow collisions.
	bool Enabled{ true };

	// Should this collider only trigger on overlap events.
	bool Overlap{ false };

	// The location, rotation and scale of this collider.
	STransform Transform;

	// The debug parameters for this collider.
	SDebugColliderParams ShowCollider{ false };

	// A reference to the owner of this collider.
	class CWorldObject* Owner{ nullptr };

	// Should this collider be affected by the parent's scaling.
	bool UseParentScale{ true };

public:
	/// Constructors

	// Constructor, Default.
	CCollider();

	// Constructor, Initiates this collider's transform.
	// @param Transform - The location, rotatoin and scale of this collider.
	CCollider(class CWorldObject* InOwner, STransform InTransform);


	/// Overridables

	// Determines what collider type of collider the specified collider is
	// then checks for the collision between this collider and the inputted collider.
	// @param Other - The ambiguous collider type to test collisons against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const CCollider* Other) const = 0;

	// Checks the collision between this collider and a circle collider.
	// @param Other - The circle collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CSphereCollider* Other) const = 0;

	// Checks the collision between this collider and a square collider.
	// @param Other - The square collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CBoxCollider* Other) const = 0;

	// Checks the collision between this collider and a cylinder collider.
	// @param Other - The cylinder collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CCylinderCollider* Other) const = 0;

	// Checks the collision between this collider and a capsule collider.
	// @param Other - The capsule collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CCapsuleCollider* Other) const = 0;

	// Checks the collision between this collider and a polygon collider.
	// @param Other - The polygon collider to test against.
	// @return - The information gathered from the collision check.
	virtual bool CheckCollision(const class CPolygonCollider* Other) const = 0;


	/// Functions

	// Displays a representation of this collider on the screen for a specified amount of time.
	virtual void DrawDebug() const;

	// Sets the bound function to an inputted function.
	inline void BindFunction(std::function<void(SHitInfo)> Function) { BoundFunction = Function; }

	// Calls the bound function.
	inline void CallFunction(SHitInfo HitInfo) const { BoundFunction(HitInfo); }


	/// Setters


	/// Getters
};