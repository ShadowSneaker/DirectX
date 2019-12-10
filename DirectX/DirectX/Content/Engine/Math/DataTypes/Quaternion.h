#pragma once
#include "Vector.h"
#include "../MathStatics.h"



// A datatype used to represent a rotation in radians
// @template - The datatype used for this quaternion.
template <typename Type>
struct Quaternion
{
public:
	/// Static Properties

	// Identity quaternion of floats.
	static const Quaternion<float> Identity;

	// Identity quaternion of doubles.
	static const Quaternion<double> IdentityDouble;


public:
	/// Properties

	// Quaternion's Pitch property.
	Type X;

	// Quaternion's Yaw property.
	Type Y;

	// Quaternion's Roll property.
	Type Z;

	// Quaternion's W property.
	Type W;


public:
	/// Constructors

	// Constructor, Default.
	Quaternion()
		:X{ (Type)0.0f }, Y{ (Type)0.0f }, Z{ (Type)0.0f }, W{ (Type)0.0f }
	{}

	// Copy Consturctor, Initiates the quaternion using another quaternion.
	inline Quaternion(const Quaternion<Type>& Quaternion);

	// Constructor, Initiates all properties with the same floating point value.
	// @param InF - The floating value used to initiate all properties with.
	inline Quaternion(Type InF);

	// Constructor, Initiates all properties with specified floating point values.
	// @param InX - Initiates the X property with the inputted value.
	// @param InY - Initiates the Y property with the inputted value.
	// @param InZ - Initiates the Z property with the inputted value.
	// @param InW - Initiates the W property with the inputted value.
	inline Quaternion(Type InX, Type InY, Type InZ, Type InW = 0.0f);

	// Constructor, Initiates all properties with a inputted vector4.
	// @param InV - The vector4 used to initiate all properties with.
	inline Quaternion(Vector<4, Type> InV);

	// Constructor, Initiates all properties with a vector3 and a floating point value.
	// @param InV - The vector3 used to initiate the X, Y and Z properties.
	// @param InW - The floating point value used to initiate the W property.
	inline Quaternion(Vector<3, Type> InV, Type InW = 0.0f);


	/// Operators

	// 
	inline Quaternion<Type> operator+(const Quaternion<Type>& Q) const;

	// 
	inline Quaternion<Type> operator+=(const Quaternion<Type>& Q);

	// 
	inline Quaternion<Type> operator-(const Quaternion<Type>& Q) const;

	// 
	inline Quaternion<Type> operator-=(const Quaternion<Type>& Q);

	// 
	inline Quaternion<Type> operator*(const Quaternion<Type>& Q) const;

	// 
	inline Quaternion<Type> operator*=(const Quaternion<Type>& Q);

	// 
	inline Vector<3, Type> operator*(const Vector<3, Type>& V) const;

	// 
	inline Quaternion<Type> operator*(const Type& F) const;

	// 
	inline Quaternion<Type> operator*=(const Type& F);

	// 
	inline Quaternion<Type> operator/(const Type& F) const;

	// 
	inline Quaternion<Type> operator/=(const Type& F);

	// 
	inline bool operator==(const Quaternion<Type>& Q) const;

	// 
	inline bool operator!=(const Quaternion<Type>& Q) const;

	// 
	inline Type operator|(const Quaternion<Type>& Q) const;

	// 
	inline Quaternion<Type> operator=(const Vector<3, Type>& V);

	// 
	inline Quaternion<Type> operator=(const Vector<4, Type>& V);

	// 
	inline Type operator[](const uint& Axis) const;

	// 
	inline Type& operator[](const uint& Axis);


	/// Conversions


	/// Debug

	inline void CheckNaN() const
	{
		if (ContainsNaN())
		{
			printf("Quaternion contains NaN");
			*const_cast<Quaternion<Type>*>(this) = Quaternion<Type>::Identity;
		}
	}


	/// Functions

