#pragma once
#include "ObjectBase.h"
#include "../../Components/Component.h"


// The basic object that can exist in worldspace.
class CWorldObject :public CObjectBase
{
private:

	/// Properties

	// A list of all components attached to this object.
	std::vector<CComponent*> Components;


public:

	// The location, rotation and scale of this object.
	STransform Transform;


public:
	/// Constructors

	// Constructor, Default.
	CWorldObject(SObjectBase Core);

	// Destructor.
	~CWorldObject();


	/// Overridables

	// Updates every frame.
	virtual void Update() override;

	// Called when this object is being destroyed.
	virtual void End() override;


	/// Functions

protected:
	// Creates a component and attaches it to this object.
	template <typename Type>
	Type* CreateComponent();


private:
	// Removes all components attached to this object.
	void DeleteAllComponents();


public:
	// Removes a specified component on this object.
	// @param Component - A reference to the component to remove.
	void DeleteComponent(CComponent* Component);

	/// Setters


	/// Getters

	template <typename Type>
	Type* FindComponent();
};


template <typename Type>
Type* CWorldObject::CreateComponent()
{
	Type NewComponent = new Type{ SObjectBase{STransform{}, GetWorld(), GetPhysics(), GetTimerManager() }, this };
	if (NewComponent)
	{
		Components.push_back(NewComponent);
		return NewComponent;
	}

	delete NewComponent;
	return nullptr;
}


template <typename Type>
Type* CWorldObject::FindComponent()
{
	for (uint i = 0; i < Components.size(); ++i)
	{
		Type* Component{ (Type*)Components[i] };
		if (Component)
		{
			return Component;
		}
	}
	return nullptr;
}