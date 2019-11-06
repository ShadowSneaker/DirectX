#pragma once
#include "Camera.h"


CCamera::CCamera()
{
	DX = TMath::Sin(Transform.Rotation.Y);
	DZ = TMath::Cos(Transform.Rotation.Y);
}


void CCamera::Rotate(float Angle)
{
	Transform.Rotation.Y += Angle;
	DX = TMath::Sin(Transform.Rotation.Y);
	DZ = TMath::Cos(Transform.Rotation.Y);
}


void CCamera::MoveForward(float Distance)
{
	//Transform.Location += Transform.Forward() * Distance;

	Transform.Location[X] += DX * Distance;
	Transform.Location[Z] += DZ * Distance;
}


void CCamera::MoveUp(float Distance) 
{
	Transform.Location[Y] += Distance;
	//Transform.Location += Transform.Up() * Distance;
}


void CCamera::MoveRight(float Distance)
{
	SVector4 Look{ DX, 0.0f, DZ, 0.0f };
	SVector4 Direction = SVector4::CrossProduct(Look, SVector4::Up());
	Transform.Location[X] += Direction[X] * -Distance;
	Transform.Location[Z] += Direction[Z] * -Distance;
}


SMatrix4 CCamera::GetViewMatrix()
{
	Offset = SVector4{ Transform.Location[X], Transform.Location[Y], Transform.Location[Z], 0.0f };
	LookAt = SVector4{ Transform.Location[X] + DX, Transform.Location[Y], Transform.Location[Z] + DZ, 0.0f };
	Up = SVector4{ SVector4::Up() };

	return SMatrix4::LookAt(Offset, LookAt, Up);
}