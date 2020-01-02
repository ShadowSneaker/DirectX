#pragma once
#include "../World/Objects/ObjectBase.h"


// The core information a component requires to function.
struct SComponentInfo
{
	/// Properties

	// The core information of a ObjectBase.
	SObjectBase Core;

	// The owner of this component.
	class CWorldObject* Object;



	/// Constructors

	// Constructor, Default.
	SComponentInfo(SObjectBase InCore, class CWorldObject* InObject)
		:Core{ InCore }, Object{ InObject }
	{}
};



// The base type of component that can be attached to any world object.
class CComponent :public CObjectBase
{
private:
	/// Properties

	// The owning world object this component is attached to
	class CWorldObject* Owner{ nullptr };


public:
	/// Constructors

	// Constructor, Default.
	CComponent(SComponentInfo Info);

	// Destructor.
	virtual ~CComponent();


	/// Functions



	/// Setters

	// Sets the owning WorldObject of this component.
	inline void SetOwner(class CWorldObject* Object) { Owner = Object; }
	

	/// Getters

	// Gets the owning World Object of this component.
	inline class CWorldObject* GetOwner() const { return Owner; }
};