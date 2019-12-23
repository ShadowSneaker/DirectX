#pragma once
#include "Camera.h"


CCamera::CCamera()
{
	//Transform.Rotation.X = TMath::Sin(TO_RADIAN(90.0f));

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
		STransform WorldTransform{ Transform.GetWorldTransform() };
		SVector4 WorldLocation{ WorldTransform.Location, 0.0f };
		//SVector4 WorldLocation{ Transform.Location, 0.0f };

		//DX = TMath::Sin(Transform.Forward());
		//DZ = TMath::Cos(Transform.Forward());
		DX = TMath::Sin(WorldTransform.Rotation.Y);
		DZ = TMath::Cos(WorldTransform.Rotation.Y);
		
		Offset = WorldLocation;
		LookAt = SVector4{ WorldLocation[X] + DX, WorldLocation[Y], WorldLocation[Z] + DZ, 0.0f };
		Up = SVector4{ Transform.Up() };
	}
	else
	{
		STransform WorldTransform{ Transform.GetWorldTransform() };

		Offset = WorldTransform.Location;

		LookAt = Offset + WorldTransform.Rotation.GetAxisZ();
		Up = Transform.Up();
	}
	return SMatrix4::LookAt(Offset, LookAt, Up);
}


SVector CCamera::GetForward() const
{
	return SVector{ DX, 0.0f, DZ };
}


SVector CCamera::GetRight() const
{
	return -SVector::CrossProduct(GetForward(), SVector::Up());
}