	// Checks to see if this quaternion is an identity quaternion.
	// @param Tolerance - Determines how close this quaternion can be to register as an indentity quaternion.
	// @return - Returns true if this quaternion is an indentity quaternion.
	inline bool IsIdentity(Type Tolerance = SMALL_NUMBER) const;

	// Checks to see if thsi quaternion is almost the same value as another quaternion.
	// @param Other - The other quaternion to compare against.
	// @param Tolerance - Determines how close this quaternion can be to the other quaternion.
	// @return - Returns true if theis quaternion is within range of the other quaternion.
	inline bool NearlyEqual(Quaternion<Type> Other, Type Tolerance = MICRO_NUMBER) const;

	// Converts this quaternion to Euler angles (degrees).
	Vector<3, Type> ToEuler() const;

	// Normalizes this quaternion if it is large enough.
	// If this quaternion is too small, it will return an identity quaternion.
	// @param Tolerance - The minimum squared length of this quaternion for normalization.
	inline void Normalize(Type Tolerance = SMALL_NUMBER);

	// 
	inline Type NormalizeAxis(Type Axis) const;

	// Rotates a vector by this quaternion.
	// @param V - The vector to be rotated.
	// @return - The vector after the rotation.
	Vector<3, Type> RotateVector(Vector<3, Type> V) const;

	// Rotates a vector by the inverse of this quaternion
	// @param V - The vector to be rotated.
	// @return - The vector after the rotation by the inverse of this quaternion.
	Vector<3, Type> UnrotateVector(Vector<3, Type> V) const;

	// @return - Returns this quaternion with W = 0.0f and V = theta * v.
	Quaternion<Type> Log() const;

	// @note - Exp should only be used after Log().
	Quaternion<Type> Exp() const;

	// Returns the inverse of this quaternion.
	inline Quaternion<Type> Inverse() const;

	// Enforce that the delta between this quaternion and another one represents the shortest possible rotation angle.
	void EnforceShortestArcWidth(const Quaternion<Type>& Other);

	// Utility check to make sure there aren't any non-finite values (NaN or Infinity) in this quaternion.
	// @return - Returns true if there are no non-finite values in this quaternion, otherwise false.
	bool ContainsNaN() const;

	// 
	inline Type ClampAxis(Type Angle) const;

	Quaternion<Type> Rotate(Type InX, Type InY, Type InZ);

	Quaternion<Type> Rotate(Quaternion<Type> Quaternion);

	Quaternion<Type> Rotate(Vector<3, Type> Vector);

	Quaternion<Type> RotateEuler(Type InX, Type InY, Type InZ);

	Quaternion<Type> RotateEuler(Vector<3, Type> Vector);

	inline void Print() const;


	/// Getters

	// Gets a normalized copy of this quaternion.
	// If this quaternion is too small it will return an identity quaternion.
	// @param Tolerance - The minimum squared length of this quaternion for normalization.
	// @return - The normalized copy of this quaternion.
	inline Quaternion<Type> GetNormalized(Type Tolerance = SMALL_NUMBER) const;

	// Returns true if this quaternion is normalized.
	bool IsNormalized() const;

	// Returns the legnth of this quaternion.
	inline Type Size() const;

	// Returns the squared length of this quaternion.
	inline Type SizeSquared() const;

	// Returns the angle of this quaternion.
	inline Type GetAngle() const;

	// Gets the axis and angle of rotation of this quaternion.
	// @param Axis [out] - vector of axis of the quaternion.
	// @param Angle [out] - Angle of the quaternion.
	// @warning - Assumes normalized quaternions.
	void ToAxisAndAngle(Vector<3, Type>& Axis, Type& Angle) const;

	// Gets the swing and twist decomposition for a specified axis.
	// @param InTwistAxis - Axis to use for decomposition.
	// @param Swing [out] - Swing component quaternion.
	// @param Twist [out] - Twist component quaternion.
	// @warning - Assumes normalized quaternion and twist axis.
	void ToSwingTwist(const Vector<3, Type>& InTwistAxis, Quaternion<Type>& Swing, Quaternion<Type>& Twist) const;

