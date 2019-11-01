#pragma once
#include "MathValues.h"

#include <float.h>
#include <math.h>


#define TO_RADIAN(x) { (float) ((x) * (TMath::Pi / 180.0f)) }
#define RADIAN { (float) (TMath::Pi * 2.0f) }
#define TO_DEGREES(x) { (float) ((x) * (180.0f / TMath::Pi)) }
#define DEGREES { (float) (TMath::Pi / 180.0f) }




// class that holds a large amount of static math functions.
class TMath
{
public:
	static const float Pi;			// The value of PI.
	static const float Pi2;			// The value of PI multiplied by 2.
	static const float InversePi;	// The inverse value of PI.
	static const float Divide2Pi;	// The value of PI devided by 2.
	static const float PiDivide2;	// The value of 2 divided by PI. 
	static const float PiDivide4;	// The value of 4 divided by PI.
	static const float HalfPi;		// The value of half PI.



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

	// 
	static inline float ATan2(float Y, float X)
	{
		const float AbsX{ TMath::Abs(X) };
		const float AbsY{ TMath::Abs(Y) };
		const bool YAbsBigger{ AbsY > AbsX };
		float T0{ (YAbsBigger) ? AbsY : AbsX };
		float T1{ (YAbsBigger) ? AbsX : AbsY };

		if (T0 == 0.0f) return 0.0f;

		float T3{ T1 / T0 };
		float T4{ T3 * T3 };

		static const float C[7] = {
			+7.2128853633444123e-03f,
			-3.5059680836411644e-02f,
			+8.1675882859940430e-02f,
			-1.3374657325451267e-01f,
			+1.9856563505717162e-01f,
			-3.3324998579202170e-01f,
			+1.0f
		};

		T0 = C[0];
		T0 = T0 * T4 + C[1];
		T0 = T0 * T4 + C[2];
		T0 = T0 * T4 + C[3];
		T0 = T0 * T4 + C[4];
		T0 = T0 * T4 + C[5];
		T0 = T0 * T4 + C[6];
		T3 = T0 * T3;

		T3 = (YAbsBigger) ? (0.5f * Pi) - T3 : T3;
		T3 = (X < 0.0f) ? Pi - T3 : T3;
		T3 = (Y < 0.0f) ? -T3 : T3;
		return T3;
	}

#define FASTASIN_HALF_PI (1.5707963050f)

	// 
	static inline float FastAsin(float Value)
	{
		bool NonNegative{ (Value >= 0.0f) };
		float X{ Abs(Value) };
		float OMX{ 1.0f - X };

		if (OMX < 0.0f)
		{
			OMX = 0.0f;
		}

		float Root{ Sqrt(OMX) };
		float Result{ ((((((-0.0012624911f * X + 0.0066700901f) * X - 0.0170881256f) * X + 0.0308918810f) * X - 0.0501743046f) * X + 0.0889789874f) * X - 0.2145988016f) * X + FASTASIN_HALF_PI };
		Result *= Root;
		return ((NonNegative) ? FASTASIN_HALF_PI - Result : Result - FASTASIN_HALF_PI);
	}

#undef FASTASIN_HALF_PI


	// 
	// @param ScalarSin - A reference to
	// @param ScalarCos - A reference to 
	// @param Value - 
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


	// 
	// @param S1 - 
	// @param S2 - 
	// @param Epsilon - 
	// @return - 
	static inline bool ScalarNearEqual(float S1, float S2, float Epsilon)
	{
		float Delta = S1 - S2;
		return (fabsf(Delta) <= Epsilon);
	}


	// 
	// @param pSin - A reference to 
	// @param pCos - A reference to
	// @param Value - 
	DEPRECATED("This function is deprecated - Use TMath::SinCos() instead.")
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


	// Converts from Radians to Degrees
	// @param - The value to convert to radians.
	// @return - The converted value.
	static float ToRadians(float Degrees)
	{
		return TO_RADIAN(Degrees);
	}


	// Converts from Degrees to Radians.
	// @param - The value to convert to dagrees.
	// @return - The converted value.
	static float ToDegrees(float Radians)
	{
		return TO_DEGREES(Radians);
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


	static inline float InvSqrt(float F)
	{
		return 1.0f / sqrtf(F);
	}


	// 
	static inline float Abs(const float Value)
	{
		return fabsf(Value);
	}


	template <class Type>
	static inline Type Max(const Type A, const Type B)
	{
		return (A >= B) ? A : B;
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


	// Tests if a value is between a minimum and maximum value.
	// @param Min - The low-point value to compare against.
	// @param Max - The high-point value to compare against.
	// @param Value - The value used to compare against the min and max.
	// @return - Returns true if the value is between the min and max.
	template <typename Type>
	static INLINE bool Range(const Type& Min, const Type& Max, const Type& Value)
	{
		return ((Value >= Min) && (Value <= Max));
	}


	// Tests if a value is between a minimum and maximum value.
	// @param Min - The low-point value to compare against.
	// @param Max - The high-point value to compare against.
	// @param Value - The value used to compare against the min and max.
	// @return - Returns true if the value is between the min and max.
	static INLINE bool Range(const int& Min, const int& Max, const int& Value)
	{
		return Range<int>(Min, Max, Value);
	}


	// Tests if a value is between a minimum and maximum value.
	// @param Min - The low-point value to compare against.
	// @param Max - The high-point value to compare against.
	// @param Value - The value used to compare against the min and max.
	// @return - Returns true if the value is between the min and max.
	static INLINE bool Range(const float& Min, const float& Max, const float& Value)
	{
		return Range<float>(Min, Max, Value);
	}


	// Tests if a value is between a minimum and maximum value.
	// @param Min - The low-point value to compare against.
	// @param Max - The high-point value to compare against.
	// @param Value - The value used to compare against the min and max.
	// @return - Returns true if the value is between the min and max.
	static INLINE bool Range(const double& Min, const double& Max, const double& Value)
	{
		return Range<double>(Min, Max, Value);
	}


	//...

	static inline bool IsNaN(float Value)
	{
		return _isnan(Value) != 0;
	}


	static inline bool IsFinite(float Value)
	{
		return _finite(Value) != 0;
	}


	// Returns a value based on comparand.
	static inline float FloatSelect(float Comparand, float ValueGEZero, float ValueLTZero)
	{
		return ((Comparand >= 0.0f) ? ValueGEZero : ValueLTZero);
	}


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

	static inline float FMod(float X, float Y)
	{
		if (fabsf(Y) <= 1.e-8f)
		{
			return 0.0f;
		}

		const float Quotient{ TruncFloat(X / Y) };
		float IntPortion{ Y * Quotient };


		if (fabsf(IntPortion) > fabsf(X))
		{
			IntPortion = X;
		}
		return X - IntPortion;
	}



};


//#ifndef PI
//#define PI
//const float TMath::Pi{ 3.14159265358f };
//const float TMath::InvsersePi{ 0.31830988618f };
//const float TMath::HalfPi{ 1.57079632679f };
//#endif