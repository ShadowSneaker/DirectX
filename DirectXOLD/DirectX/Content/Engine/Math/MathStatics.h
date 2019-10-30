#pragma once
#include "MathValues.h"

#include <math.h>


#define TO_RADIAN(x) { (float) ((x) * (TMath::Pi / 180.0f)) }
#define RADIAN { (float) (TMath::Pi * 2.0f) }
#define TO_DEGREES(x) { (float) ((x) * (180.0f / TMath::Pi)) }
#define DEGREES { (float) (TMath::Pi / 180.0f) }


// class that holds a large amount of static math functions.
class TMath
{
public:
	static const float Pi;
	static const float Pi2;
	static const float InversePi;
	static const float Divide2Pi;
	static const float PiDivide2;
	static const float PiDivide4;
	static const float HalfPi;

public:
	// 
	static inline float Sin(float Value) { return sinf(Value); }

	// 
	static inline float ASin(float Value) { return asinf((Value < -1.0f) ? -1.0f : ((Value < 1.0f) ? Value : 1.0f)); }

	// 
	static inline float Sinh(float Value) { return sinhf(Value); }

	// 
	static inline float Cos(float Value) { return cosf(Value); }

	// 
	static inline float ACos(float Value) { return acosf((Value < -1.0f) ? -1.0f : ((Value < 1.0f) ? Value : 1.0f)); }

	// 
	static inline float Tan(float Value) { return tanf(Value); }

	// 
	static inline float ATan(float Value) { return atanf(Value); }

	static void SinCos(float* ScalarSin, float* ScalarCos, float Value)
	{
		float Quotient = (InversePi * 0.5f) * Value;
		Quotient = (float)((int)(Quotient + (Value >= 0.0f) ? 0.5f : -0.5f));

		float Y = Value - (2.0f * Pi) * Quotient;

		float Sign;
		if (Y > HalfPi)
		{
			Y -= Pi;
			Sign = -1.0f;
		}
		else if (Y < -HalfPi)
		{
			Y -= -Pi;
			Sign = -1.0f;
		}
		else
		{
			Sign = 1.0f;
		}

		float Y2 = Y * Y;
		*ScalarSin = (((((-2.3889859e-08f * Y2 + 2.7525562e-06f) * Y2 - 0.00019840874f) * Y2 + 0.0083333310f) * Y2 - 0.16666667f) * Y2 + 1.0f) * Y;

		float P = ((((-2.6051615e-07f * Y2 + 2.4760495e-05f) * Y2 - 0.0013888378f) * Y2 + 0.041666638f) * Y2 - 0.5f) * Y2 + 1.0f;
		*ScalarCos = Sign * P;
	}


	// Returns the result of number powered by a value.
	static inline float Power(const float A, const float B)
	{
		return powf(A, B);
	}


	// Returns the square root of an inputted value.
	static inline float Sqrt(const float Value)
	{
		return sqrtf(Value);
	}


	// 
	static inline float Abs(const float Value)
	{
		return fabsf(Value);
	}


	// Clamps the value to be between the Min and Max.
	template <typename Type>
	static inline Type Clamp(const Type Min, const Type Max, const Type Value)
	{
		return (Value > Max) ? Max : (Value < Min) ? Min : Value;
	}


	// Clamps the value to be between the Min and Max.
	static inline float Clamp(const float Min, const float Max, const float Value)
	{
		return Clamp<float>(Min, Max, Value);
	}

	// Clamps the value to be between the Min and Max.
	static inline double Clamp(const double Min, const double Max, const double Value)
	{
		return Clamp<double>(Min, Max, Value);
	}


	// Clamps the value to be between the Min and Max.
	static inline int Clamp(const int Min, const int Max, const int Value)
	{
		return Clamp<int>(Min, Max, Value);
	}


	// Clamps the value between the Min and Max.
	// Will force the value inputted to be between the Min and Max values.
	template <typename Type>
	static inline Type ForceClamp(const Type Min, const Type Max, Type& Value)
	{
		Value = Clamp<Type>(Min, Max, Value);
		return Value;
	}


	// Clamps the value between the Min and Max.
	// Will force the value inputted to be between the Min and Max values.
	static inline float ForceClamp(const float Min, const float Max, float& Value)
	{
		return ForceClamp<float>(Min, Max, Value);
	}


