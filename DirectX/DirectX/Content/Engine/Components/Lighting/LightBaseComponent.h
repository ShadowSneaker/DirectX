#pragma once
#include "../Component.h"
#include "../../Graphics/Lighting/LightBase.h"


// A light component that doesn't actually produce any light.
// This is used as a parent class to handle how light components should behave.
// This component should not be directly used. Use: CDirectionalLightComponent, CPointLightComponent,
// CSpotLightComponent instead.
class CLightBaseComponent :public CComponent, public CLightBase
{
protected:
	/// Properties


public:
	/// Constructors

	// Constructor, Default.
	CLightBaseComponent(SComponentInfo Info);

	// Destructor.
	~CLightBaseComponent();



};