	// Returns the right direction (X axis) after it has been rotated by this quaternion.
	inline Vector<3, Type> GetAxisX() const;

	// Returns the up direction (Y axis) after it has been rotated by this quaternion.
	inline Vector<3, Type> GetAxisY() const;

	// Returns the forward direction (Z axis) after it has been rotated by this quaternion.
	inline Vector<3, Type> GetAxisZ() const;

	// Returns the right direction (X axis) after it has been rotated by this quaternion.
	inline Vector<3, Type> GetRightVector() const;

	// Returns the up direction (Y axis) after it has been rotated by this quaternion.
	inline Vector<3, Type> GetUpVector() const;

	// Returns the forward direction (Z axis) after it has been rotated by this quaternion.
	inline Vector<3, Type> GetForwardVector() const;

	// Converts a rotation into a unit vector facing in it's direction. Equivalent to GetForwardVector().
	inline Vector<3, Type> ToVector() const;

	// Returns the axis of rotation of the quaternion.
	// This is the axis around which the rotation occurs to transform the canonical coordinate system to the target orientation.
	// For the identity quaternion whihc has no such rotation, FVector(1.0f, 1.0f, 1.0f) is returned.
	inline Vector<3, Type> GetRotationAxis() const;

	// Find the angular distance between two rotation quaternions (in radians).
	inline Type AngularDistance(const Quaternion<Type>& Quaternion) const;

	inline Vector<4, Type> GetAsVector() const;



	/// Statics

	inline static bool NearlyEqual(Quaternion<Type> A, Quaternion<Type> B, Type Tolerance = MICRO_NUMBER)
	{
		return A.NearlyEqual(B, Tolerance);
	}


	// Converts a float vector of Euler angles (degrees) into a Quaternion.
	// @param Vector - A vector of Eular angles.
	// @return - The constructor quaternion.
	static Quaternion<Type> Euler(const Vector<3, Type>& Vec)
	{
		const Type DivideBy2{ ((Type)TMath::Pi / (Type)180.0f) / (Type)2.0f };

		Type SPitch{ TMath::Sin(Vec[EAxis::X] * 0.5f) };
		Type SYaw{ TMath::Sin(Vec[EAxis::Y] * 0.5f) };
		Type SRoll{ TMath::Sin(Vec[EAxis::Z] * 0.5f) };

		Type CPitch{ TMath::Cos(Vec[EAxis::X] * 0.5f) };
		Type CYaw{ TMath::Cos(Vec[EAxis::Y] * 0.5f) };
		Type CRoll{ TMath::Cos(Vec[EAxis::Z] * 0.5f) };

		//TMath::SinCos(&SPitch, &CPitch, Vector[EAxis::X] * DivideBy2);
		//TMath::SinCos(&SYaw, &CYaw, Vector[EAxis::Y] * DivideBy2);
		//TMath::SinCos(&SRoll, &CRoll, Vector[EAxis::Z] * DivideBy2);

		Quaternion<Type> Result;
		Result.W = (CYaw * CPitch * CRoll) + (SYaw * SPitch * SRoll);
		Result.X = (CYaw * CPitch * SRoll) - (SYaw * SPitch * CRoll);
		Result.Y = (SYaw * CPitch * SRoll) + (CYaw * SPitch * CRoll);
		Result.Z = (SYaw * CPitch * CRoll) - (CYaw * SPitch * SRoll);

		//Result.X = ( CRoll * SPitch * SYaw) - (SRoll * CPitch * CYaw);
		//Result.Y = ( CRoll * CPitch * SYaw) - (SRoll * SPitch * CYaw);
		//Result.Z = (-CRoll * SPitch * CYaw) - (SRoll * CPitch * SYaw);
		//Result.W = ( CRoll * CPitch * CYaw) + (SRoll * SPitch * SYaw);

		return Result;
	}


