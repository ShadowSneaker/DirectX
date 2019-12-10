#include "LightBaseComponent.h"
#include "../../Graphics/Renderer.h"



CLightBaseComponent::CLightBaseComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CLightBase::CLightBase{}
{
	Shader = GetRenderer()->SetLightShader(this, "Lighting.hlsl");
}


CLightBaseComponent::~CLightBaseComponent()
{
	CComponent::~CComponent();
}