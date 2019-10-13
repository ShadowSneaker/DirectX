#pragma once




class CObjectBase
{
private:
	/// Properties

	bool Enable{ true };




public:
	/// Constructors

	// Constructor, Default.
	CObjectBase();



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

};