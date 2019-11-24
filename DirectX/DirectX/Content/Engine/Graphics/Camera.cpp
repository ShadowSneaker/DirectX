#pragma once
#include "Camera.h"


CCamera::CCamera()
{
	if (UseLegacyControls)
	{
		DX = TMath::Sin(Transform.Rotation.Y);
		DZ = TMath::Cos(Transform.Rotation.Y);
	}
}


void CCamera::Rotate(float X, float Y, float Z)
{
	if (UseLegacyControls)
	{
		Transform.Rotation.Y += Y;
		DX = TMath::Sin(Transform.Rotation.Y);
		DZ = TMath::Cos(Transform.Rotation.Y);
	}
	else
	{
		//Transform.Rotation.X += X;
		//Transform.Rotation.Y += Y;
		//Transform.Rotation.Z += Z;
		SQuaternion Euler = SQuaternion::Euler(SVector{ X, Y, Z });
		Transform.Rotation += Euler;
		Transform.Rotation.W = Euler.W;
		//Transform.Rotation.W = SQuaternion::Euler(SVector{ X, Y, Z } + Transform.Rotation.ToEuler()).W;


		//SMatrix4 Rot;
		//Rot.Identity();
		//Rot.SetRotate(Transform.Rotation + SQuaternion{ X, Y, Z, 0.0f });
		//Transform.Rotation = Rot.ToVector();
	}
}


void CCamera::MoveForward(float Distance)
{
	//Transform.Location += Transform.Forward() * Distance;
	if (UseLegacyControls)
	{
		Transform.Location[X] += DX * Distance;
		Transform.Location[Z] += DZ * Distance;
	}
	else
	{
		Transform.Location += Transform.Forward() * Distance;
	}
}


void CCamera::MoveUp(float Distance) 
{
	//Transform.Location += Transform.Up() * Distance;
	if (UseLegacyControls)
	{
		Transform.Location[Y] += Distance;
	}
	else
	{
		Transform.Location += Transform.Up() * Distance;
	}
}


void CCamera::MoveRight(float Distance)
{
	//SVector Right{ Transform.Right() };
	//Transform.Location += Right * Distance;
	if (UseLegacyControls)
	{
		SVector4 Look{ DX, 0.0f, DZ, 0.0f };
		SVector4 Direction = SVector4::CrossProduct(Look, SVector4::Up());
		Transform.Location[X] += Direction[X] * -Distance;
		Transform.Location[Z] += Direction[Z] * -Distance;
	}
	else
	{
		Transform.Location += Transform.Right() * Distance;
	}
}


SMatrix4 CCamera::GetViewMatrix()
{
	if (UseLegacyControls)
	{
		SVector4 WorldLocation{ Transform.GetWorldLocation(), 0.0f };

		//Offset = SVector4{ Transform.Location, 0.0f };
		Offset = WorldLocation;
		LookAt = SVector4{ WorldLocation[X] + DX, WorldLocation[Y], WorldLocation[Z] + DZ, 0.0f };
		Up = SVector4{ SVector4::Up() };
	}
	else
	{
		SVector Forward{ 0.0f };
		Forward[X] = TMath::Sin(Transform.Rotation.X);
		Forward[Y] = TMath::Sin(Transform.Rotation.Y);
		Forward[Z] = TMath::Cos(Transform.Rotation.Z);

		Offset = SVector4{ Transform.Location, 0.0f };
		//LookAt = SVector4{ Transform.Location[X] + Forward[X], Transform.Location[Y] + Forward[Y], Transform.Location[Z] + Forward[Z], 0.0f };
		LookAt = SVector4{ Transform.Location + Transform.Forward(), 0.0f };
		Up = SVector4{ Transform.Up(), 0.0f };
	}
	return SMatrix4::LookAt(Offset, LookAt, Up);
}