	static Quaternion<Type> Euler(const Type& X, const Type& Y, const Type& Z)
	{
		return Quaternion<Type>::Euler(Vector<3, Type>{ X, Y, Z });
	}
};


// A quaternion type using floating points.
typedef Quaternion<float> SQuaternion;

// A quaternion type using doubles.
typedef Quaternion<double> SQuaterniond;



template <typename Type>
inline Quaternion<Type>::Quaternion(const Quaternion<Type>& Q)
	:X{ Q.X }, Y{ Q.Y }, Z{ Q.Z }, W{ Q.W }
{}


template <typename Type>
inline Quaternion<Type>::Quaternion(Type InF)
	: X{ InF }, Y{ InF }, Z{ InF }, W{ InF }
{}


template <typename Type>
inline Quaternion<Type>::Quaternion(Type InX, Type InY, Type InZ, Type InW)
	: X{ InX }, Y{ InY }, Z{ InZ }, W{ InW }
{}


template <typename Type>
inline Quaternion<Type>::Quaternion(Vector<4, Type> InV)
	: X{ InV[EAxis::X] }, Y{ InV[EAxis::Y] }, Z{ InV[EAxis::Z] }, W{ InV[EAxis::W] }
{}


template <typename Type>
inline Quaternion<Type>::Quaternion(Vector<3, Type> InV, Type InW)
	: X{ InV[EAxis::X] }, Y{ InV[EAxis::Y] }, Z{ InV[EAxis::Z] }, W{ InW }
{}


template <typename Type>
inline Quaternion<Type> Quaternion<Type>::operator+(const Quaternion<Type>& Q) const
{
	return Quaternion<Type> { X + Q.X, Y + Q.Y, Z + Q.Z, W + Q.W };
}


template <typename Type>
inline Quaternion<Type> Quaternion<Type>::operator+=(const Quaternion<Type>& Q)
{
	X += Q.X;
	Y += Q.Y;
	Z += Q.Z;
	W += Q.W;
	CheckNaN();
	return *this;
}


template <typename Type>
inline Quaternion<Type> Quaternion<Type>::operator-(const Quaternion<Type>& Q) const
{
	return Quaternion<Type>
	{
		X - Q.X,
		Y - Q.Y,
		Z - Q.Z,
		W - Q.W
	};
}


template <typename Type>
inline Quaternion<Type> Quaternion<Type>::operator-=(const Quaternion<Type>& Q)
{
	X -= Q.X;
	Y -= Q.Y;
	Z -= Q.Z;
	W -= Q.W;
	CheckNaN();
	return *this;
}


template <typename Type>
inline Quaternion<Type> Quaternion<Type>::operator*(const Quaternion<Type>& Q) const
{
	// Mask0 =  1.0f, -1.0f,  1.0f, -1.0f
	// Mask1 =  1.0f,  1.0f, -1.0f, -1.0f
	// Mask2 = -1.0f,  1.0f,  1.0f, -1.0f

	Quaternion<Type> Result;
	Result.X = this->W * Q.X;
	Result.Y = this->W * Q.Y;
	Result.Z = this->W * Q.Z;
	Result.W = this->W * Q.W;

	Result.X += (this->X * Q.W) * (Type)1.0f;
	Result.Y += (this->X * Q.Z) * (Type)-1.0f;
	Result.Z += (this->X * Q.Y) * (Type)1.0f;
	Result.W += (this->X * Q.X) * (Type)-1.0f;

	Result.X += (this->Y * Q.Z) * (Type)1.0f;
	Result.Y += (this->Y * Q.W) * (Type)1.0f;
	Result.Z += (this->Y * Q.X) * (Type)-1.0f;
	Result.W += (this->Y * Q.Y) * (Type)-1.0f;

	Result.X += (this->Z * Q.Y) * (Type)-1.0f;
	Result.Y += (this->Z * Q.X) * (Type)1.0f;
	Result.Z += (this->Z * Q.W) * (Type)1.0f;
	Result.W += (this->Z * Q.Z) * (Type)-1.0f;

	CheckNaN();
	return Result;
}


