#pragma once
#include "../Math/DataTypes/Matrix.h"


class CCamera
{
private:
	/// Properties

	SVector Offset;
	//SVector Position;
	//SVector LookAt;

	//SVector Up;

	DirectX::XMVECTOR Position;
	DirectX::XMVECTOR LookAt;
	DirectX::XMVECTOR UP;


	float DX;
	float DZ;
	float Rotation;




public:
	/// Constructor
	
	// Constructor, Default.
	CCamera(SVector InPos, float InRotation);

	// Destructor.
	~CCamera();


public:
	/// Functions

	void Rotate(float Angle);

	void Forward(float Distance);

	void Up(float Distance);

	//SMatrix4 GetViewMatrix()
	DirectX::XMMATRIX GetViewMatrix();
};