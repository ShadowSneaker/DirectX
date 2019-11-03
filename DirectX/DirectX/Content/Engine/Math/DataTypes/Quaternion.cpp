#include "Quaternion.h"


const SQuaternion SQuaternion::Identity{ 0.0f, 0.0f, 0.0f, 1.0f };


SVector SQuaternion::Euler() const
{
	const float SingularityTest{ (Z * X) - (W * Y) };
	const float YawY{ 2.0f * ((W * Z) + (X * Y)) };
	const float YawX{ (1.0f - 2.0f * (TMath::Square(Y) + TMath::Square(Z))) };

	const float SingularityThreashold = 0.4999995f;
	const float RadToDeg{ (180.0f) / TMath::Pi };

	SVector Result;

	if (SingularityTest < -SingularityThreashold)
	{
		Result[EAxis::X] = -90.0f;
		Result[EAxis::Y] = TMath::ATan2(YawY, YawX) * RadToDeg;
		Result[EAxis::Z] = NormalizeAxis(-Result[EAxis::Y] - (2.0f * TMath::ATan2(X, W) * RadToDeg));
	}
	else if (SingularityTest > SingularityThreashold)
	{
		Result[EAxis::X] = 90.0f;
		Result[EAxis::Y] = TMath::ATan2(YawY, YawX) * RadToDeg;
		Result[EAxis::Z] = NormalizeAxis(Result[EAxis::Y] - (2.0f * TMath::ATan2(X, W) * RadToDeg));
	}
	else
	{
		Result[EAxis::X] = TMath::FastAsin(2.0f * (SingularityTest)) * RadToDeg;
		Result[EAxis::Y] = TMath::ATan2(YawY, YawX) * RadToDeg;
		Result[EAxis::Z] = TMath::ATan2(-2.0f * ((W * X) + (Y * Z)), (1.0f - 2.0f * (TMath::Square(X) + TMath::Square(Y)))) * RadToDeg;
	}
	return Result;
}


SQuaternion SQuaternion::Log() const
{
	SQuaternion Result;
	Result.W = 0.0f;

	if (TMath::Abs(W) < 1.0f)
	{
		const float Angle{ TMath::ACos(W) };
		const float SinAngle{ TMath::Sin(Angle) };

		if (TMath::Abs(SinAngle) >= SMALL_NUMBER)
		{
			const float Scale{ Angle / SinAngle };
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


SQuaternion SQuaternion::Exp() const
{
	const float Angle{ TMath::Sqrt((X * X) + (Y * Y) + (Z * Z)) };
	const float SinAngle{ TMath::Sin(Angle) };

	SQuaternion Result;
	Result.W = TMath::Cos(Angle);

	if (TMath::Abs(SinAngle) >= SMALL_NUMBER)
	{
		const float Scale{ SinAngle / Angle };
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


void SQuaternion::ToSwingTwist(const SVector& TwistAxis, SQuaternion& Swing, SQuaternion& Twist) const
{
	SVector Projection{ TwistAxis * SVector::DotProduct(TwistAxis, SVector{ X, Y, Z }) };
	Twist = SQuaternion{ Projection[EAxis::X], Projection[EAxis::Y], Projection[EAxis::Z], W };

	if (Twist.SizeSquared() == 0.0f)
	{
		Twist = SQuaternion::Identity;
	}
	else
	{
		Twist.Normalize();
	}

	Swing = *this * Twist.Inverse();
}


float SQuaternion::AngularDistance(const SQuaternion& Quaternion) const
{
	float InnerProd{ (X * Quaternion.X) + (Y * Quaternion.Y) + (Z * Quaternion.Z) + (W * Quaternion.W) };
	return TMath::ACos((2.0f * InnerProd * InnerProd) - 1.0f);
}


