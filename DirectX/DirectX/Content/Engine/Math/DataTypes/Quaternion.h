#pragma once
#include "Vector.h"
#include "../MathStatics.h"



// Quaternion
struct SQuaternion
{
public:
	/// Static Properties

	// Identity quaternion.
	static const SQuaternion Identity;


public:
	/// Properties

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

	// Copy Consturctor, Initiates the quaternion using another quaternion.
	inline SQuaternion(const SQuaternion& Quaternion);

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

	// Checks to see if this quaternion is an identity quaternion.
	// @param Tolerance - Determines how close this quaternion can be to register as an indentity quaternion.
	// @return - Returns true if this quaternion is an indentity quaternion.
	inline bool IsIdentity(float Tolerance = SMALL_NUMBER) const;

	// Checks to see if thsi quaternion is almost the same value as another quaternion.
	// @param Other - The other quaternion to compare against.
	// @param Tolerance - Determines how close this quaternion can be to the other quaternion.
	// @return - Returns true if theis quaternion is within range of the other quaternion.
	inline bool NearlyEqual(SQuaternion Other, float Tolerance = MICRO_NUMBER) const;

	// Converts this quaternion to Euler angles (degrees).
	SVector Euler() const;

	// Normalizes this quaternion if it is large enough.
	// If this quaternion is too small, it will return an identity quaternion.
	// @param Tolerance - The minimum squared length of this quaternion for normalization.
	inline void Normalize(float Tolerance = SMALL_NUMBER);

	// 
	inline float NormalizeAxis(float Axis) const;

	// Rotates a vector by this quaternion.
	// @param V - The vector to be rotated.
	// @return - The vector after the rotation.
	SVector RotateVector(SVector V) const;

	// Rotates a vector by the inverse of this quaternion
	// @param V - The vector to be rotated.
	// @return - The vector after the rotation by the inverse of this quaternion.
	SVector UnrotateVector(SVector V) const;

	// @return - Returns this quaternion with W = 0.0f and V = theta * v.
	SQuaternion Log() const;

	// @note - Exp should only be used after Log().
	SQuaternion Exp() const;

	// Returns the inverse of this quaternion.
	inline SQuaternion Inverse() const;

	// Enforce that the delta between this quaternion and another one represents the shortest possible rotation angle.
	void EnforceShortestArcWidth(const SQuaternion& Other);

	// Utility check to make sure there aren't any non-finite values (NaN or Infinity) in this quaternion.
	// @return - Returns true if there are no non-finite values in this quaternion, otherwise false.
	bool ContainsNaN() const;

	// 
	inline float ClampAxis(float Angle) const;


	/// Getters

	// Gets a normalized copy of this quaternion.
	// If this quaternion is too small it will return an identity quaternion.
	// @param Tolerance - The minimum squared length of this quaternion for normalization.
	// @return - The normalized copy of this quaternion.
	inline SQuaternion GetNormalized(float Tolerance = SMALL_NUMBER) const;

	// Returns true if this quaternion is normalized.
	bool IsNormalized() const;

	// Returns the legnth of this quaternion.
	inline float Size() const;

	// Returns the squared length of this quaternion.
	inline float SizeSquared() const;

	// Returns the angle of this quaternion.
	inline float GetAngle() const;

	// Gets the axis and angle of rotation of this quaternion.
	// @param Axis [out] - vector of axis of the quaternion.
	// @param Angle [out] - Angle of the quaternion.
	// @warning - Assumes normalized quaternions.
	void ToAxisAndAngle(SVector& Axis, float& Angle) const;

	// Gets the swing and twist decomposition for a specified axis.
	// @param InTwistAxis - Axis to use for decomposition.
	// @param Swing [out] - Swing component quaternion.
	// @param Twist [out] - Twist component quaternion.
	// @warning - Assumes normalized quaternion and twist axis.
	void ToSwingTwist(const SVector& InTwistAxis, SQuaternion& Swing, SQuaternion& Twist) const;

	// Returns the right direction (X axis) after it has been rotated by this quaternion.
	inline SVector GetAxisX() const;

