#pragma once
#include "../Math/DataTypes/Transform.h"
#include "../Math/DataTypes/Matrix.h"


class CCamera
{
private:
	/// Properties

	SVector4 Offset{ 0.0f };
	SVector4 LookAt{ 0.0f };
	SVector4 Up = SVector4::Up();


	float DX{ 0.0f };
	float DZ{ 0.0f };
	float Rot{ 0.0f };


public:
	STransform Transform;

	// Determines how close objects can get before they start clipping with the camera (The lowest value this can be is 0.001f).
	float NearClipPlane{ 0.001f };

	// Determines how far objects can get before they start dissapearing (This cannot be lower than the NearClipPlane).
	float FarClipPlane{ 1000.0f };


public:
	/// Constructors
	CCamera();

	

	/// Functions


	void Rotate(float Angle);

	void MoveForward(float Distance);

	void MoveUp(float Distance);

	void MoveRight(float Distance);

	SMatrix4 GetViewMatrix();

};