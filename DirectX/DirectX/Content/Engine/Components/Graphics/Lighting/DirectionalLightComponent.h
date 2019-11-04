#pragma once
#include "../../Component.h"
#include "../../../Graphics/Lighting/DirectionalLight.h"


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