	// Returns the up direction (Y axis) after it has been rotated by this quaternion.
	inline SVector GetAxisY() const;

	// Returns the forward direction (Z axis) after it has been rotated by this quaternion.
	inline SVector GetAxisZ() const;

	// Returns the right direction (X axis) after it has been rotated by this quaternion.
	inline SVector GetRightVector() const;

	// Returns the up direction (Y axis) after it has been rotated by this quaternion.
	inline SVector GetUpVector() const;

	// Returns the forward direction (Z axis) after it has been rotated by this quaternion.
	inline SVector GetForwardVector() const;

	// Converts a rotation into a unit vector facing in it's direction. Equivalent to GetForwardVector().
	inline SVector Vector() const;

	// Returns the axis of rotation of the quaternion.
	// This is the axis around which the rotation occurs to transform the canonical coordinate system to the target orientation.
	// For the identity quaternion whihc has no such rotation, FVector(1.0f, 1.0f, 1.0f) is returned.
	inline SVector GetRotationAxis() const;

	// Find the angular distance between two rotation quaternions (in radians).
	inline float AngularDistance(const SQuaternion& Quaternion) const;

	inline SVector4 GetAsVector() const;



	/// Statics

	inline static bool NearlyEqual(SQuaternion A, SQuaternion B, float Tolerance = MICRO_NUMBER)
	{
		return A.NearlyEqual(B, Tolerance);
	}


	// Converts a float vector of Euler angles (degrees) into a Quaternion.
	// @param Vector - A vector of Eular angles.
	// @return - The constructor quaternion.
	static SQuaternion Euler(const SVector& Vector)
	{
		const float DivideBy2 = (TMath::Pi / 180.0f) / 2;

		float SPitch;
		float SYaw;
		float SRoll;

		float CPitch;
		float CYaw;
		float CRoll;

		TMath::SinCos(&SPitch, &CPitch, Vector[EAxis::X] * DivideBy2);
		TMath::SinCos(&SYaw, &CYaw, Vector[EAxis::Y] * DivideBy2);
		TMath::SinCos(&SRoll, &CRoll, Vector[EAxis::Z] * DivideBy2);

		SQuaternion Result;
		Result.X = (CRoll * SPitch * SYaw) - (SRoll * CPitch * CYaw);
		Result.Y = (-CRoll * SPitch * CYaw) - (SRoll * CPitch * SYaw);
		Result.Z = (CRoll * CPitch * SYaw) - (SRoll * SPitch * CYaw);
		Result.W = (CRoll * CPitch * CYaw) + (SRoll * SPitch * SYaw);

		return Result;
	}
};




inline SQuaternion::SQuaternion(const SQuaternion& Q)
	:X{ Q.X }, Y{ Q.Y }, Z{ Q.Z }, W{ Q.W }
{}


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
	X = V[EAxis::X];
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


inline bool SQuaternion::IsIdentity(float Tolerance) const
{
	return NearlyEqual(SQuaternion::Identity, Tolerance);
}


inline bool SQuaternion::NearlyEqual(SQuaternion Other, float Tolerance) const
{
	return TMath::Abs(X - Other.X <= Tolerance && TMath::Abs(Y - Other.Y) <= Tolerance && TMath::Abs(Z - Other.Z) <= Tolerance && TMath::Abs(W - Other.W) <= Tolerance)
		|| (TMath::Abs(X + Other.X) <= Tolerance && TMath::Abs(Y + Other.Y) <= Tolerance && TMath::Abs(Z + Other.Z) <= Tolerance && TMath::Abs(W + Other.W) <= Tolerance);
}


inline void SQuaternion::Normalize(float Tolerance)
{
	const float SquareSum{ (X * X) + (Y * Y) + (Z * Z) + (W * W) };
	if (SquareSum >= Tolerance)
	{
		const float Scale{ TMath::InvSqrt(SquareSum) };
		X *= Scale;
		Y *= Scale;
		Z *= Scale;
		W *= Scale;
	}
	else
	{
		*this = SQuaternion::Identity;
	}
}


