#pragma once
#include "../MathValues.h"


// Other libraries.

#ifdef INCLUDE_DIRECTX_MATH
#include <DirectXMath.h>
#endif

// Temporary Includes -- Use SString and CConsole instead.
#include <string>


// Stores the different types of axis possible.
// Used to easily access values in a vector.
enum EAxis { X = 0, Y = 1, Z = 2, W = 3 };


// A struct used to get a point in space. Can handle any dimensions.
// @template Size - How many dimensions this vector should have.
// @template Element - The datatype this vector should use.
template <uint Size, typename Element = float>
struct Vector
{
private:
	/// Properties

	// Stores all the Elements of this vector class.
	Element Data[Size]{ Element(0.0f) };

public:

	/// Constructors

	// Constructor, Default. Creates an empty vector.
	Vector<Size, Element>()
	{
		for (uint i = 0; i < Size; ++i)
		{
			Data[i] = (Element)0.0f;
		}
	}

	// Constructor, Initializes a Vector2 using 2 values.
	Vector<Size, Element>(Element InX, Element InY)
	{
		ASSERT(Size == 2, "Error: Illigal use of constructor. Is the vector the correct size?");
		Data[0] = InX;
		Data[1] = InY;
	}

	// Constructor, Initializes a Vector3 using 3 values.
	Vector<Size, Element>(Element InX, Element InY, Element InZ)
	{
		ASSERT(Size == 3, "Error: Illigal use of constructor. Is the vector the correct size?");
		Data[0] = InX;
		Data[1] = InY;
		Data[2] = InZ;
	}

	// Constructor, Initializes a Vector4 using 4 value.
	Vector<Size, Element>(Element InX, Element InY, Element InZ, Element InW)
	{
		ASSERT(Size == 4, "Error: Illigal use of constructor. Is the vector the correct size?");
		Data[0] = InX;
		Data[1] = InY;
		Data[2] = InZ;
		Data[3] = InW;
	}

	// Constructor, Initializes a Vector4 using 2 Vector2s.
	Vector<Size, Element>(Vector<2, Element> InV, Vector<2, Element> InV2)
	{
		ASSERT(Size == 4, "Error: Illigal use of constructor. Is the vector the correct size?");
		Data[0] = InV[0];
		Data[1] = InV[1];
		Data[2] = InV2[0];
		Data[3] = InV2[1];
	}

	// Constructor, Initializes a Vector4 using a Vector2 and 2 values.
	Vector<Size, Element>(Vector<2, Element> InV, Element InZ, Element InW)
	{
		ASSERT(Size == 4, "Error: Illigal use of constructor. Is the vector the correct size?");
		Data[0] = InV[0];
		Data[1] = InV[1];
		Data[2] = InZ;
		Data[3] = InW;
	}

	// Constructor, Initializes the vector with the inputted components.
	Vector<Size, Element>(Element InE[Size])
		: Data{ InE }
	{}

	// Constructor, Initializes all vector components with the inputted value.
	Vector<Size, Element>(Element InE)
	{
		for (uint i = 0; i < Size; ++i)
		{
			Data[i] = InE;
		}
	}

	// Constructor, Initializes this vector with the components of another vector.
	// @param Other - The other vector to copy the values from.
	// @param FloodValue - The value to give this vector if the other vector is smaller than this one.
	template <uint Size2, typename Element2>
	Vector<Size, Element>(Vector<Size2, Element2> Other, float FloodValue = 0.0f)
	{
		for (uint i = 0; i < Size; ++i)
		{
			Data[i] = Element((i < Size2) ? Other[i] : FloodValue);
		}
	}


	/// Operators

	// Operator, Returns the result of an addition between this vector and another vector.
	template <uint Size2, typename Element2>
	INLINE Vector<Size, Element> operator+(const Vector<Size2, Element2>& V) const;

	// Operator, Returns the result of an addition between this vector and an element value.
	INLINE Vector<Size, Element> operator+(const Element& E) const;

	// Operator, Returns the result of an addition between an element value and this vector.
	INLINE friend Vector<Size, Element> operator+(const Element& E, const Vector<Size, Element>& V)
	{
		Vector<Size, Element> Result;
		for (uint i = 0; i < Size; ++i)
		{
			Result[i] = E + V[i];
		}
		Result.CheckNaN();
		return Result;
	}

	// Operator, Sets this vector's values with the result of an addition between this vector and another vector.
	template <uint Size2, typename Element2>
	INLINE Vector<Size, Element> operator+=(const Vector<Size2, Element2>& V);

	// Operator, Sets this vector's values with the result of an addition between this vector and an element value.
	INLINE Vector<Size, Element> operator+=(const Element& E);

	// Operator, Returns the result of a subtraction between this vector and another vector.
	template <uint Size2, typename Element2>
	INLINE Vector<Size, Element> operator-(const Vector<Size2, Element2>& V) const;

	// Operator, Returns the result of a subtraction between this vector and an element value.
	INLINE Vector<Size, Element> operator-(const Element& E) const;

	// Operator, Returns the result of a subtraction between an element value and this vector.
	INLINE friend Vector<Size, Element> operator-(const Element& E, const Vector<Size, Element>& V)
	{
		Vector<Size, Element> Result;
		for (uint i = 0; i < Size; ++i)
		{
			Result[i] = E - V[i];
		}
		Result.CheckNaN();
		return Result;
	}

	// Operator, Returns the contents of this vector but negative.
	INLINE Vector<Size, Element> operator-() const;

