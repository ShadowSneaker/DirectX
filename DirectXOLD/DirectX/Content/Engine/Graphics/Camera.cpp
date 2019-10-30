#include "Camera.h"


CCamera::CCamera(SVector4 InPosition, float InRotation)
	:Offset{ InPosition }, Rotation{ InRotation }
{
	DX = TMath::Sin(TO_RADIAN(Rotation));
	DZ = TMath::Cos(TO_RADIAN(Rotation));
}


CCamera::~CCamera()
{

}


void CCamera::Rotate(float Angle)
{
	Rotation += Angle;
	DX = TMath::Sin(TO_RADIAN(Rotation));
	DZ = TMath::Cos(TO_RADIAN(Rotation));
}


void CCamera::MoveForward(float Distance)
{
	Offset[X] += DX * Distance;
	Offset[Z] += DZ * Distance;
}


void CCamera::MoveUp(float Distance)
{
	Offset[Y] += Distance;
}


void CCamera::MoveLeft(float Distance)
{
	SVector4 Direction = SVector4::CrossProduct(Offset, LookAt);
	Offset[X] += Direction[X] * Distance;
	Offset[Z] += Direction[Z] * Distance;
}


SMatrix4 CCamera::GetViewMatrix()
{
	Position = SVector4(Offset[X], Offset[Y], Offset[Z], 0.0f);
	LookAt = SVector4(Offset[X] + DX, Offset[Y], Offset[Z] + DZ, 0.0f);
	Up = SVector4(0.0f, 1.0f, 0.0f, 0.0f);

	return SMatrix4::LookAt(Position, LookAt, Up);
}