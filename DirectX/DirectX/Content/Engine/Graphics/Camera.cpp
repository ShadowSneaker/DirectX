#include "Camera.h"


CCamera::CCamera(SVector InPosition, float InRotation)
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
	Rotation = Angle;
}


void CCamera::Forward(float Distance)
{
	Offset[X] = DX * Distance;
	Offset[Z] = DZ * Distance;
}


void CCamera::Up(float Distance)
{
	Offset[Y] = Distance;
}


//SMatrix4 CCamera::GetViewMatrix()
DirectX::XMMATRIX CCamera::GetViewMatrix()
{
	//Position = Vector<4, uint>(Offset[X], Offset[Y], Offset[Z], 0.0f).ToFloat();
	//LookAt = Vector<4, uint>(Offset[X] + DX, Offset[Y], Offset[Z] + DZ, 0.0f).ToFloat();
	//UP = Vector<4, uint>(0.0f, 1.0f, 0.0f, 0.0f).ToFloat();

	//return SMatrix4::LookAt(Position, LookAt, UP);
	
	Position = DirectX::XMVectorSet(Offset[X], Offset[Y], Offset[Z], 0.0f);
	LookAt = DirectX::XMVectorSet(Offset[X] + DX, Offset[Y], Offset[Z] + DZ, 0.0f);
	UP = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	return DirectX::XMMatrixLookAtLH(Position, LookAt, UP);
}