	// Clamps the value between the Min and Max.
	// Will force the value inputted to be between the Min and Max values.
	static inline double ForceClamp(const double Min, const double Max, double& Value)
	{
		return ForceClamp<double>(Min, Max, Value);
	}


	// Clamps the value between the Min and Max.
	// Will force the value inputted to be between the Min and Max values.
	static inline int ForceClamp(const int Min, const int Max, int& Value)
	{
		return ForceClamp<int>(Min, Max, Value);
	}


	// Shorthand of doing Clamp(0,1). 
	// Clamps the value to be between 0 and 1.
	template <typename Type>
	static inline Type Clamp01(const Type Value)
	{
		return Clamp<Type>((Type)0, (Type)1, Value);
	}


	// Shorthand of doing Clamp(0,1).
	// Clamps the value to be between 0 and 1.
	static inline float Clamp01(const float Value)
	{
		return Clamp01<float>(Value);
	}


	// Shorthand of doing Clamp(0,1).
	// Clamps the value to be between 0 and 1.
	static inline double Clamp01(const double Value)
	{
		return Clamp01<double>(Value);
	}


	// Shorthand of doing ForceClamp(0,1).
	// Clamps the value to be between 0 and 1.
	// WIll force te value inputted to be between the Min and Max values.
	template <typename Type>
	static inline Type ForceClamp01(Type& Value)
	{
		return ForceClamp<Type>((Type)0, (Type)1, Value);
	}


	// Shorthand of doing ForceClamp(0,1).
	// Clamps the value to be between 0 and 1.
	// WIll force te value inputted to be between the Min and Max values.
	static inline float ForceClamp01(float& Value)
	{
		return ForceClamp01<float>(Value);
	}


	// Shorthand of doing ForceClamp(0,1).
	// Clamps the value to be between 0 and 1.
	// WIll force te value inputted to be between the Min and Max values.
	static inline double ForceClamp01(double& Value)
	{
		return ForceClamp01<double>(Value);
	}


	// Multiplies value by itself.
	template <typename Type>
	static inline Type Square(const Type Value)
	{
		return Value * Value;
	}


	// Multiplies value by itself.
	static inline float Square(const float Value)
	{
		return Square<float>(Value);
	}


	// Multiplies value by itself.
	static inline int Square(const int Value)
	{
		return Square<int>(Value);
	}


	// Multiplies value by itself.
	static inline double Square(const double Value)
	{
		return Square<double>(Value);
	}


	// Locks a value between a minimum and a maximum value.
	// @param Min - The lowest value the inputted value can be.
	// @param Max - The largest value the inputted value can be.
	// @param Percent - The variable being clamped.
	template <typename Type>
	static inline Type Lerp(const Type Min, const Type Max, const float Percent)
	{
		return (Type)((Max - Min) * Percent) + Min;
	}


	// Locks a value between a minimum and a maximum value.
	// @param Min - The lowest value the inputted value can be.
	// @param Max - The largest value the inputted value can be.
	// @param Percent - The variable being clamped.
	static inline float Lerp(const float Min, const float Max, const float Percent)
	{
		return Lerp<float>(Min, Max, Percent);
	}


	// Locks a value between a minimum and a maximum value.
	// @param Min - The lowest value the inputted value can be.
	// @param Max - The largest value the inputted value can be.
	// @param Percent - The variable being clamped.
	static inline double Lerp(const double Min, const double Max, const float Percent)
	{
		return Lerp<double>(Min, Max, Percent);
	}


	// Locks a value between a minimum and a maximum value.
	// @param Min - The lowest value the inputted value can be.
	// @param Max - The largest value the inputted value can be.
	// @param Percent - The variable being clamped.
	static inline int Lerp(const int Min, const int Max, const float Percent)
	{
		return Lerp<int>(Min, Max, Percent);
	}


	// Gets a value betwee.
	// @param Percent - The variable being clamped.
	static inline float Lerp01(const float Percent)
	{
		return Lerp<float>(0.0f, 0.1f, Percent);
	}


	// Returns the percentage between two values.
	// @param Min - The minimum value.
	// @param Max - The maximum value.
	// @param Percent - The value (between 0 and 1) to retreive the percentage.
	// @Return - The value between the minimum and maximum based off the percentage.
	static inline const float Percent(const float Min, const float Max, const float Value)
	{
		return (Value - Min) / (Max - Min);
	}


