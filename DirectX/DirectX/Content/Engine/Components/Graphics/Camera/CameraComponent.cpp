#include "CameraComponent.h"
#include "../../../Graphics/Renderer.h"


CCameraComponent::CCameraComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CCamera::CCamera{}
{
	GetRenderer()->AddCamera(this);
}


CCameraComponent::~CCameraComponent()
{
	GetRenderer()->RemoveCamera(this);
	CComponent::~CComponent();
	CCamera::~CCamera();
}