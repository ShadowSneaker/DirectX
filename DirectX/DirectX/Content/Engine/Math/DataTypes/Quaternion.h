#pragma once
#include "Vector.h"

//#define TO_RADIAN(x) { (float) ((x) * PI / 180.0f) }
#define TO_RADIAN(x) { (float) ((x) * (PI * 2.0f)) }
#define RADIAN { (float) (PI * 2.0f) }
#define TO_DEGREES(x) { (float) ((x) * (PI / 180.0f)) }
#define DEGREES { (float) (PI / 180.0f) }


// Quaternion
struct SQuaternion
{
public:
	/// Properties

	// The identity quaternion.
	static const SQuaternion Identity;

	// Quaternion's Pitch property.
	float X;

	// Quaternion's Yaw property.
	float Y;

	// Quaternion's Roll property.
	float Z;

	// Quaternion's W property.
	float W;


public:
	/// Constructors

	// Constructor, Default.
	SQuaternion() 
		:X{ 0.0f }, Y{ 0.0f }, Z{ 0.0f }, W{ 0.0f }
	{}

	// Constructor, Initiates all properties with the same floating point value.
	// @param InF - The floating value used to initiate all properties with.
	inline SQuaternion(float InF);

	// Constructor, Initiates all properties with specified floating point values.
	// @param InX - Initiates the X property with the inputted value.
	// @param InY - Initiates the Y property with the inputted value.
	// @param InZ - Initiates the Z property with the inputted value.
	// @param InW - Initiates the W property with the inputted value.
	inline SQuaternion(float InX, float InY, float InZ, float InW = 0.0f);

	// Constructor, Initiates all properties with a inputted vector4.
	// @param InV - The vector4 used to initiate all properties with.
	inline SQuaternion(SVector4 InV);

	// Constructor, Initiates all properties with a vector3 and a floating point value.
	// @param InV - The vector3 used to initiate the X, Y and Z properties.
	// @param InW - The floating point value used to initiate the W property.
	inline SQuaternion(SVector InV, float InW = 0.0f);


	/// Operators

	// 
	inline SQuaternion operator+(const SQuaternion& Q) const;

	// 
	inline SQuaternion operator+=(const SQuaternion& Q);

	// 
	inline SQuaternion operator-(const SQuaternion& Q) const;

	// 
	inline SQuaternion operator-=(const SQuaternion& Q);

	// 
	inline SQuaternion operator*(const SQuaternion& Q) const;

	// 
	inline SQuaternion operator*=(const SQuaternion& Q);

	// 
	inline SVector operator*(const SVector& V) const;

	// 
	inline SQuaternion operator*(const float& F) const;

	// 
	inline SQuaternion operator*=(const float& F);

	// 
	inline SQuaternion operator/(const float& F) const;

	// 
	inline SQuaternion operator/=(const float& F);

	// 
	inline bool operator==(const SQuaternion& Q) const;

	// 
	inline bool operator!=(const SQuaternion& Q) const;

	// 
	inline float operator|(const SQuaternion& Q) const;

	// 
	inline SQuaternion operator=(const SVector& V);

	// 
	inline SQuaternion operator=(const SVector4& V);

	// 
	inline float operator[](const uint& Axis) const;

	// 
	inline float& operator[](const uint& Axis);


	/// Conversions


	/// Functions
};





inline SQuaternion::SQuaternion(float InF)
	: X{ InF }, Y{ InF }, Z{ InF }, W{ InF }
{}


inline SQuaternion::SQuaternion(float InX, float InY, float InZ, float InW)
	: X{ InX }, Y{ InY }, Z{ InZ }, W{ InW }
{}


inline SQuaternion::SQuaternion(SVector4 InV)
	: X{ InV[EAxis::X] }, Y{ InV[EAxis::Y] }, Z{ InV[EAxis::Z] }, W{ InV[EAxis::W] }
{}


inline SQuaternion::SQuaternion(SVector InV, float InW)
	: X{ InV[EAxis::X] }, Y{ InV[EAxis::Y] }, Z{ InV[EAxis::Z] }, W{ InW }
{}


inline SQuaternion SQuaternion::operator+(const SQuaternion& Q) const
{
	return SQuaternion
	{
		X + Q.X,
		Y + Q.Y,
		Z + Q.Z,
		W + Q.W
	};
}


inline SQuaternion SQuaternion::operator+=(const SQuaternion& Q)
{
	X += Q.X;
	Y += Q.Y;
	Z += Q.Z;
	W += Q.W;
	return *this;
}


inline SQuaternion SQuaternion::operator-(const SQuaternion& Q) const
{
	return SQuaternion
	{
		X - Q.X,
		Y - Q.Y,
		Z - Q.Z,
		W - Q.W
	};
}


inline SQuaternion SQuaternion::operator-=(const SQuaternion& Q)
{
	X -= Q.X;
	Y -= Q.Y;
	Z -= Q.Z;
	W -= Q.W;
	return *this;
}


inline SQuaternion SQuaternion::operator*(const SQuaternion& Q) const
{
	// NOT FINISHED
	return SQuaternion();
}


inline SQuaternion SQuaternion::operator*=(const SQuaternion& Q)
{
	// NOT FINISHED
	return SQuaternion();
}


inline SVector SQuaternion::operator*(const SVector& V) const
{
	// NOT FINISHED
	return SVector();
}


inline SQuaternion SQuaternion::operator*(const float& F) const
{
	return SQuaternion
	{
		X * F,
		Y * F,
		Z * F,
		W * F
	};
}


inline SQuaternion SQuaternion::operator*=(const float& F)
{
	X *= F;
	Y *= F;
	Z *= F;
	W *= F;
	return *this;
}


inline SQuaternion SQuaternion::operator/(const float& F) const
{
	const float Recip{ 1.0f / F };
	return SQuaternion
	{
		X * Recip,
		Y * Recip,
		Z * Recip,
		W * Recip
	};
}


inline SQuaternion SQuaternion::operator/=(const float& F)
{
	const float Recip{ 1.0f / F };
	X *= Recip;
	Y *= Recip;
	Z *= Recip;
	W *= Recip;
	return *this;
}


inline bool SQuaternion::operator==(const SQuaternion& Q) const
{
	return
		(
			X == Q.X &&
			Y == Q.Y &&
			Z == Q.Z &&
			W == Q.W
			);
}


inline bool SQuaternion::operator!=(const SQuaternion& Q) const
{
	return
		(
			X != Q.X ||
			Y != Q.Y ||
			Z != Q.Z ||
			W != Q.W
			);
}


inline float SQuaternion::operator|(const SQuaternion& Q) const
{
	return
		(
		(X * Q.X) +
			(Y * Q.Y) +
			(Z + Q.Z) +
			(W + Q.W)
			);
}


inline SQuaternion SQuaternion::operator=(const SVector& V)
{
	X = V[EAxis::X];
	Y = V[EAxis::Y];
	Z = V[EAxis::Z];
	return *this;
}


inline SQuaternion SQuaternion::operator=(const SVector4& V)
{
	X = V[EAxis::X]; \
		Y = V[EAxis::Y];
	Z = V[EAxis::Z];
	W = V[EAxis::W];
	return *this;
}


inline float SQuaternion::operator[](const uint& Axis) const
{
	switch (Axis)
	{
	case 0:
		return X;

	case 1:
		return Y;

	case 2:
		return Z;

	default:
		return W;
	}
}


inline float& SQuaternion::operator[](const uint& Axis)
{
	switch (Axis)
	{
	case 0:
		return X;

	case 1:
		return Y;

	case 2:
		return Z;

	default:
		return W;
	}
}