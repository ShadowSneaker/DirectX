#include "DirectionalLight.h"


CDirectionalLight::CDirectionalLight()
	:CLightBase::CLightBase{}
{
	Transform.Rotation = SQuaternion{ -0.3f, -0.8f, 0.5f, 0.0f };
	Colour = SVector4{ 1.0f, 0.0f, 0.0f, 1.0f };
}