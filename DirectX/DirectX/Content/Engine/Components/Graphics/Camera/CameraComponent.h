#pragma once
#include "../../Component.h"
#include "../../../Graphics/Camera.h"


// A component type that allows the user to view the world.
class CCameraComponent :public CComponent, public CCamera
{
private:
	/// Properties


public:
	/// Constructors

	// Constructor, Default.
	CCameraComponent(SComponentInfo Info);

	// Destructor
	~CCameraComponent();


	/// Functions


};