template <typename Type>
inline Quaternion<Type> Quaternion<Type>::operator*=(const Quaternion<Type>& Q)
{
	*this = *this * Q;
	return *this;
}


template <typename Type>
inline Vector<3, Type> Quaternion<Type>::operator*(const Vector<3, Type>& V) const
{
	return RotateVector(V);
}


template <typename Type>
inline Quaternion<Type> Quaternion<Type>::operator*(const Type& F) const
{
	return Quaternion<Type>
	{
		X* F,
		Y* F,
		Z* F,
		W* F
	};
}


template <typename Type>
inline Quaternion<Type> Quaternion<Type>::operator*=(const Type& F)
{
	X *= F;
	Y *= F;
	Z *= F;
	W *= F;
	CheckNaN();
	return *this;
}


template <typename Type>
inline Quaternion<Type> Quaternion<Type>::operator/(const Type& F) const
{
	const Type Recip{ (Type)1.0f / F };
	return Quaternion
	{
		X * Recip,
		Y * Recip,
		Z * Recip,
		W * Recip
	};
}


template <typename Type>
inline Quaternion<Type> Quaternion<Type>::operator/=(const Type& F)
{
	const Type Recip{ (Type)1.0f / F };
	X *= Recip;
	Y *= Recip;
	Z *= Recip;
	W *= Recip;
	CheckNaN();
	return *this;
}


template <typename Type>
inline bool Quaternion<Type>::operator==(const Quaternion<Type>& Q) const
{
	return
		(
			X == Q.X &&
			Y == Q.Y &&
			Z == Q.Z &&
			W == Q.W
		);
}


template <typename Type>
inline bool Quaternion<Type>::operator!=(const Quaternion<Type>& Q) const
{
	return
		(
			X != Q.X ||
			Y != Q.Y ||
			Z != Q.Z ||
			W != Q.W
		);
}


template <typename Type>
inline Type Quaternion<Type>::operator|(const Quaternion<Type>& Q) const
{
	return
		(
			(X * Q.X) +
			(Y * Q.Y) +
			(Z + Q.Z) +
			(W + Q.W)
		);
}


template <typename Type>
inline Quaternion<Type> Quaternion<Type>::operator=(const Vector<3, Type>& V)
{
	X = V[EAxis::X];
	Y = V[EAxis::Y];
	Z = V[EAxis::Z];
	return *this;
}


template <typename Type>
inline Quaternion<Type> Quaternion<Type>::operator=(const Vector<4, Type>& V)
{
	X = V[EAxis::X];
	Y = V[EAxis::Y];
	Z = V[EAxis::Z];
	W = V[EAxis::W];
	return *this;
}


template <typename Type>
inline Type Quaternion<Type>::operator[](const uint& Axis) const
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


template <typename Type>
inline Type& Quaternion<Type>::operator[](const uint& Axis)
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


template <typename Type>
inline bool Quaternion<Type>::IsIdentity(Type Tolerance) const
{
	return NearlyEqual(Quaternion::Identity, Tolerance);
}


template <typename Type>
inline bool Quaternion<Type>::NearlyEqual(Quaternion<Type> Other, Type Tolerance) const
{
	return TMath::Abs(X - Other.X <= Tolerance && TMath::Abs(Y - Other.Y) <= Tolerance && TMath::Abs(Z - Other.Z) <= Tolerance && TMath::Abs(W - Other.W) <= Tolerance)
		|| (TMath::Abs(X + Other.X) <= Tolerance && TMath::Abs(Y + Other.Y) <= Tolerance && TMath::Abs(Z + Other.Z) <= Tolerance && TMath::Abs(W + Other.W) <= Tolerance);
}


