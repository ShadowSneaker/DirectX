#include "PointLightComponent.h"
#include "../../Graphics/Renderer.h"


CPointLightComponent::CPointLightComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CPointLight::CPointLight{}
{
	//Shader = GetRenderer()->SetLightShader(this, "Lighting.hlsl");
}


CPointLightComponent::~CPointLightComponent()
{
	
}