	// Operator, Sets this vector's values with the result of a subtraction between this vector and another vector.
	template <uint Size2, typename Element2>
	INLINE Vector<Size, Element> operator-=(const Vector<Size2, Element2>& V);

	// Operator, Sets this vector's values with the result of a subtraction between this vector and an element value.
	INLINE Vector<Size, Element> operator-=(const Element& E);

	// Operator, Returns the result of a multiplication between this vector and another vector.
	template <uint Size2, typename Element2>
	INLINE Vector<Size, Element> operator*(const Vector<Size2, Element2>& V) const;

	// Operator, Returns the result of a multiplication between this vector and another vector.
	INLINE Vector<Size, Element> operator*(const Element& E) const;

	// Operator, Returns the result of a multiplication between an element value and this vector.
	INLINE friend Vector<Size, Element> operator*(const Element& E, const Vector<Size, Element>& V)
	{
		Vector<Size, Element> Result;
		for (uint i = 0; i < Size; ++i)
		{
			Result[i] = E * V[i];
		}
		Result.CheckNaN();
		return Result;
	}

	// Operator, Sets this vector's values with the result of a multiplication between this vector and another vector.
	template <uint Size2, typename Element2>
	INLINE Vector<Size, Element> operator*=(const Vector<Size2, Element2>& V);

	// Operator, Sets this vector's values with the result of a multiplication between this vector and an element value.
	INLINE Vector<Size, Element> operator*=(const Element& E);

	// Operator, Returns the result of a division between this vector and another vector.
	template <uint Size2, typename Element2>
	INLINE Vector<Size, Element> operator/(const Vector<Size2, Element2>& V) const;

	// Operator, Returns the result of a division between this vector and another vector.
	INLINE Vector<Size, Element> operator/(const Element& E) const;

	// Operator, Returns the result of a division between an element value and this vector.
	INLINE friend Vector<Size, Element> operator/(const Element& E, const Vector<Size, Element>& V)
	{
		Vector<Size, Element> Result;
		for (uint i = 0; i < Size; ++i)
		{
			Result[i] = E / V[i];
		}
		Result.CheckNaN();
		return Result;
	}

	// Operator, Sets this vector's values with the result of a division between this vector and another vector. 
	template <uint Size2, typename Element2>
	INLINE Vector<Size, Element> operator/=(const Vector<Size2, Element2>& V);

	// Operator, Sets this vector's values with the result of a division between this vector and an element value. 
	INLINE Vector<Size, Element> operator/=(const Element& E);

	// Operator, Increments all components of the vector by 1.
	INLINE Vector<Size, Element> operator++();

	// Operator, Decrements all components of the vector by 1.
	INLINE Vector<Size, Element> operator--();

	// Operator, Assigns all components to the value of a single input.
	INLINE Vector<Size, Element> operator=(const Element& E);

	// Operator, Calculates the cross product between this vector and another vector.
	INLINE Vector<Size, Element> operator|(const Vector<Size, Element>& V) const;

	// Operator, Calculates the dot product between this vector and another vector.
	INLINE Element operator^(const Vector<Size, Element>& V) const;

	// Operator, Tests if this vector is greater than another vector.
	INLINE bool operator>(const Vector<Size, Element>& V) const;

	// Operator, Test if all components of this vector is greater than an element value.
	INLINE bool operator>(const Element& E) const;

	// Operator, Test if this vector is greater than or equal to another vector.
	INLINE bool operator>=(const Vector<Size, Element>& V) const;

	// Operator, Test if all components of this vector is greater than or equal to an element value.
	INLINE bool operator>=(const Element& E) const;

	// Operator, Test if this vector is less than another vector.
	INLINE bool operator<(const Vector<Size, Element>& V) const;

	// Operator, Test if all components of this vector is less than an element value.
	INLINE bool operator<(const Element& E) const;

	// Operator, Test if this vector is less than or equal to another vector.
	INLINE bool operator<=(const Vector<Size, Element>& V) const;

	// Operator, Test if all components of this vector is less than or equal to an element value.
	INLINE bool operator<=(const Element& E) const;

	// Operator, Test if this vector is equal to another vector.
	INLINE bool operator==(const Vector<Size, Element>& V) const;

	// Operator, Test if all components of this vector is equal to an element value.
	INLINE bool operator==(const Element& E) const;

	// Operator, Test if this vector is not equal to another vector.
	INLINE bool operator!=(const Vector<Size, Element>& V) const;

	// Operator, Test if all components of this vector is not equal to an element value.
	INLINE bool operator!=(const Element& E) const;

	// Operator, Gets an element from the vector based off an input.
	INLINE Element& operator[](const uint& Component);

	// Operator, Gets an element from the vector based off an input.
	INLINE Element operator[](const uint& Component) const;

	// Operator, Gets an element from the vector based off an axis.
	INLINE Element& operator[](const EAxis& Axis);

	// Operator, Gets an element from the vector based off an axis.
	INLINE Element operator[](const EAxis& Axis) const;



	/// Conversions

#ifdef INCLUDE_DIRECTX_MATH
// Converts a DirectX::XMVECTOR to this type of vector.
// @param V - The XMVECTOR to convert.
// @return - The converted vector.
	static INLINE Vector<Size, Element> FromXMVector(DirectX::XMVECTOR V)
	{
		Vector<Size, Element> Result;
		switch (Size)
		{
		default:
		case 4:
			Result[3] = DirectX::XMVectorGetW(V);

		case 3:
			Result[2] = DirectX::XMVectorGetZ(V);

		case 2:
			Result[1] = DirectX::XMVectorGetY(V);

		case 1:
			Result[0] = DirectX::XMVectorGetX(V);
			return Result;
		}
	}
#endif

