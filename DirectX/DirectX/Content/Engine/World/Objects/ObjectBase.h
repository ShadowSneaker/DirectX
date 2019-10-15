#pragma once
#include "../../Math/Math.h"
#include "../../Core/Systems/TimerManager.h"


// A list of references of core systems to allow the user to access common systems.
// An encapsulation for object constructors. All constructors that inherit from CObjectBase requires this as an input.
struct SObjectBase
{
	/// Properties

	// The location, rotation and position of the object.
	// This is only used to initialise the world object at a specified location, rotation and scale.
	STransform Transform;

	// A reference to the world object.
	class CWorld* World{ nullptr };

	// A reference to the physics object.
	class CPhysics* Physics{ nullptr };

	// A reference to the player camera.
	//class CCamera* Camera;

	// A reference to the image manager.
	//class CImageManager* ImageManager;

	// A reference to the input manager.
	//class CInputManager* InputManager;

	// A reference to the timer manager.
	CTimerManager* TimerManager{ nullptr };

	// A reference to the created window.
	//SVector2i WindowSize;
};


class CObjectBase
{
private:
	/// Properties

	bool Enable{ true };

	SObjectBase Base;


public:
	/// Constructors

	// Constructor, Default.
	CObjectBase(SObjectBase Core);



	/// Overridables

	// Called on the first loop this object was created.
	virtual void Begin() {}

	// Updates every frame.
	virtual void Update() {}

	// Called when this object is pending kill.
	// This is not the same as the destructor.
	// This is used to finishup gameplay components in this object.
	virtual void End() {}


	/// Functions




	/// Setters

	inline void SetEnabled(bool NewEnable) { Enable = NewEnable; }

	/// Getters


	// This will be changed to a recursion function to go through all parents to see if they are also enabled.
	inline bool IsEnabled() const { return Enable; }

	// Returns a reference to the world.
	inline class CWorld* GetWorld() const { return Base.World; }

	// Returns a reference to the level this object belongs to.

	// Returns a reference to the physics object.
	inline class CPhysics* GetPhysics() const { return Base.Physics; }

	// Returns the width and height of the created window.
	//inline SVector2i GetWindowSize() const { return Base.WindowSize; }

	// Returns a reference to the Image manager.
	//inline class CImageManager* GetImageManager() const { return Base.ImageManager; }

	// Returns a reference to the timer manager.
	inline CTimerManager* GetTimerManager() const { return Base.TimerManager; }

	// Returns a reference to the input manager.
	//inline class CInputManager* GetInputManager() const { return Base.InputManager; }
};