inline float SQuaternion::NormalizeAxis(float Angle) const
{
	Angle = ClampAxis(Angle);

	if (Angle > 180.0f)
	{
		Angle -= 360.0f;
	}
	return Angle;
}


inline SVector SQuaternion::RotateVector(SVector V) const
{
	// http://people.csail.mit.edu/bkph/articles/Quaternions.pdf
	// V' = V + 2w(Q x V) + (2Q x (Q x V))
	// refactor:
	// V' = V + w(2(Q x V)) + (Q x (2(Q x V)))
	// T = 2(Q x V);
	// V' = V + w*(T) + (Q x T)

	const SVector Quat{ X, Y, Z };
	SVector T{ SVector::CrossProduct(Quat, V) * 2.0f };
	return SVector{ V + (T * W) + SVector::CrossProduct(Quat, T) };
}


inline SVector SQuaternion::UnrotateVector(SVector V) const
{
	const SVector Quat{ -X, -Y, -Z };
	const SVector T{ SVector::CrossProduct(Quat, V) * 2.0f };
	return SVector{ V + (T * W) + SVector::CrossProduct(Quat, T) };
}


inline SQuaternion SQuaternion::Inverse() const
{
	if (IsNormalized())
	{
		return SQuaternion{ -X, -Y, -Z, W };
	}
	return SQuaternion{};
}


inline void SQuaternion::EnforceShortestArcWidth(const SQuaternion& Other)
{
	const float DotResult{ (Other | *this) };
	const float Bias{ TMath::FloatSelect(DotResult, 1.0f, -1.0f) };
	X *= Bias;
	Y *= Bias;
	Z *= Bias;
	W *= Bias;
}


inline bool SQuaternion::ContainsNaN() const
{
	return
		(
			!TMath::IsFinite(X) ||
			!TMath::IsFinite(Y) ||
			!TMath::IsFinite(Z) ||
			!TMath::IsFinite(W)
			);
}


inline float SQuaternion::ClampAxis(float Angle) const
{
	Angle = TMath::FMod(Angle, 360.0f);
	if (Angle < 0.0f)
	{
		Angle += 360.0f;
	}
	return Angle;
}


inline SQuaternion SQuaternion::GetNormalized(float Tolerance) const
{
	SQuaternion Result{ *this };
	Result.Normalize(Tolerance);
	return Result;
}


inline bool SQuaternion::IsNormalized() const
{
	return (TMath::Abs(1.0f - SizeSquared()) < 0.01f);
}


inline float SQuaternion::Size() const
{
	return TMath::Sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));
}


inline float SQuaternion::SizeSquared() const
{
	return ((X * X) + (Y * Y) + (Z * Z) + (W * W));
}


inline float SQuaternion::GetAngle() const
{
	return 2.0f * TMath::ACos(W);
}


inline void SQuaternion::ToAxisAndAngle(SVector& Axis, float& Angle) const
{
	Angle = GetAngle();
	Axis = GetRotationAxis();
}


inline SVector SQuaternion::GetAxisX() const
{
	return RotateVector(SVector::Right());
}


inline SVector SQuaternion::GetAxisY() const
{
	return RotateVector(SVector::Up());
}


inline SVector SQuaternion::GetAxisZ() const
{
	return RotateVector(SVector::Forward());
}


inline SVector SQuaternion::GetRightVector() const
{
	return GetAxisX();
}


inline SVector SQuaternion::GetUpVector() const
{
	return GetAxisY();
}


inline SVector SQuaternion::GetForwardVector() const
{
	return GetAxisZ();
}


inline SVector SQuaternion::Vector() const
{
	return GetAxisX();
}


inline SVector SQuaternion::GetRotationAxis() const
{
	const float S{ TMath::Sqrt(TMath::Max(1.0f - (W * W), 0.0f)) };
	if (S >= 0.0001)
	{
		return SVector{ X / S, Y / S, Z / S };
	}
	return SVector::Right();
}


inline SVector4 SQuaternion::GetAsVector() const
{
	return SVector4{ X, Y, Z, W };
}