	// Converts this vector to a specified type.
	template <typename Type>
	INLINE Vector<Size, Type> ToType();

	// Converts this vector to a specified type.
	template <typename Type>
	INLINE Vector<Size, Type> ToType() const;

	// Converts this vector to a vector of floats.
	INLINE Vector<Size, float> ToFloat();

	// Converts this vector to a vector of integers.
	INLINE Vector<Size, int> ToInt();

	// Converts this vector to a vector of double floats.
	INLINE Vector<Size, double> ToDouble();

	// Converts this vector to a vector of floats.
	INLINE Vector<Size, float> ToFloat() const;

	// Converts this vector to a vector of integers.
	INLINE Vector<Size, int> ToInt() const;

	// Converts this vector to a vector of double floats.
	INLINE Vector<Size, double> ToDouble() const;

#ifdef INCLUDE_DIRECTX_MATH
	// Converts this vector to a DirectX::XMVECTOR.
	INLINE DirectX::XMVECTOR ToXMVector() const;
#endif



	/// Debug

	// Debug diagnostics handle for when a vector contains NaN.
	INLINE void CheckNaN() const;

	// Checks if this vector components contains NaN.
	INLINE bool ContainsNaN() const;

	// Prints out the contents of this vector to the console.
	INLINE void Print() const;



	/// Functions

	// Calculates the cross product between this vector and another vector.
	// @param V - The inputted vector to calculate against.
	// @return - The resulting vector.
	INLINE Vector<3, Element> CrossProduct(const Vector<3, Element>& V) const;

	// Calculates the dot product between this vector and another vector.
	// @param V - The inputted vector to calculate against.
	// @return - The resulting vector.
	INLINE float DotProduct(const Vector<Size, Element>& V) const;

	// Creates a vector with the highest values in each dimension between this vector and an inputted vector.
	// @param V - The inputted vector to calculate against.
	// @return - The resulting vector.
	INLINE Vector<Size, Element> Max(const Vector<Size, Element>& V) const;

	// Gets the highest value in this vector.
	// @return - The highest component in this vector.
	INLINE Element MaxComp() const;

	// Creates a vector with the lowest values in each dimension between this vector and an inputted vector.
	// @param V - The inputted vector to calculate against.
	// @return - The resulting vector.
	INLINE Vector<Size, Element> Min(const Vector<Size, Element>& V) const;

	// Gets the lowest value in this vector.
	// @return - The lowest component in this vector.
	INLINE Element MinComp() const;

	// Normalizes the vector.
	INLINE Vector<Size, Element> Normalize() const;

	// Returns true if this vector is almost equal to another vector.
	// @param Other - The vector to compare with.
	// @param Threshold - The range in which the other vector can be in.
	// @return - Returns true if the other vector is within range of this vector.
	INLINE bool NearlyEqual(const Vector<Size, Element>& Other, const Element& Threshold = MICRO_NUMBER) const;

	// Checks to see if this vector is close to zero based on a range.
	// @param Range - The threshold to check how close to zero the vector is.
	INLINE bool NearlyZero(float Threshold = MICRO_NUMBER) const;

	// Checks to see if this vector's values are 0.
	// @return - Returns true if this vector's values are equal to zero.
	INLINE bool IsZero() const;

	// Powers the entire vector a specified amount of times.
	// @param Amount - The power.
	// @return The vector powered.
	INLINE Vector<Size, Element> Power(uint Amount) const;

	// Multiplies this vector by itself.
	// @return - Returns this vector doubled.
	INLINE float SizeSquared() const;

	// Returns a modified size of this vector.
	// @template NewSize - The size of the new vector to be created.
	// @param Value - The value to add to the end of the vector (if expanding).
	// @return - A new vector with copied components of this vector.
	template <uint NewSize>
	INLINE Vector<NewSize, Element> Resize(const Element& Value = 0.0f) const;



	/// Setters

	// Sets the X component based on the inputted value.
	// @param Value - The value to set this component.
	INLINE void SetX(const Element& Value);

	// Sets the Y component based on the inputted value.
	// @param Value - The value to set this component.
	INLINE void SetY(const Element& Value);

	// Sets the Z component based on the inputted value.
	// @param Value - The value to set this component.
	INLINE void SetZ(const Element& Value);

	// Sets the W component based on the inputted value.
	// @param Value - The value to set this component.
	INLINE void SetW(const Element& Value);



	/// Getters

	// Returns the inputted component of this vector.
	INLINE Element& GetComponent(const EAxis& Component);

	// Returns the inputted component of this vector.
	INLINE Element GetComponent(const EAxis& Component) const;

	// Returns the X component of this vector.
	INLINE Element& X();

	// Returns the X component of this vector.
	INLINE Element X() const;

	// Returns the Y component of this vector.
	INLINE Element& Y();

	// Returns the Y component of this vector.
	INLINE Element Y() const;

	// Returns the Z component of this vector.
	INLINE Element& Z();

	// Returns the Z component of this vector.
	INLINE Element Z() const;

	// Returns the W component of this vector.
	INLINE Element& W();

	// Returns the W component of this vector.
	INLINE Element W() const;

	// Returns the amount of dimensions this vector has.
	INLINE uint GetSize() const { return Size; }

	// Returns the X component.
	INLINE Element& GetX();

