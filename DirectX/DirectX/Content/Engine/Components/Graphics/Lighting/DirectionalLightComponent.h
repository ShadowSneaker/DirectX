#pragma once
#include "../../Component.h"
#include "../../../Graphics/Lighting/DirectionalLight.h"


// A light component that globaly lights up the world pointing in a specific direction.
class CDirectionalLightComponent :public CComponent, public CDirectionalLight
{
private:
	/// Properties


public:
	/// Constructors

	// Constructor, Default.
	CDirectionalLightComponent(SComponentInfo Info);

	// Destructor.
	~CDirectionalLightComponent();


	/// Functions
};