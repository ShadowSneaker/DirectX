#pragma once
#include "../World/Objects/ObjectBase.h"


struct SComponentInfo
{
	/// Properties

	SObjectBase Core;
	class CWorldObject* Object;


	/// Constructors

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

	inline void SetOwner(class CWorldObject* Object) { Owner = Object; }
	

	/// Getters

	inline class CWorldObject* GetOwner() const { return Owner; }
};