	// Returns the X component.
	INLINE Element GetX() const;

	// Returns the X component.
	INLINE Element& GetY();

	// Returns the Y component.
	INLINE Element GetY() const;

	// Returns the X component.
	INLINE Element& GetZ();

	// Returns the Z component.
	INLINE Element GetZ() const;

	// Returns the X component.
	INLINE Element& GetW();

	// Returns the W component.
	INLINE Element GetW() const;



	/// Statics

	// Returns the dot product between two vectors.
	// @param V1 - The first vector.
	// @param V2 - The second vector.
	// @return - The dot product between the first and second vectors.
	static INLINE float DotProduct(const Vector<Size, Element>& V1, const Vector<Size, Element>& V2)
	{
		return V1 ^ V2;
	}


	// Calculates the cross product between two vectors.
	// @param V1 - The first vector.
	// @param V2 - The second vector.
	// @return - A new vector with the cross product between the first and second vectors.
	static INLINE Vector<Size, Element> CrossProduct(const Vector<Size, Element>& V1, const Vector<Size, Element>& V2)
	{
		return V1 | V2;
	}


	// Gets the value between two vectors based on a percentage value.
	// @param Min - The minimum value of the lerp.
	// @param Max - The maximum value of the lerp.
	// @param Value - The point between the two vectors (between 0 - 1).
	// @return - The vector at the position of the value.
	static INLINE Vector<Size, Element> Lerp(const Vector<Size, Element>& Min, const Vector<Size, Element>& Max, float Value)
	{
		return ((Max - Min) * Value) + Min;
	}


	// Powers the entire vector a specified amount of times.
	// @param V - The vector to power.
	// @param Amount - The power.
	// @return - The vector powered.
	static INLINE Vector<Size, Element> Power(const Vector<Size, Element>& V, uint Amount)
	{
		return V.Power(Amount);
	}


	// Normalizes the vector.
	// @param V - The vector to normalize.
	// @return - The normalized value.
	static INLINE Vector<Size, Element> Normalize(Vector<Size, Element> V)
	{
		return V.Normalize();
	}


	// Shorthand way of typing Vector{ 0, 1, 0 }.
	// Vector size must have a Y component.
	static INLINE Vector<Size, Element> Up()
	{
		ASSERT(Size >= 2, "Vector size is too small");
		Vector<Size, Element> Vec;
		Vec = (Element)0.0f;
		Vec[EAxis::Y] = (Element)1.0f;
		return Vec;
	}


	// Shorthand way of typing Vector{ 0, -1, 0 }.
	// Vector size must have a Y component.
	static INLINE Vector<Size, Element> Down()
	{
		ASSERT(Size >= 2, "Vector size is too small");
		Vector<Size, Element> Vec;
		Vec = (Element)0.0f;
		Vec[EAxis::Y] = (Element)-1.0f;
		return Vec;
	}


	// Shorthand way of typing Vector{ -1, 0, 0 }.
	// Vector size must have an X component.
	static INLINE Vector<Size, Element> Left()
	{
		ASSERT(Size >= 1, "Vector size is too small");
		Vector<Size, Element> Vec;
		Vec = (Element)0.0f;
		Vec[EAxis::X] = (Element)-1.0f;
		return Vec;
	}


	// Shorthand way of typing Vector{ 1, 0, 0 }.
	// Vector size must have an X component.
	static INLINE Vector<Size, Element> Right()
	{
		ASSERT(Size >= 1, "Vector size is too small");
		Vector<Size, Element> Vec;
		Vec = (Element)0.0f;
		Vec[EAxis::X] = (Element)1.0f;
		return Vec;
	}


	// Shorthand way of typing Vector{ 0, 0, 1 }.
	// Vector size must have a Z component.
	static INLINE Vector<Size, Element> Forward()
	{
		ASSERT(Size >= 3, "Vector size is too small");
		Vector<Size, Element> Vec;
		Vec = (Element)0.0f;
		Vec[EAxis::Z] = (Element)1.0f;
		return Vec;
	}


	// Shorthand way of typing Vector{ 0, 0, -1 }.
	// Vector size must have a Z component.
	static INLINE Vector<Size, Element> Backward()
	{
		ASSERT(Size >= 3, "Vector size is too small");
		Vector<Size, Element> Vec;
		Vec = (Element)0.0f;
		Vec[EAxis::Z] = (Element)-1.0f;
		return Vec;
	}


	// Returns true if the two imputted vectors are almost equal to each other based on a range.
	// @param Other - The vector to compare with.
	// @param Threshold - The range in which the other vector can be in.
	// @return - Returns true if the other vector is within range of this vector.
	static INLINE bool NearlyEqual(const Vector<Size, Element>& A, const Vector<Size, Element>& B, const Element& Threshold)
	{
		return A.NearlyEqual(B, Threshold);
	}


	// Creates a vector with the highest values in each dimension between both inputted vectors.
	// @param V1 - The first vector to use.
	// @param V2 - The second vector to use.
	// @return - A new vector with the highest values between both vectors.
	static INLINE Vector<Size, Element> Max(const Vector<Size, Element>& V1, const Vector<Size, Element>& V2)
	{
		return V1.Max(V2);
	}


	// Gets the highest value in the inputted vector.
	// @param V - The vector to get the highest value component from.
	// @return - The highest value in the vector.
	static INLINE Element MaxComp(const Vector<Size, Element>& V)
	{
		return V.MaxComp();
	}


