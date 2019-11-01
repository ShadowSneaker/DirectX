#pragma once
#include "Camera.h"


CCamera::CCamera()
{
	DX = TMath::Sin(TO_RADIAN(Transform.GetWorldRotation().Y));
	DZ = TMath::Cos(TO_RADIAN(Transform.GetWorldRotation().Y));
}


void CCamera::Rotate(float Angle)
{
	Rot += Angle;
	DX = TMath::Sin(TO_RADIAN(Rot));
	DZ = TMath::Cos(TO_RADIAN(Rot));
}


void CCamera::MoveForward(float Distance)
{
	Transform.Location[X] += DX * Distance;
	Transform.Location[Z] += DZ * Distance;
	//Transform.Location[X] += TMath::Sin(TO_RADIAN(Transform.GetWorldRotation().Y)) * Distance;
	//Transform.Location[Z] += TMath::Cos(TO_RADIAN(Transform.GetWorldRotation().Y)) * Distance;
}


void CCamera::MoveUp(float Distance) 
{
	Transform.Location[Y] += Distance;
}


void CCamera::MoveRight(float Distance)
{
	SVector Q(TO_RADIAN(Rot), TO_RADIAN(Rot), TO_RADIAN(Rot));
	SVector V = SVector::Right();

	SVector T = SVector::CrossProduct(Q, V) * 2.0f;
	SVector Result = V + (T * 1.0f) + SVector::CrossProduct(Q, T);
	Transform.Location += Result * Distance;

	//SVector4 Direction = 2.0f * SVector4::CrossProduct(LookAt.Normalize(), SVector4::Up());
	//Transform.Location[X] += Direction[X] * Distance;
	//Transform.Location[Z] += Direction[Z] * Distance;

	//Transform.Location[X] -= Distance;
}


SMatrix4 CCamera::GetViewMatrix()
{
	//SVector Location{ Transform.GetWorldLocation() };
	//
	//Offset = SVector4{ Location, 0.0f };
	//LookAt = SVector4{ Location[X] + TMath::Sin(TO_RADIAN(Transform.GetWorldRotation().Y)), Location[Y], Location[Z] + TMath::Cos(TO_RADIAN(Transform.GetWorldRotation().Y)), 0.0f };
	//Up = SVector4::Up();

	Offset = SVector4(Transform.Location[X], Transform.Location[Y], Transform.Location[Z], 0.0f);
	LookAt = SVector4(Transform.Location[X] + DX, Transform.Location[Y], Transform.Location[Z] + DZ, 0.0f);
	Up = SVector4::Up();

	return SMatrix4::LookAt(Offset, LookAt, Up);
}