template <typename Type>
Vector<3, Type> Quaternion<Type>::ToEuler() const
{
	Vector<3, Type> Result;

	Type SinRCosP{ 2.0f * (W * X + Y * Z) };
	Type CosRCosP{ 1.0f - 2.0f * (X * X + Y * Y) };
	Result[EAxis::Z] = TMath::ATan2(SinRCosP, CosRCosP);

	Type SinP{ 2.0f * (W * Y - Z * X) };
	if (TMath::Abs(SinP) >= 1.0f) Result[EAxis::X] = std::copysign(TMath::Pi / 2.0f, SinP);
	else Result[EAxis::X] = TMath::ASin(SinP);

	Type SinYCosP{ 2.0f * (W * Z + X * Y) };
	Type CosYCosP{ 1.0f - 2.0f * (Y * Y + Z * Z) };
	Result[EAxis::Y] = TMath::ATan2(SinYCosP, CosYCosP);
	return Result;


	/*const Type SingularityTest{ Type((Z * X) - (W * Y)) };
	const Type YawY{ Type(2.0f * ((W * Z) + (X * Y))) };
	const Type YawX{ Type(1.0f - 2.0f * (TMath::Square(Y) + TMath::Square(Z))) };

	const Type SingularityThreashold = (Type)0.4999995f;
	const Type RadToDeg{ Type((180.0f) / TMath::Pi) };

	Vector<3, Type> Result;

	if (SingularityTest < -SingularityThreashold)
	{
		Result[EAxis::X] = (Type)-90.0f;
		Result[EAxis::Y] = (Type)TMath::ATan2(YawY, YawX) * RadToDeg;
		Result[EAxis::Z] = (Type)NormalizeAxis(-Result[EAxis::Y] - (2.0f * TMath::ATan2(X, W) * RadToDeg));
	}
	else if (SingularityTest > SingularityThreashold)
	{
		Result[EAxis::X] = (Type)90.0f;
		Result[EAxis::Y] = (Type)TMath::ATan2(YawY, YawX) * RadToDeg;
		Result[EAxis::Z] = (Type)NormalizeAxis(Result[EAxis::Y] - (2.0f * TMath::ATan2(X, W) * RadToDeg));
	}
	else
	{
		Result[EAxis::X] = (Type)TMath::FastAsin(2.0f * (SingularityTest)) * RadToDeg;
		Result[EAxis::Y] = (Type)TMath::ATan2(YawY, YawX) * RadToDeg;
		Result[EAxis::Z] = (Type)TMath::ATan2(-2.0f * ((W * X) + (Y * Z)), (1.0f - 2.0f * (TMath::Square(X) + TMath::Square(Y)))) * RadToDeg;
	}
	return Result;*/
}


template <typename Type>
inline void Quaternion<Type>::Normalize(Type Tolerance)
{
	const Type SquareSum{ (X * X) + (Y * Y) + (Z * Z) + (W * W) };
	if (SquareSum >= Tolerance)
	{
		const Type Scale{ TMath::InvSqrt(SquareSum) };
		X *= Scale;
		Y *= Scale;
		Z *= Scale;
		W *= Scale;
	}
	else
	{
		*this = Quaternion<Type>::Identity;
	}
}


template <typename Type>
inline Type Quaternion<Type>::NormalizeAxis(Type Angle) const
{
	Angle = ClampAxis(Angle);

	if (Angle > 180.0f)
	{
		Angle -= 360.0f;
	}
	return Angle;
}


template <typename Type>
inline Vector<3, Type> Quaternion<Type>::RotateVector(Vector<3, Type> V) const
{
	// http://people.csail.mit.edu/bkph/articles/Quaternions.pdf
	// V' = V + 2w(Q x V) + (2Q x (Q x V))
	// refactor:
	// V' = V + w(2(Q x V)) + (Q x (2(Q x V)))
	// T = 2(Q x V);
	// V' = V + w*(T) + (Q x T)

	const Vector<3, Type> Quat{ X, Y, Z };
	const Vector<3, Type> T{ Vector<3, Type>::CrossProduct(Quat, V) * 2.0f };
	return Vector<3, Type>{ V + (T * W) + Vector<3, Type>::CrossProduct(Quat, T) };
}