	// Creates a vector with the lowest values in each dimension between both inputted vectors.
	// @param V1 - The first vector to use.
	// @param V2 - The second vector to use.
	// @return - A new vector with the lowest values between both vectors.
	static INLINE Vector<Size, Element> Min(const Vector<Size, Element>& V1, const Vector<Size, Element>& V2)
	{
		return V1.Min(V2);
	}


	// Gets the lowest value in the inputted vector.
	// @param V - The vector to get the lowest value from.
	// @return - The lowest value in the inputted vector.
	static INLINE Element MinComp(const Vector<Size, Element>& V)
	{
		return V.MinComp();
	}


	// Calculates the distance between two vectors.
	// @param V1 - The first vector.
	// @param V2 - The second vector.
	// @return - Returns the distance between the two vectors.
	static INLINE float Distance(const Vector<Size, Element>& V1, const Vector<Size, Element>& V2)
	{
		Vector<Size, Element> Delta{ V1 - V2 };
		return TMath::Sqrt(Vector<Size, Element>::DotProduct(Delta, Delta));
	}


	// Calculates the distance between two vectors squared.
	// @param V1 - The first vector.
	// @param V2 - The second vector.
	// @return - Returns the distance between the two vectors squared.
	static INLINE float DistanceSquared(const Vector<Size, Element>& V1, const Vector<Size, Element>& V2)
	{
		Vector<Size, Element> Delta{ V1 - V2 };
		return Vector<Size, Element>::DotProduct(Delta, Delta);
	}


	// Creates a new vector by selecting using values in two vectors and a bool value (true = V1, false = V2).
	// @param V1 - The first vector type to use.
	// @param V2 - The second vector type to use.
	// @param Control - Determines which vector to use for each axis.
	// @return - Returns a new vector with the selected values.
	static INLINE Vector<Size, Element> Select(Vector<Size, Element> V1, Vector<Size, Element> V2, Vector<Size, bool> Control)
	{
		Vector<Size, Element> Result;
		for (uint i = 0; i < Size; ++i)
		{
			//Result[i] = V1[i] & ~Control[i] | V2[i] & Control[0]; 
			Result[i] = ((Control[i]) ? V1[i] : V2[i]);
		}
		Result.CheckNaN();
		return Result;
	}


	// Merges two vectors together based on the inputted axis.
	// @param V1 - The first vector to use.
	// @param V2 - The second vector to use.
	// @param A - The axis to initiate the first two values.
	// @param B - The axis to initiate the last two values.
	// @return - Returns a vector4 with the merged values.
	static INLINE Vector<4, Element> Merge(Vector<4, Element> V1, Vector<4, Element> V2, EAxis A, EAxis B)
	{
		Vector<4, Element> Result
		{
			V1[A],
			V2[A],
			V1[B],
			V2[B]
		};
		Result.CheckNaN();
		return Result;
	}
};


// A float vector with 2 dimensions.
typedef Vector<2, float> SVector2;

// A float vector with 3 dimensions.
typedef Vector<3, float> SVector3;

// A float vector with 3 dimensions.
typedef Vector<3, float> SVector;

// A float vector with 4 dimensions.
typedef Vector<4, float> SVector4;

// A double vector with 2 dimensions.
typedef Vector<2, double> SVector2d;

// A double vector with 3 dimensions.
typedef Vector<3, double> SVector3d;

// A double vector with 4 dimensions.
typedef Vector<4, double> SVector4d;

// An int vector with 2 dimensions.
typedef Vector<2, int> SVector2i;

// An int vector with 3 dimensions.
typedef Vector<3, int> SVector3i;

// An int vector with 4 dimensions.
typedef Vector<4, int> SVector4i;

// A bool vector with 2 dimensions, used for Vector::Select().
typedef Vector<2, bool> SVector2Control;

// A bool vector with 3 dimensions, used for Vector::Select().
typedef Vector<3, bool> SVectorControl;

// A bool vector with 3 dimensions, used for Vector::Select().
typedef Vector<3, bool> SVector3Control;

// A bool vector with 4 dimensions, used for Vector::Select().
typedef Vector<4, bool> SVector4Control;


template <uint Size, typename Element>
INLINE static Vector<3, Element> CrossProduct(const Vector<3, Element>& A, const Vector<3, Element>& B)
{
	return A | B;
}


template <uint Size, typename Element>
INLINE static float DotProduct(const Vector<Size, Element>& A, const Vector<Size, Element>& B)
{
	return A ^ B;
}