	// Returns the percentage between two values.
	// @param Min - The minimum value.
	// @param Max - The maximum value.
	// @param Percent - The value (between 0 and 1) to retreive the percentage.
	// @Return - The percentage between the minimum and maximum based off the percentage.
	static inline const double Percent(const double Min, const double Max, const double Value)
	{
		return (Value - Min) / (Max - Min);
	}


	// Returns the percentage between two values.
	// @param Min - The minimum value.
	// @param Max - The maximum value.
	// @param Percent - The value (between 0 and 1) to retreive the percentage.
	// @Return - The percentage between the minimum and maximum based off the percentage.
	static inline const float Percent(const int Min, const int Max, const int Value)
	{
		return float(Value - Min) / float(Max - Min);
	}


	// Tests if a value is almost the same value as another value.
	// @param A - The variable to be compared.
	// @param B - The variable to be compared with.
	// @param Range - How much of a difference A can be from B.
	// @return - Returns true if object B was in range of object A.
	template <typename Type>
	static inline bool NearlyEqual(const Type A, const Type B, const float Range)
	{
		return ((A >= B - Range) && A <= B + Range);
	}


	// Tests if a value is almost the same value as another value.
	// @param A - The variable to be compared.
	// @param B - The variable to be compared with.
	// @param Range - How much of a difference A can be from B.
	// @return - Returns true if object B was in range of object A.
	static inline bool NearlyEqual(const float A, const float B, const float Range)
	{
		return NearlyEqual<float>(A, B, Range);
	}


	// Tests if a value is almost the same value as another value.
	// @param A - The variable to be compared.
	// @param B - The variable to be compared with.
	// @param Range - How much of a difference A can be from B.
	// @return - Returns true if object B was in range of object A.
	static inline bool NearlyEqual(const int A, const int B, const float Range)
	{
		return NearlyEqual<int>(A, B, Range);
	}


	// Tests if a value is almost the same value as another value.
	// @param A - The variable to be compared.
	// @param B - The variable to be compared with.
	// @param Range - How much of a difference A can be from B.
	// @return - Returns true if object B was in range of object A.
	static inline bool NearlyEqual(const double A, const double B, const float Range)
	{
		return NearlyEqual<double>(A, B, Range);
	}

	static inline bool ScalarNearEqual(float S1, float S2, float Epsilon)
	{
		float Delta = S1 - S2;
		return (fabsf(Delta) <= Epsilon);
	}


	static inline void ScalarSinCos(float* pSin, float* pCos, float Value)
	{
		if (!pSin || !pCos)
		{
			return;
		}

		float Quotient = Divide2Pi * Value;
		if (Value >= 0.0f)
		{
			Quotient = static_cast<float>(static_cast<int>(Quotient + 0.5f));
		}
		else
		{
			Quotient = static_cast<float>(static_cast<int>(Quotient - 0.5f));
		}

		float Y = Value - Pi2 * Quotient;

		float Sign;
		if (Y > PiDivide2)
		{
			Y = Pi - Y;
			Sign = -1.0f;
		}
		else if (Y < -PiDivide2)
		{
			Y = -Pi - Y;
			Sign = -1.0f;
		}
		else
		{
			Sign = 1.0f;
		}

		float Y2 = Y * Y;

		*pSin = (((((-2.3889859e-08f * Y2 + 2.7525562e-06f) * Y2 - 0.00019840874f) * Y2 + 0.0083333310f) * Y2 - 0.16666667f) * Y2 + 1.0f) * Y;
		float P = ((((-2.6051615e-07f * Y2 + 2.4760495e-05f) * Y2 - 0.0013888378f) * Y2 + 0.041666638f) * Y2 - 0.5f) * Y2 + 1.0f;
		*pCos = Sign * P;
	}

	//...


	static inline int TruncInt(float Value)
	{
		return (int)Value;
	}


	static inline float TruncFloat(float Value)
	{
		return (float)TruncInt(Value);
	}


	static inline double TruncDouble(float Value)
	{
		return (double)TruncInt(Value);
	}



};




//#ifndef PI
//#define PI
//const float TMath::Pi{ 3.14159265358f };
//const float TMath::InvsersePi{ 0.31830988618f };
//const float TMath::HalfPi{ 1.57079632679f };
//#endif