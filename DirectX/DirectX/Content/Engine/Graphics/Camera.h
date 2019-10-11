#pragma once
#include "../Math/DataTypes/Matrix.h"


class CCamera
{
private:
	/// Properties

	SVector4 Offset;
	SVector4 Position;
	SVector4 LookAt;
	SVector4 Up;


	//DirectX::XMVECTOR Position;
	//DirectX::XMVECTOR LookAt;
	//DirectX::XMVECTOR UP;


	float DX;
	float DZ;
	float Rotation;




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