template <uint Size, typename Element>
template <uint Size2, typename Element2>
INLINE Vector<Size, Element> Vector<Size, Element>::operator+(const Vector<Size2, Element2>& V) const
{
	uint Count{ (Size < Size2) ? Size : Size2 };
	Vector<Size, Element> Result;
	for (uint i = 0; i < Count; ++i)
	{
		Result[i] = Data[i] + (Element)V[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::operator+(const Element& E) const
{
	Vector<Size, Element> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = Data[i] + E;
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Element>
template <uint Size2, typename Element2>
INLINE Vector<Size, Element> Vector<Size, Element>::operator+=(const Vector<Size2, Element2>& V)
{
	uint Count{ (Size < Size2) ? Size : Size2 };
	for (uint i = 0; i < Count; ++i)
	{
		Data[i] += (Element)V[i];
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::operator+=(const Element& E)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] += E;
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Element>
template <uint Size2, typename Element2>
INLINE Vector<Size, Element> Vector<Size, Element>::operator-(const Vector<Size2, Element2>& V) const
{
	uint Count{ (Size < Size2) ? Size : Size2 };
	Vector<Size, Element> Result;
	for (uint i = 0; i < Count; ++i)
	{
		Result[i] = Data[i] - (Element)V[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::operator-(const Element& E) const
{
	Vector<Size, Element> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = Data[i] - E;
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::operator-() const
{
	Vector<Size, Element> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = -Data[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Element>
template <uint Size2, typename Element2>
INLINE Vector<Size, Element> Vector<Size, Element>::operator-=(const Vector<Size2, Element2>& V)
{
	uint Count{ (Size < Size2) ? Size : Size2 };
	for (uint i = 0; i < Count; ++i)
	{
		Data[i] -= (Element)V[i];
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::operator-=(const Element& E)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] -= E;
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Element>
template <uint Size2, typename Element2>
INLINE Vector<Size, Element> Vector<Size, Element>::operator*(const Vector<Size2, Element2>& V) const
{
	uint Count{ (Size < Size2) ? Size : Size2 };
	Vector<Size, Element> Result;
	for (uint i = 0; i < Count; ++i)
	{
		Result[i] = Data[i] * (Element)V[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::operator*(const Element& E) const
{
	Vector<Size, Element> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = Data[i] * E;
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Element>
template <uint Size2, typename Element2>
INLINE Vector<Size, Element> Vector<Size, Element>::operator*=(const Vector<Size2, Element2>& V)
{
	uint Count{ (Size < Size2) ? Size : Size2 };
	for (uint i = 0; i < Count; ++i)
	{
		Data[i] *= (Element)V[i];
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::operator*=(const Element& E)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] *= E;
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Element>
template <uint Size2, typename Element2>
INLINE Vector<Size, Element> Vector<Size, Element>::operator/(const Vector<Size2, Element2>& V) const
{
	uint Count{ (Size < Size2) ? Size : Size2 };
	Vector<Size, Element> Result;
	for (uint i = 0; i < Count; ++i)
	{
		Result[i] = Data[i] / (Element)V[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::operator/(const Element& E) const
{
	Vector<Size, Element> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = Data[i] / E;
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Element>
template <uint Size2, typename Element2>
INLINE Vector<Size, Element> Vector<Size, Element>::operator/=(const Vector<Size2, Element2>& V)
{
	uint Count{ (Size < Size2) ? Size : Size2 };
	for (uint i = 0; i < Count; ++i)
	{
		Data[i] /= (Element)V[i];
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::operator/=(const Element& E)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] /= E;
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::operator++()
{
	for (uint i = 0; i < Size; ++i)
	{
		++Data[i];
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::operator--()
{
	for (uint i = 0; i < Size; ++i)
	{
		--Data[i];
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::operator=(const Element& E)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] = E;
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::operator|(const Vector<Size, Element>& V) const
{
	Vector<Size, Element> Result{ 0.0f };
	Result[EAxis::X] = (Data[EAxis::Y] * V[EAxis::Z]) - (Data[EAxis::Z] * V[EAxis::Y]);
	Result[EAxis::Y] = (Data[EAxis::Z] * V[EAxis::X]) - (Data[EAxis::X] * V[EAxis::Z]);
	Result[EAxis::Z] = (Data[EAxis::X] * V[EAxis::Y]) - (Data[EAxis::Y] * V[EAxis::X]);
	Result.CheckNaN();
	return Result;
};


template <uint Size, typename Element>
INLINE Element Vector<Size, Element>::operator^(const Vector<Size, Element>& V) const
{
	Element Result{ 0.0f };
	for (uint i = 0; i < Size; ++i)
	{
		Result += Data[i] * V[i];
	}
	//if (TMath::IsFinite(Result)) Result{ 0.0f };
	return Result;
}


template <uint Size, typename Element>
INLINE bool Vector<Size, Element>::operator>(const Vector<Size, Element>& V) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] <= V[i])
			return false;
	}
	return true;
}


template <uint Size, typename Element>
INLINE bool Vector<Size, Element>::operator>(const Element& E) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] <= E)
			return false;
	}
	return true;
}


template <uint Size, typename Element>
INLINE bool Vector<Size, Element>::operator>=(const Vector<Size, Element>& V) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] < V[i])
			return false;
	}
	return true;
}


template <uint Size, typename Element>
INLINE bool Vector<Size, Element>::operator>=(const Element& E) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] < E)
			return false;
	}
	return true;
}



template <uint Size, typename Element>
INLINE bool Vector<Size, Element>::operator<(const Vector<Size, Element>& V) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] >= V[i])
			return false;
	}
	return true;
}


template <uint Size, typename Element>
INLINE bool Vector<Size, Element>::operator<(const Element& E) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] >= E)
			return false;
	}
	return true;
}


template <uint Size, typename Element>
INLINE bool Vector<Size, Element>::operator<=(const Vector<Size, Element>& V) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] > V[i])
			return false;
	}
	return true;
}


template <uint Size, typename Element>
INLINE bool Vector<Size, Element>::operator<=(const Element& E) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] > E)
			return false;
	}
	return true;
}


template <uint Size, typename Element>
INLINE bool Vector<Size, Element>::operator==(const Vector<Size, Element>& V) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] != V[i])
			return false;
	}
	return true;
}


template <uint Size, typename Element>
INLINE bool Vector<Size, Element>::operator==(const Element& E) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] != E)
			return false;
	}
	return true;
}


