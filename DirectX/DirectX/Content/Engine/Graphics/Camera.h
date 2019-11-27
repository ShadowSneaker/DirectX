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

	float FieldOfView{ 90.0f };

	bool UseLegacyControls{ true };


public:
	/// Constructors
	CCamera();

	

	/// Functions


#ifndef USE_LEGACY_CONTROLS
	DEPRECATED("Rotate function is deprecated, Define 'USE_LEGACY_CONTROLS' to enable")
#endif
	void Rotate(float X, float Y, float Z);

#ifndef USE_LEGACY_CONTROLS
	DEPRECATED("MoveForward function is deprecated, Define 'USE_LEGACY_CONTROLS' to enable")
#endif
	void MoveForward(float Distance);

#ifndef USE_LEGACY_CONTROLS
	DEPRECATED("MoveUp function is deprecated, Define 'USE_LEGACY_CONTROLS' to enable")
#endif
	void MoveUp(float Distance);

#ifndef USE_LEGACY_CONTROLS
	DEPRECATED("MoveRight function is deprecated, Define 'USE_LEGACY_CONTROLS' to enable")
#endif
	void MoveRight(float Distance);

	SMatrix4 GetViewMatrix();

	/// Getters

	

};