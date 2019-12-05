#pragma once
#include "../Component.h"
#include "../../Graphics/Lighting/PointLight.h"


class CPointLightComponent :public CComponent, public CPointLight
{
private:
	/// Properties


public:
	/// Constructors.

	// Constructor, Default.
	CPointLightComponent(SComponentInfo Info);

	// Destructor.
	~CPointLightComponent();
}