template <typename Type>
inline Vector<3, Type> Quaternion<Type>::UnrotateVector(Vector<3, Type> V) const
{
	const Vector<3, Type> Quat{ -X, -Y, -Z };
	const Vector<3, Type> T{ Vector<3, Type>::CrossProduct(Quat, V) * 2.0f };
	return Vector<3, Type>{ V + (T * W) + Vector<3, Type>::CrossProduct(Quat, T) };
}


template <typename Type>
Quaternion<Type> Quaternion<Type>::Log() const
{
	Quaternion<Type> Result;
	Result.W = (Type)0.0f;

	if (TMath::Abs(W) < 1.0f)
	{
		const Type Angle{ (Type)TMath::ACos(W) };
		const Type SinAngle{ (Type)TMath::Sin(Angle) };

		if (TMath::Abs(SinAngle) >= SMALL_NUMBER)
		{
			const Type Scale{ Angle / SinAngle };
			Result.X = Scale * X;
			Result.Y = Scale * Y;
			Result.Z = Scale * Z;
			return Result;
		}
	}

	Result.X = X;
	Result.Y = Y;
	Result.Z = Z;
	return Result;
}


template <typename Type>
Quaternion<Type> Quaternion<Type>::Exp() const
{
	const Type Angle{ (Type)TMath::Sqrt((X * X) + (Y * Y) + (Z * Z)) };
	const Type SinAngle{ (Type)TMath::Sin(Angle) };

	Quaternion<Type> Result;
	Result.W = (Type)TMath::Cos(Angle);

	if (TMath::Abs(SinAngle) >= SMALL_NUMBER)
	{
		const Type Scale{ SinAngle / Angle };
		Result.X = Scale * X;
		Result.Y = Scale * Y;
		Result.Z = Scale * Z;
		return Result;
	}

	Result.X = X;
	Result.Y = Y;
	Result.Z = Z;
	return Result;
}


template <typename Type>
inline Quaternion<Type> Quaternion<Type>::Inverse() const
{
	if (IsNormalized())
	{
		return Quaternion<Type>{ -X, -Y, -Z, W };
	}
	return Quaternion<Type>{};
}


template <typename Type>
inline void Quaternion<Type>::EnforceShortestArcWidth(const Quaternion<Type>& Other)
{
	const Type DotResult{ (Other | *this) };
	const Type Bias{ TMath::FloatSelect(DotResult, 1.0f, -1.0f) };
	X *= Bias;
	Y *= Bias;
	Z *= Bias;
	W *= Bias;
}


template <typename Type>
inline bool Quaternion<Type>::ContainsNaN() const
{
	return
		(
			!TMath::IsFinite(X) ||
			!TMath::IsFinite(Y) ||
			!TMath::IsFinite(Z) ||
			!TMath::IsFinite(W)
		);
}


template <typename Type>
inline Type Quaternion<Type>::ClampAxis(Type Angle) const
{
	Angle = TMath::FMod(Angle, (Type)360.0f);
	if (Angle < (Type)0.0f)
	{
		Angle += (Type)360.0f;
	}
	return Angle;
}


template <typename Type>
Quaternion<Type> Quaternion<Type>::Rotate(Type InX, Type InY, Type InZ)
{
	return Quaternion<Type>{};
}


template <typename Type>
Quaternion<Type> Quaternion<Type>::Rotate(Quaternion<Type> Quat)
{
	return Quaternion<Type>{};
}


template <typename Type>
Quaternion<Type> Quaternion<Type>::Rotate(Vector<3, Type> Vector)
{
	return Quaternion<Type>{};
}


template <typename Type>
Quaternion<Type> Quaternion<Type>::RotateEuler(Type InX, Type InY, Type InZ)
{
	return Quaternion<Type>{};
}


