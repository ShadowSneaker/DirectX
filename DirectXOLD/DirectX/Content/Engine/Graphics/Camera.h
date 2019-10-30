#pragma once
#include "../Math/DataTypes/Matrix.h"


class CCamera
{
private:
	/// Properties

	SVector4 Offset;// { 0.0f };
	SVector4 Position;// { 0.0f };
	SVector4 LookAt;// { 0.0f, 0.0f, -4.0f, 0.0f };
	SVector4 Up;// = SVector4::Up();


	//DirectX::XMVECTOR Position;
	//DirectX::XMVECTOR LookAt;
	//DirectX::XMVECTOR UP;


	float DX;
	float DZ;
	float Rotation;


public:
	float NearClipPlane{ 0.0001f };
	float FarClipPlane{ 10000.0f };



public:
	/// Constructor
	
	// Constructor, Default.
	CCamera(SVector4 InPos, float InRotation);

	// Destructor.
	~CCamera();


public:
	/// Functions

	void Rotate(float Angle);

	void MoveForward(float Distance);

	void MoveUp(float Distance);

	void MoveLeft(float Distance);

	SMatrix4 GetViewMatrix();;
	//DirectX::XMMATRIX GetViewMatrix();
};