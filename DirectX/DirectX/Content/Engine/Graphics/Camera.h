#pragma once
#include "../Math/DataTypes/Transform.h"
#include "../Math/DataTypes/Matrix.h"


// So I think the reason why the camera was rotating around a point could possibly be because it was rotating the object
// then offseting the object. This makes sense as it would cause the object to rotate around the origin point.
// Although this is still a guess and I have no idea how to fix it. 



// An object used to view the game world.
class CCamera
{
private:
	/// Properties

	// The offset in worldspace this object is at.
	SVector4 Offset{ 0.0f };

	// What the camera is looking at.
	SVector4 LookAt{ 0.0f };

	// The up vector of this camera.
	SVector4 Up = SVector4::Up();

	// The sin of the Y rotation.
	float DX{ 0.0f };

	// The cos of the Y rotation.
	float DZ{ 0.0f };

public:
	// The location, rotation and scale of the camera.
	STransform Transform;

	// Determines how close objects can get before they start clipping with the camera (The lowest value this can be is 0.001f).
	float NearClipPlane{ 0.001f };

	// Determines how far objects can get before they start dissapearing (This cannot be lower than the NearClipPlane).
	float FarClipPlane{ 1000.0f };

	// The FOV of the camera.
	float FieldOfView{ 90.0f };

	// Used for easy testing between a new and improved system (that doesn't work) or the origional system.
	bool UseLegacyControls{ true };



public:
	/// Constructors
	
	// Constructor, Default.
	CCamera();

	

	/// Functions

	// Rotates the camera.
#ifndef USE_LEGACY_CONTROLS
	DEPRECATED("Rotate function is deprecated, Define 'USE_LEGACY_CONTROLS' to enable")
#endif
	void Rotate(float X, float Y, float Z);

	// Moves the camera forward.
#ifndef USE_LEGACY_CONTROLS
	DEPRECATED("MoveForward function is deprecated, Define 'USE_LEGACY_CONTROLS' to enable")
#endif
	void MoveForward(float Distance);
#
	// Moves the camera up.
#ifndef USE_LEGACY_CONTROLS
	DEPRECATED("MoveUp function is deprecated, Define 'USE_LEGACY_CONTROLS' to enable")
#endif
	void MoveUp(float Distance);

	// Moves the camera right.
#ifndef USE_LEGACY_CONTROLS
	DEPRECATED("MoveRight function is deprecated, Define 'USE_LEGACY_CONTROLS' to enable")
#endif
	void MoveRight(float Distance);

	// Returns the view matrix of this camera.
	SMatrix4 GetViewMatrix();



	/// Getters

	// Returns the forward vector of this camera.
	SVector GetForward() const;

	// Returns the right vector of this camera.
	SVector GetRight() const;
};