template <typename Type>
Quaternion<Type> Quaternion<Type>::RotateEuler(Vector<3, Type> Vector)
{
	return Quaternion<Type>{};
}


template <typename Type>
inline void Quaternion<Type>::Print() const
{
	printf("%f, %f, %f, %f\n", X, Y, Z, W);
}


template <typename Type>
inline Quaternion<Type> Quaternion<Type>::GetNormalized(Type Tolerance) const
{
	Quaternion Result{ *this };
	Result.Normalize(Tolerance);
	return Result;
}


template <typename Type>
inline bool Quaternion<Type>::IsNormalized() const
{
	return (TMath::Abs(1.0f - SizeSquared()) < 0.01f);
}


template <typename Type>
inline Type Quaternion<Type>::Size() const
{
	return TMath::Sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));
}


template <typename Type>
inline Type Quaternion<Type>::SizeSquared() const
{
	return ((X * X) + (Y * Y) + (Z * Z) + (W * W));
}


template <typename Type>
inline Type Quaternion<Type>::GetAngle() const
{
	return (Type)2.0f * TMath::ACos(W);
}


template <typename Type>
inline void Quaternion<Type>::ToAxisAndAngle(Vector<3, Type>& Axis, Type& Angle) const
{
	Angle = GetAngle();
	Axis = GetRotationAxis();
}


template <typename Type>
void Quaternion<Type>::ToSwingTwist(const Vector<3, Type>& TwistAxis, Quaternion<Type>& Swing, Quaternion<Type>& Twist) const
{
	Vector<3, Type> Projection{ TwistAxis * Vector<3, Type>::DotProduct(TwistAxis, Vector<3, Type>{ X, Y, Z }) };
	Twist = Quaternion<Type>{ Projection[EAxis::X], Projection[EAxis::Y], Projection[EAxis::Z], W };

	if (Twist.SizeSquared() == 0.0f)
	{
		Twist = Quaternion<Type>::Identity;
	}
	else
	{
		Twist.Normalize();
	}

	Swing = *this * Twist.Inverse();
}


template <typename Type>
inline Vector<3, Type> Quaternion<Type>::GetAxisX() const
{
	return RotateVector(Vector<3, Type>::Right());
}


template <typename Type>
inline Vector<3, Type> Quaternion<Type>::GetAxisY() const
{
	return RotateVector(Vector<3, Type>::Up());
}


template <typename Type>
inline Vector<3, Type> Quaternion<Type>::GetAxisZ() const
{
	return RotateVector(Vector<3, Type>::Forward());
}


template <typename Type>
inline Vector<3, Type> Quaternion<Type>::GetRightVector() const
{
	return GetAxisX();
}


template <typename Type>
inline Vector<3, Type> Quaternion<Type>::GetUpVector() const
{
	return GetAxisY();
}


template <typename Type>
inline Vector<3, Type> Quaternion<Type>::GetForwardVector() const
{
	return GetAxisZ();
}


template <typename Type>
inline Vector<3, Type> Quaternion<Type>::ToVector() const
{
	return GetAxisX();
}


template <typename Type>
inline Vector<3, Type> Quaternion<Type>::GetRotationAxis() const
{
	const Type S{ TMath::Sqrt(TMath::Max(1.0f - (W * W), 0.0f)) };
	if (S >= (Type)0.0001f)
	{
		return Vector<3, Type>{ X / S, Y / S, Z / S };
	}
	return Vector<3, Type>::Right();
}


template <typename Type>
Type Quaternion<Type>::AngularDistance(const Quaternion<Type>& Quat) const
{
	Type InnerProd{ (X * Quat.X) + (Y * Quat.Y) + (Z * Quat.Z) + (W * Quat.W) };
	return (Type)TMath::ACos((2.0f * InnerProd * InnerProd) - 1.0f);
}


template <typename Type>
inline Vector<4, Type> Quaternion<Type>::GetAsVector() const
{
	return Vector<4, Type>{ X, Y, Z, W };
}