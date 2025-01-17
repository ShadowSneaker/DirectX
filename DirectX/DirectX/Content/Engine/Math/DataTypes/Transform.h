#pragma once
#include "Quaternion.h"

#include <vector>

struct STransform
{
private:

	// 
	STransform* Parent = nullptr;

	// 
	std::vector<STransform*> Children;


public:
	// The Transform's Position Component.
	SVector Location{ 0.0f };

	// The Transform's Rotation Component.
	SQuaternion Rotation{ 0.0f, 0.0f, 0.0, 1.0f };

	// The Transform's Scale Component.
	SVector Scale{ 1.0f };


public:

	/// Constructors

	// Constructor, Default.
	STransform() {};

	// Constructor, Initiates all components of the transform.
	STransform(const SVector InLocation, const SQuaternion InRotation, const SVector InScale);

	// Destructor.
	~STransform();


	/// Operators


	/// Conversions


	/// Functions

private:
	// Removes this transform from it's parent's children list.
	inline void RemoveFromParent();
public:

	// Gets the forward pointing vector relative to this object.
	inline SVector Forward() const { return GetWorldRotation().GetForwardVector(); }

	// Gets the backward pointing vector relative to this object.
	inline SVector Backward() const { return -GetWorldRotation().GetForwardVector(); }

	// Gets the right pointing vector relative to this object.
	inline SVector Right() const { return GetWorldRotation().GetRightVector(); }

	// Gets the left pointing vector relative to this object.
	inline SVector Left() const { return -GetWorldRotation().GetRightVector(); }

	// Gets the up pointing vector relative to this object.
	inline SVector Up() const { return GetWorldRotation().GetUpVector(); }

	// Gets the down pointing vector relative to this object.
	inline SVector Down() const { return -GetWorldRotation().GetUpVector(); }

	// Rotates this transform to look at another transform's position.
	inline void LookAt(STransform Other);


	/// Getters

	// Gets the relative location of this object.
	inline SVector GetLocation() const { return Location; }

	// Gets the relative rotation of this object.
	inline SQuaternion GetRotation() const { return Rotation; }

	// Gets the relatice scale of this object.
	inline SVector GetScale() const { return Scale; }

	STransform GetWorldTransform() const;

	//inline SVector GetWorldLocation() const { return ((Parent) ? Parent->GetWorldLocation() : SVector{ 0.0f }) + Location; }
	inline SVector GetWorldLocation() const { return GetWorldTransform().Location; }

	// Gets the rotation of this object in worldspace.
	inline SQuaternion GetWorldRotation() const { return (((Parent) ? Parent->GetWorldRotation() : SQuaternion{ 0.0f }) + Rotation); }
	//inline SQuaternion GetWorldRotation() const { return GetWorldTransform().Rotation; }

	// Gets the scale of this object in worldspace.
	//inline SVector GetWorldScale() const { return ((Parent) ? Parent->GetWorldScale() : SVector{ 1.0f }) * Scale; }
	inline SVector GetWorldScale() const { return GetWorldTransform().Scale; }

	// Gets a reference to all this object's children.
	inline std::vector<STransform*> GetChildren() const { return Children; }

	// Gets a reference to this object's parent.
	inline STransform* GetParent() const { return Parent; }


	/// Setters

	inline void SetParent(STransform* Transform);


	/// Statics

};


inline void STransform::LookAt(STransform Other)
{
	Rotation.Y = TO_DEGREES(TMath::ATan2(Other.Location[X] - Location[X], Other.Location[Z] - Location[Z]));
}


