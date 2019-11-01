#pragma once
#include "Camera.h"


CCamera::CCamera()
{
	//DX = TMath::Sin(TO_RADIAN(Transform.GetWorldRotation().Y));
	//DZ = TMath::Cos(TO_RADIAN(Transform.GetWorldRotation().Y));
}


void CCamera::Rotate(float Angle)
{
	Transform.Rotation.Z += Angle;
	//DX = TMath::Sin(TO_RADIAN(Transform.GetWorldRotation().Y));
	//DZ = TMath::Cos(TO_RADIAN(Transform.GetWorldRotation().Y));
}


void CCamera::MoveForward(float Distance)
{
	//Transform.Location[X] += DX * Distance;
	//Transform.Location[Z] += DZ * Distance;
	Transform.Location[X] += TMath::Sin(TO_RADIAN(Transform.GetWorldRotation().Y)) * Distance;
	Transform.Location[Z] += TMath::Cos(TO_RADIAN(Transform.GetWorldRotation().Y)) * Distance;
}


void CCamera::MoveUp(float Distance) 
{
	Transform.Location[Y] += Distance;
}


void CCamera::MoveRight(float Distance)
{
	SVector4 Direction = SVector4::CrossProduct(LookAt.Normalize(), SVector4::Up());
	Transform.Location[X] += Direction[X] * Distance;
	Transform.Location[Z] += Direction[Z] * Distance;

	//Transform.Location[X] -= Distance;
}


SMatrix4 CCamera::GetViewMatrix()
{
	SVector Location{ Transform.GetWorldLocation() };

	Offset = SVector4{ Location, 0.0f };
	LookAt = SVector4{ Location[X] + TMath::Sin(TO_RADIAN(Transform.GetWorldRotation().Y)), Location[Y], Location[Z] + TMath::Cos(TO_RADIAN(Transform.GetWorldRotation().Y)), 0.0f };
	Up = SVector4::Up();

	return SMatrix4::LookAt(Offset, LookAt, Up);
}