template <uint Size, typename Element>
INLINE bool Vector<Size, Element>::operator!=(const Vector<Size, Element>& V) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] == V[i])
			return false;
	}
	return true;
}


template <uint Size, typename Element>
INLINE bool Vector<Size, Element>::operator!=(const Element& E) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] == E)
			return false;
	}
	return true;
}


template <uint Size, typename Element>
INLINE Element& Vector<Size, Element>::operator[](const uint& Component)
{
	return Data[Component];
}


template <uint Size, typename Element>
INLINE Element Vector<Size, Element>::operator[](const uint& Component) const
{
	return Data[Component];
}


template <uint Size, typename Element>
INLINE Element& Vector<Size, Element>::operator[](const EAxis& Axis)
{
	return Data[Axis];
}


template <uint Size, typename Element>
INLINE Element Vector<Size, Element>::operator[](const EAxis& Axis) const
{
	return Data[Axis];
}


template <uint Size, typename Element>
template <typename Type>
INLINE Vector<Size, Type> Vector<Size, Element>::ToType()
{
	Vector<Size, Type> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = (Type)Data[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Element>
template <typename Type>
INLINE Vector<Size, Type> Vector<Size, Element>::ToType() const
{
	Vector<Size, Type> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = (Type)Data[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Element>
INLINE Vector<Size, float> Vector<Size, Element>::ToFloat()
{
	return ToType<float>();
}


template <uint Size, typename Element>
INLINE Vector<Size, int> Vector<Size, Element>::ToInt()
{
	return ToType<int>();
}


template <uint Size, typename Element>
INLINE Vector<Size, double> Vector<Size, Element>::ToDouble()
{
	return ToType<double>();
}


template <uint Size, typename Element>
INLINE Vector<Size, float> Vector<Size, Element>::ToFloat() const
{
	return ToType<float>();
}


template <uint Size, typename Element>
INLINE Vector<Size, int> Vector<Size, Element>::ToInt() const
{
	return ToType<int>();
}


template <uint Size, typename Element>
INLINE Vector<Size, double> Vector<Size, Element>::ToDouble() const
{
	return ToType<double>();
}


#ifdef INCLUDE_DIRECTX_MATH
template <uint Size, typename Element>
INLINE DirectX::XMVECTOR Vector<Size, Element>::ToXMVector() const
{
	switch (Size)
	{
	case 1:
		return DirectX::XMVectorSet(Data[0], 0.0f, 0.0f, 0.0f);

	case 2:
		return DirectX::XMVectorSet(Data[0], Data[1], 0.0f, 0.0f);

	case 3:
		return DirectX::XMVectorSet(Data[0], Data[1], Data[2], 0.0f);

	case 4:
	default:
		return DirectX::XMVectorSet(Data[0], Data[1], Data[2], Data[3]);
	}
}
#endif


template <uint Size, typename Element>
INLINE void Vector<Size, Element>::CheckNaN() const
{
	if (ContainsNaN())
	{
		printf("Vector contains NaN\n");
		*const_cast<Vector<Size, Element>*>(this) = Vector<Size, Element>{ 0.0f };
	}
}


template <uint Size, typename Element>
INLINE bool Vector<Size, Element>::ContainsNaN() const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (TMath::IsFinite(Data[i])) return false;
	}
	return true;
}


template <uint Size, typename Element>
INLINE void Vector<Size, Element>::Print() const
{
	for (uint i = 0; i < Size; ++i)
	{
		printf("%f, ", Data[i]);
	}
	printf("\n");
}


template <uint Size, typename Element>
INLINE Vector<3, Element> Vector<Size, Element>::CrossProduct(const Vector<3, Element>& V) const
{
	return *this | V;
}


template <uint Size, typename Element>
INLINE float Vector<Size, Element>::DotProduct(const Vector<Size, Element>& V) const
{
	return *this ^ V;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::Max(const Vector<Size, Element>& V) const
{
	Vector<Size, Element> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = (Data[i] > V[i]) ? Data[i] : V[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Element>
INLINE Element Vector<Size, Element>::MaxComp() const
{
	Element Result{ Data[0] };
	for (uint i = 1; i < Size; ++i)
	{
		Result = (Result > Data[i]) ? Result : Data[i];
	}
	if (TMath::IsFinite(Result)) Result = 0.0f;
	return Result;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::Min(const Vector<Size, Element>& V) const
{
	Vector<Size, Element> Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result[i] = (Data[i] < V[i]) ? Data[i] : V[i];
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Element>
INLINE Element Vector<Size, Element>::MinComp() const
{
	Element Result{ Data[0] };
	for (uint i = 1; i < Size; ++i)
	{
		Result = (Result < Data[i]) ? Result : Data[i];
	}
	if (TMath::IsFinite(Result)) Result = 0.0f;
	return Result;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::Normalize() const
{
	return *this / DotProduct(*this);
}


template <uint Size, typename Element>
INLINE bool Vector<Size, Element>::NearlyEqual(const Vector<Size, Element>& Other, const Element& Threshold) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] <= Other[i] - Threshold || Data[i] >= Other[i] + Threshold) return false;
	}
	return true;
}


template <uint Size, typename Element>
INLINE bool Vector<Size, Element>::NearlyZero(float Threshold) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (TMath::Abs(Data[i]) > Threshold)
		{
			return false;
		}
	}
	return true;
}


template <uint Size, typename Element>
INLINE bool Vector<Size, Element>::IsZero() const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] != Element(0))
		{
			return false;
		}
	}
	return true;
}


