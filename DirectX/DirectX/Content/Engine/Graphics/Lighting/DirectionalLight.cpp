#include "DirectionalLight.h"


CDirectionalLight::CDirectionalLight()
	:CLightBase::CLightBase{}
{
	//Transform.Rotation = SQuaternion{ 0.0f, 8.0f, 0.5f, 0.0f };
	Transform.Rotation = SQuaternion{ 0.0f, 1.0f, 0.0f, 0.0f };
}