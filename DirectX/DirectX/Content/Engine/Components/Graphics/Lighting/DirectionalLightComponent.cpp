#include "DirectionalLightComponent.h"
#include "../../../Graphics/Renderer.h"


CDirectionalLightComponent::CDirectionalLightComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CDirectionalLight::CDirectionalLight{}
{
	GetRenderer()->AddLight(this);
}


CDirectionalLightComponent::~CDirectionalLightComponent()
{
	GetRenderer()->RemoveLight(this);
	CComponent::~CComponent();
	CDirectionalLight::~CDirectionalLight();
}