template <uint Size, typename Element>
INLINE Vector<Size, Element> Vector<Size, Element>::Power(uint Amount) const
{
	Vector<Size, Element> Result = Data;
	for (uint i = 0; i < Amount; ++i)
	{
		Result *= Data;
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Element>
INLINE float Vector<Size, Element>::SizeSquared() const
{
	float Result;
	for (uint i = 0; i < Size; ++i)
	{
		Result += Data[i] * Data[i];
	}
	if (TMath::IsFinite(Result)) Result = 0.0f;
	return Result;
}


template <uint Size, typename Element>
template <uint NewSize>
INLINE Vector<NewSize, Element> Vector<Size, Element>::Resize(const Element& Value) const
{
	Vector<NewSize, Element> Result;
	for (uint i = 0; i < NewSize; ++i)
	{
		Result[i] = (i < Size) ? Data[i] : Value;
	}
	Result.CheckNaN();
	return Result;
}


template <uint Size, typename Element>
INLINE void Vector<Size, Element>::SetX(const Element& Value)
{
	ASSERT(Size > 0, "This vector does not have a 'X' component.");
	Data[EAxis::X] = Value;
	CheckNaN();
}


template <uint Size, typename Element>
INLINE void Vector<Size, Element>::SetY(const Element& Value)
{
	ASSERT(Size > 1, "This vector does not have a 'Y' component.");
	Data[EAxis::Y] = Value;
	CheckNaN();
}


template <uint Size, typename Element>
INLINE void Vector<Size, Element>::SetZ(const Element& Value)
{
	ASSERT(Size > 2, "This vector does not have a 'Z' component.");
	Data[EAxis::Z] = Value;
	CheckNaN();
}


template <uint Size, typename Element>
INLINE void Vector<Size, Element>::SetW(const Element& Value)
{
	ASSERT(Size > 3, "This vector does not have a 'W' component.");
	Data[EAxis::W] = Value;
	CheckNaN();
}


template <uint Size, typename Element>
INLINE Element& Vector<Size, Element>::GetComponent(const EAxis& Component)
{
	return Data[Component];
}


template <uint Size, typename Element>
INLINE Element Vector<Size, Element>::GetComponent(const EAxis& Component) const
{
	return Data[Component];
}


template <uint Size, typename Element>
INLINE Element& Vector<Size, Element>::X()
{
	ASSERT(Size > 0, "This vector does not have a 'X' component.");
	return Data[EAxis::X];
}


template <uint Size, typename Element>
INLINE Element Vector<Size, Element>::X() const
{
	ASSERT(Size > 0, "This vector does not have a 'X' component.");
	return Data[EAxis::X];
}


template <uint Size, typename Element>
INLINE Element& Vector<Size, Element>::Y()
{
	ASSERT(Size > 1, "This vector does not have a 'Y' component.");
	return Data[EAxis::Y];
}


template <uint Size, typename Element>
INLINE Element Vector<Size, Element>::Y() const
{
	ASSERT(Size > 1, "This vector does not have a 'Y' component.");
	return Data[EAxis::Y];
}


template <uint Size, typename Element>
INLINE Element& Vector<Size, Element>::Z()
{
	ASSERT(Size > 2, "This vector does not have a 'Z' component.");
	return Data[EAxis::Z];
}


template <uint Size, typename Element>
INLINE Element Vector<Size, Element>::Z() const
{
	ASSERT(Size > 2, "This vector does not have a 'Z' component.");
	return Data[EAxis::Z];
}


template <uint Size, typename Element>
INLINE Element& Vector<Size, Element>::W()
{
	ASSERT(Size > 3, "This vector does not have a 'W' component.");
	return Data[EAxis::W];
}


template <uint Size, typename Element>
INLINE Element Vector<Size, Element>::W() const
{
	ASSERT(Size > 3, "This vector does not have a 'W' component.");
	return Data[EAxis::W];
}


template <uint Size, typename Element>
INLINE Element& Vector<Size, Element>::GetX()
{
	ASSERT(Size > 0, "This vector does not have a 'X' component.");
	return Data[EAxis::X];
}


template <uint Size, typename Element>
INLINE Element Vector<Size, Element>::GetX() const
{
	ASSERT(Size > 0, "This vector does not have a 'X' component.");
	return Data[EAxis::X];
}


template <uint Size, typename Element>
INLINE Element& Vector<Size, Element>::GetY()
{
	ASSERT(Size > 1, "This vector does not have a 'Y' component.");
	return Data[EAxis::Y];
}


template <uint Size, typename Element>
INLINE Element Vector<Size, Element>::GetY() const
{
	ASSERT(Size > 1, "This vector does not have a 'Y' component.");
	return Data[EAxis::Y];
}


template <uint Size, typename Element>
INLINE Element& Vector<Size, Element>::GetZ()
{
	ASSERT(Size > 2, "This vector does not have a 'Z' component.");
	return Data[EAxis::Z];
}


template <uint Size, typename Element>
INLINE Element Vector<Size, Element>::GetZ() const
{
	ASSERT(Size > 2, "This vector does not have a 'Z' component.");
	return Data[EAxis::Z];
}


template <uint Size, typename Element>
INLINE Element& Vector<Size, Element>::GetW()
{
	ASSERT(Size > 3, "This vector does not have a 'W' component.");
	return Data[EAxis::W];
}


template <uint Size, typename Element>
INLINE Element Vector<Size, Element>::GetW() const
{
	ASSERT(Size > 3, "This vector does not have a 'W' component.");
	return Data[EAxis::W];
}