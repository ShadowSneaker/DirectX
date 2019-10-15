#pragma once
#include "WorldObject.h"


// An object that can be controlled by the player or AI.
class CPuppet :public CWorldObject
{
private:
	/// Properties


public:
	/// Constructors

	// Constructor, Default.
	// @param Core - The core information for an object.
	CPuppet(SObjectBase Core);

	// Destructor.
	~CPuppet();


	/// Overridables

	// Runs every tick.
	virtual void Update() override;

	// Allows user inputs to be bound to this object.
	virtual void SetupInput(class CInputManager* Input) {}
};