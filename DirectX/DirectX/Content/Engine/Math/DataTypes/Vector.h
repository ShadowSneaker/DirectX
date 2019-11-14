#pragma once
#include "../MathValues.h"
#include <DirectXMath.h>

// Temporary Includes -- Use SString and CConsole instead.
#include <string>


// A helper Enum used to select a specifc component in common vector sizes.
enum EAxis { X = 0, Y = 1, Z = 2, W = 3 };


// A struct used to get a point in space. Can handle any dimensions.
template <uint Size, typename Element = float>
struct Vector
{
private:
	/// Properties

	// Stores all the Elements of this Vector class.
	Element Data[Size]{ Element(0.0f) };

public:

	/// Constructors

	// Constructor, Default. Creates an empty Vector.
	Vector<Size, Element>()
	{
		for (uint i = 0; i < Size; ++i)
		{
			Data[i] = (Element)0.0f;
		}
	}

	// Constructor, Initializes a Vector2 using 2 Values.
	Vector<Size, Element>(Element InX, Element InY)
	{
		ASSERT(Size == 2, "Error: Illigal use of constructor. Is the vector the correct size?");
		Data[0] = InX;
		Data[1] = InY;
	}

	// Constructor, Initializes a Vector3 using 3 Values.
	Vector<Size, Element>(Element InX, Element InY, Element InZ)
	{
		ASSERT(Size == 3, "Error: Illigal use of constructor. Is the vector the correct size?");
		Data[0] = InX;
		Data[1] = InY;
		Data[2] = InZ;
	}

	// Constructor, Initializes a Vector4 using 4 Value.
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

	// Constructor, Initializes a Vector4 using a Vector2 and 2 Values.
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

	// Constructor, Initializes all vector components with the inputed value.
	Vector<Size, Element>(Element InE)
	{
		for (uint i = 0; i < Size; ++i)
		{
			Data[i] = InE;
		}
	}

	// Constructor, Initiazes this vector with the components of another vector.
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

	// Operator, Returns the result between an addition this Vector and another Vector.
	template <uint Size2, typename Element2>
	inline Vector<Size, Element> operator+(const Vector<Size2, Element2>& V) const;

	// Operator, Returns the result between an addition this Vector and a Element Value.
	inline Vector<Size, Element> operator+(const Element& E) const;

	// Operator, Sets this Vectors values with the result of an addition between this Vector and another Vector.
	template <uint Size2, typename Element2>
	inline Vector<Size, Element> operator+=(const Vector<Size2, Element2>& V);

	// Operator, Sets this Vectors values with the result of an addition between this Vector and a Element Value.
	inline Vector<Size, Element> operator+=(const Element& E);

	// Operator, Returns the result between a subtraction this Vector and another Vector.
	template <uint Size2, typename Element2>
	inline Vector<Size, Element> operator-(const Vector<Size2, Element2>& V) const;

	// Operator, Returns the result between a subtraction this Vector and a Element Value.
	inline Vector<Size, Element> operator-(const Element& E) const;

	// Operator, Returns the the contents of this vector but negative.
	inline Vector<Size, Element> operator-() const;

	// Operator, Sets this Vectors values with the result of a subtraction between this Vector and another Vector.
	template <uint Size2, typename Element2>
	inline Vector<Size, Element> operator-=(const Vector<Size2, Element2>& V);

	// Operator, Sets this Vectors values with the result of a subtraction between this Vector and another Vector.
	inline Vector<Size, Element> operator-=(const Element& E);

	// Operator, Returns the result between a multiplication this Vector and another Vector.
	template <uint Size2, typename Element2>
	inline Vector<Size, Element> operator*(const Vector<Size2, Element2>& V) const;

	// Operator, Returns the result between a multiplication this Vector and another Vector.
	inline Vector<Size, Element> operator*(const Element& E) const;

	// Operator, Sets this Vectors values with the result of a multiplication between this Vector and another Vector.
	template <uint Size2, typename Element2>
	inline Vector<Size, Element> operator*=(const Vector<Size2, Element2>& V);

	// Operator, Sets this Vectors values with the result of a multiplication between this Vector and another Vector.
	inline Vector<Size, Element> operator*=(const Element& E);

	// Operator, Returns the result between a division this Vector and another Vector.
	template <uint Size2, typename Element2>
	inline Vector<Size, Element> operator/(const Vector<Size2, Element2>& V) const;

	// Operator, Returns the result between a division this Vector and another Vector.
	inline Vector<Size, Element> operator/(const Element& E) const;

	// Operator, Sets this Vectors values with the result of a division between this Vector and another Vector. 
	template <uint Size2, typename Element2>
	inline Vector<Size, Element> operator/=(const Vector<Size2, Element2>& V);

	// Operator, Sets this Vectors values with the result of a division between this Vector and another Vector. 
	inline Vector<Size, Element> operator/=(const Element& E);

	// Operator, Increments all components of the vector by 1.
	inline Vector<Size, Element> operator++();

	// Operator, Decrements all components of the vector by 1.
	inline Vector<Size, Element> operator--();

	// Operator, Assigns all components to the value of a single input.
	inline Vector<Size, Element> operator=(const Element& E);

	// Operator, Calculates the cross product between this Vector and another Vector.
	inline Vector<Size, Element> operator|(const Vector<Size, Element>& V) const;

	// Operator, Calculates the dot product between this Vector and another Vector.
	inline Element operator^(const Vector<Size, Element>& V) const;

	// Operator, Tests if this Vector is greater than another Vector.
	inline bool operator>(const Vector<Size, Element>& V) const;

	// Operator, Test if all components of this Vector is greater than an Element Value.
	inline bool operator>(const Element& E) const;

	// Operator, Test if this Vector is greater than or equal to another Vector.
	inline bool operator>=(const Vector<Size, Element>& V) const;

	// Operator, Test if all components of this Vector is greater than or equal to an Element Value
	inline bool operator>=(const Element& E) const;

	// Operator, Test if this Vector is less than another Vector.
	inline bool operator<(const Vector<Size, Element>& V) const;

	// Operator, Test if all components of this Vector is less than an Element Value.
	inline bool operator<(const Element& E) const;

	// Operator, Test if this Vector is less than or Equal to another Vector.
	inline bool operator<=(const Vector<Size, Element>& V) const;

	// Operator, Test if all components of this Vector is less than or equal to an Element Value.
	inline bool operator<=(const Element& E) const;

	// Operator, Test if this Vector is equal to another Vector.
	inline bool operator==(const Vector<Size, Element>& V) const;

	// Operator, Test if all components of this Vector is equal to an Element Value.
	inline bool operator==(const Element& E) const;

	// Operator, Test if this Vector is not equal to another Vectr.
	inline bool operator!=(const Vector<Size, Element>& V) const;

	// Operator, Test if all components of this Vector is not equal to an Element Value.
	inline bool operator!=(const Element& E) const;

	// Operator, gets an element from the Vector based off an input.
	inline Element& operator[](const uint Component);

	// Operator, gets an element from the Vector based off an input.
	inline Element operator[](const uint Component) const;


	/// Conversions

	// Converts this vector to a specified type.
	template <typename Type>
	inline Vector<Size, Type> ToType();

	// Converts this vector to a specified type.
	template <typename Type>
	inline Vector<Size, Type> ToType() const;

	// Converts this vector to a vector of floats.
	inline Vector<Size, float> ToFloat();

	// Converts this vector to a vector of intagers.
	inline Vector<Size, int> ToInt();

	// Converts this vector to a vector of double floats.
	inline Vector<Size, double> ToDouble();

	// Converts this vector to a vector of floats.
	inline Vector<Size, float> ToFloat() const;

	// Converts this vector to a vector of intagers.
	inline Vector<Size, int> ToInt() const;

	// Converts this vector to a vector of double floats.
	inline Vector<Size, double> ToDouble() const;

	//inline DirectX::XMVECTOR ToXMVector() const;


	/// Debug.

	// Debug Diagnostics handle for when a vector contains NaN.
	inline void CheckNaN() const;

	// Checks if this vector components contains NaN.
	inline bool ContainsNaN() const;


	/// Functions

	// Prints out the contents of this vector to the console. Returns the vector converted into a string.
	inline std::string Print(const bool bPrintToConsole = true) const;

	// Calculates the Cross Product between this Vector and another Vector.
	inline Vector<3, Element> CrossProduct(const Vector<3, Element>& V) const;

	// Calculates the Dot Product between this Vector and another Vector.
	inline float DotProduct(const Vector<Size, Element>& E) const;

	// Creates a vector with the highest values in each dimension between this vector and an inputted vector.
	inline Vector<Size, Element> Max(const Vector<Size, Element>& V) const;

	// Gets the highest value in this Vector.
	inline Element MaxComp() const;

	// Creates a vector with the lowest values in each dimension between this vector and an inputted vector.
	inline Vector<Size, Element> Min(const Vector<Size, Element>& V) const;

	// Gets the lowest value in this vector.
	inline Element MinComp() const;

	// Normalizes the vector.
	inline Vector<Size, Element> Normalize() const;

	// Returns true if this vector is almost equal to another vector.
	// @param Other - The vector to compare with.
	// @param Threshold - The range in which the other vector can be in.
	// @return - Returns true if the other vector is within range of this vector.
	inline bool NearlyEqual(const Vector<Size, Element>& Other, const Element& Threshold) const;

	// Checks to see if this vector is close to zero based on a range.
	// @param Range - The threshold to check how close to zero the vector is.
	inline bool NearlyZero(float Threshold = MICRO_NUMBER) const;

	// Checks to see if this vector's values are 0.
	// @return - Returns true if this vector's values are equal to zero
	inline bool IsZero();

	// Powers the entire vector a specified amount of times.
	// @param Amount - The power.
	// @return The vector powered.
	inline Vector<Size, Element> Power(uint Amount);

	// Multiplies this vector by iteself.
	// @return - Retursn this vector doubled.
	inline float SizeSquared() const;

	// Returns a modified size of this vector.
	// @param Value - The value to add to the end of the vector (if expanding).
	// @return - A new vector with copied compoenents of this vector.
	template <uint NewSize>
	inline Vector<NewSize, Element> Resize(const Element& Value = 0.0f) const;




	/// Getters

	// Returns the inputted component of this vector.
	inline Element& GetComponent(const EAxis& Component);

	// Returns the inputted component of this vector.
	inline Element GetComponent(const EAxis& Component) const;

	// Returns the X component of this vector.
	inline Element& X();

	// Returns the X component of this vector.
	inline Element X() const;

	// Returns the Y component of this vector.
	inline Element& Y();

	// Returns the Y component of this vector.
	inline Element Y() const;

	// Returns the Z component of this vector.
	inline Element& Z();

	// Returns the Z component of this vector.
	inline Element Z() const;

	// Returns the W component of this vector.
	inline Element& W();

	// Returns the W component of this vector.
	inline Element W() const;

	// Gets how many dimensions this vector is in.
	// @return - Returns how many dimensions this vector has.
	inline uint GetSize() const { return Size; }

	// Returns the X component.
	inline Element GetX() const;

	// Returns the Y component.
	inline Element GetY() const;

	// Returns the Z component.
	inline Element GetZ() const;

	// Returns the W component.
	inline Element GetW() const;


	/// Setters

	// Sets the X component based on the inputted value.
	inline void SetX(const Element& Value);

	// Sets the Y component based on the inputted value.
	inline void SetY(const Element& Value);

	// Sets the Z component based on the inputted value.
	inline void SetZ(const Element& Value);

	// Sets the W component based on the inputted value.
	inline void SetW(const Element& Value);


	/// Statics

	// Returns the dot product between two vectors.
	// @param V1 - The first vector.
	// @param V2 - The second vector.
	// @return - The dot product between the first and second vectors.
	static inline float DotProduct(const Vector<Size, Element>& V1, const Vector<Size, Element>& V2)
	{
		return V1 ^ V2;
	}


	// Calculates the cross product between two vectors.
	// @param V1 - The first vector.
	// @param V2 - The second vector.
	// @return - A new vector with the cross product between the first and second vectors.
	static inline Vector<Size, Element> CrossProduct(const Vector<Size, Element>& V1, const Vector<Size, Element>& V2)
	{
		return V1 | V2;
	}


	// Gets the value between two vectors based on a percentage value.
	// @param Min - The minimum value of the lerp.
	// @param Max - The maximum value of the lerp.
	// @param Value - The point between the two vectors (between 0 - 1).
	// @return - The vector at the position of the value.
	static inline Vector<Size, Element> Lerp(const Vector<Size, Element>& Min, const Vector<Size, Element>& Max, float Value)
	{
		return ((Max - Min) * Value) + Min;
	}


	// Powers the entire vector a specified amount of times.
	// @param V - The vector to Power.
	// @param Amount - The Power.
	// @return - The vector powered.
	static inline Vector<Size, Element> Power(const Vector<Size, Element>& V, uint Amount)
	{
		return V.Power(Amount);
	}


	// Normalizes the vector.
	// @param V - The vector to normalize.
	// @return - The normalized value.
	static inline Vector<Size, Element> Normalize(Vector<Size, Element> V)
	{
		return V.Normalize();
	}


	// Shorthand way of typing Vector{ 0, 1, 0 }.
	// Vector size must have a Y component.
	static inline Vector<Size, Element> Up()
	{
		ASSERT(Size >= 2, "Vector size is too small");
		Vector<Size, Element> Vec;
		Vec = (Element)0.0f;
		Vec[EAxis::Y] = (Element)1.0f;
		return Vec;
	}


	// Shorthand way of typing Vector{ 0, -1, 0 }.
	// Vector size must have a Y component.
	static inline Vector<Size, Element> Down()
	{
		ASSERT(Size >= 2, "Vector size is too small");
		Vector<Size, Element> Vec;
		Vec = (Element)0.0f;
		Vec[EAxis::Y] = (Element)-1.0f;
		return Vec;
	}


	// Shorthand way of typing Vector{ -1, 0, 0 }.
	// Vector size must have a X component.
	static inline Vector<Size, Element> Left()
	{
		ASSERT(Size >= 1, "Vector size is too small");
		Vector<Size, Element> Vec;
		Vec = (Element)0.0f;
		Vec[EAxis::X] = (Element)-1.0f;
		return Vec;
	}


	// Shorthand way of typing Vector{ 1, 0, 0 }.
	// Vector size must have a X component.
	static inline Vector<Size, Element> Right()
	{
		ASSERT(Size >= 1, "Vector size is too small");
		Vector<Size, Element> Vec;
		Vec = (Element)0.0f;
		Vec[EAxis::X] = (Element)1.0f;
		return Vec;
	}


	// Shorthand way of typing Vector{ 0, 0, 1 }.
	// Vector size must have a Z component.
	static inline Vector<Size, Element> Forward()
	{
		ASSERT(Size >= 3, "Vector size is too small");
		Vector<Size, Element> Vec;
		Vec = (Element)0.0f;
		Vec[EAxis::Z] = (Element)1.0f;
		return Vec;
	}


	// Shorthand way of typing Vector{ 0, 0, -1 }.
	// Vector size must have a Z component.
	static inline Vector<Size, Element> Backward()
	{
		ASSERT(Size >= 3, "Vector size is too small");
		Vector<Size, Element> Vec;
		Vec = (Element)0.0f;
		Vec[EAxis::Z] = (Element)-1.0f;
		return Vec;
	}


	// Returns true if the two imputted vectors are almost equal to eachother based on a range.
	// @param Other - The vector to compare with.
	// @param Threshold - The range in which the other vector can be in.
	// @return - Returns true if the other vector is within range of this vector.
	static inline bool NearlyEqual(const Vector<Size, Element>& A, const Vector<Size, Element>& B, const Element& Threshold)
	{
		return A.NearlyEqual(B, Threshold);
	}


	// Creates a vector with the highest values in each dimension between both inputted vectors.
	// @param V1 - The first vector to use.
	// @param V2 - The second vector to use.
	// @return - A new vector with the highest values between both vector.
	static inline Vector<Size, Element> Max(const Vector<Size, Element>& V1, const Vector<Size, Element>& V2)
	{
		return V1.Max(V2);
	}


	// Gets the highest value in the inputted vector.
	// @param V - The vector to get the highest value component from.
	// @return - The highest value in the vector.
	static inline Element MaxComp(const Vector<Size, Element>& V)
	{
		return V.MaxComp();
	}


	// Creates a vector with the lowest values in each dimension between both inputted vectors.
	// @param V1 - The first vector to use.
	// @param V2 - The second vector to use.
	// @return - A new vector with the lowest values between both vectors.
	static inline Vector<Size, Element> Min(const Vector<Size, Element>& V1, const Vector<Size, Element>& V2)
	{
		return V1.Min(V2);
	}


	// Gets the lowest value in the inputted vector.
	// @param V - The vector to get the lowest value from.
	// @return - The lowest value in the inputted vector.
	static inline Element MinComp(const Vector<Size, Element>& V)
	{
		return V.MinComp();
	}


	// Calculates the distance between two vectors.
	// @param V1 - The first vector.
	// @param V2 - The second vector.
	// @return - Returns a distance between the two vectors.
	static inline float Distance(const Vector<Size, Element>& V1, const Vector<Size, Element>& V2)
	{
		Vector<Size, Element> Delta{ V1 - V2 };
		return TMath::Sqrt(Vector<Size, Element>::DotProduct(Delta, Delta));
	}


	// Calculates the distance between two vectors squared.
	// @param V1 - The first vector.
	// @param V2 - The second vector.
	// @return - Returns a distance between the two vectors squared.
	static inline float DistanceSquared(const Vector<Size, Element>& V1, const Vector<Size, Element>& V2)
	{
		Vector<Size, Element> Delta{ V1 - V2 };
		return Vector<Size, Element>::DotProduct(Delta, Delta);
	}


	// Creates a new vector by selecting using values in two vectors and a bool value (true = V1, false = V2).
	// @param V1 - The first vector type to use.
	// @param V2 - The second vector type to use.
	// @param Control - Determines which vector to use for each axis.
	// @return - Returns a new vector with the selected values.
	static inline Vector<Size, Element> Select(Vector<Size, Element> V1, Vector<Size, Element> V2, Vector<Size, bool> Control)
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
	static inline Vector<4, Element> Merge(Vector<4, Element> V1, Vector<4, Element> V2, EAxis A, EAxis B)
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


// A float Vector with 2 Dimensions.
typedef Vector<2, float> SVector2;

// A float Vector with 3 Dimensions.
typedef Vector<3, float> SVector3;

// A float Vector with 3 Dimensions.
typedef Vector<3, float> SVector;

// A float Vector with 4 Dimensions.
typedef Vector<4, float> SVector4;

// A double Vector with 2 Dimensions.
typedef Vector<2, double> SVector2d;

// A double Vector with 3 Dimensions.
typedef Vector<3, double> SVector3d;

// A double Vector with 4 Dimensions.
typedef Vector<4, double> SVector4d;

// A int Vector with 2 Dimensions.
typedef Vector<2, int> SVector2i;

// A int Vector with 3 Dimensions.
typedef Vector<3, int> SVector3i;

// A int Vector with 4 Dimensions.
typedef Vector<4, int> SVector4i;

// A bool vector with 2 dimensions, used for Vector::Select();
typedef Vector<2, bool> SVector2Control;

// A bool vector with 3 dimensions, used for Vector::Select();
typedef Vector<3, bool> SVectorControl;

// A bool vector with 3 dimensions, used for Vector::Select();
typedef Vector<3, bool> SVector3Control;

// A bool vector with 4 dimensions, used for Vector::Select();
typedef Vector<4, bool> SVector4Control;


template <uint Size, typename Element>
inline static Vector<3, Element> CrossProduct(const Vector<3, Element>& A, const Vector<3, Element>& B)
{
	return A | B;
}


template <uint Size, typename Element>
inline static float DotProduct(const Vector<Size, Element>& A, const Vector<Size, Element>& B)
{
	return A ^ B;
}


template <uint Size, typename Element>
template <uint Size2, typename Element2>
inline Vector<Size, Element> Vector<Size, Element>::operator+(const Vector<Size2, Element2>& V) const
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
inline Vector<Size, Element> Vector<Size, Element>::operator+(const Element& E) const
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
inline Vector<Size, Element> Vector<Size, Element>::operator+=(const Vector<Size2, Element2>& V)
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
inline Vector<Size, Element> Vector<Size, Element>::operator+=(const Element& E)
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
inline Vector<Size, Element> Vector<Size, Element>::operator-(const Vector<Size2, Element2>& V) const
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
inline Vector<Size, Element> Vector<Size, Element>::operator-(const Element& E) const
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
inline Vector<Size, Element> Vector<Size, Element>::operator-() const
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
inline Vector<Size, Element> Vector<Size, Element>::operator-=(const Vector<Size2, Element2>& V)
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
inline Vector<Size, Element> Vector<Size, Element>::operator-=(const Element& E)
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
inline Vector<Size, Element> Vector<Size, Element>::operator*(const Vector<Size2, Element2>& V) const
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
inline Vector<Size, Element> Vector<Size, Element>::operator*(const Element& E) const
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
inline Vector<Size, Element> Vector<Size, Element>::operator*=(const Vector<Size2, Element2>& V)
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
inline Vector<Size, Element> Vector<Size, Element>::operator*=(const Element& E)
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
inline Vector<Size, Element> Vector<Size, Element>::operator/(const Vector<Size2, Element2>& V) const
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
inline Vector<Size, Element> Vector<Size, Element>::operator/(const Element& E) const
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
inline Vector<Size, Element> Vector<Size, Element>::operator/=(const Vector<Size2, Element2>& V)
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
inline Vector<Size, Element> Vector<Size, Element>::operator/=(const Element& E)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] /= E;
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Element>
inline Vector<Size, Element> Vector<Size, Element>::operator++()
{
	for (uint i = 0; i < Size; ++i)
	{
		++Data[i];
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Element>
inline Vector<Size, Element> Vector<Size, Element>::operator--()
{
	for (uint i = 0; i < Size; ++i)
	{
		--Data[i];
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Element>
inline Vector<Size, Element> Vector<Size, Element>::operator=(const Element& E)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] = E;
	}
	CheckNaN();
	return *this;
}


template <uint Size, typename Element>
inline Vector<Size, Element> Vector<Size, Element>::operator|(const Vector<Size, Element>& V) const
{
	Vector<Size, Element> Result{ 0.0f };
	Result[EAxis::X] = (Data[EAxis::Y] * V[EAxis::Z]) - (Data[EAxis::Z] * V[EAxis::Y]);
	Result[EAxis::Y] = (Data[EAxis::Z] * V[EAxis::X]) - (Data[EAxis::X] * V[EAxis::Z]);
	Result[EAxis::Z] = (Data[EAxis::X] * V[EAxis::Y]) - (Data[EAxis::Y] * V[EAxis::X]);
	Result.CheckNaN();
	return Result;
};


template <uint Size, typename Element>
inline Element Vector<Size, Element>::operator^(const Vector<Size, Element>& V) const
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
inline bool Vector<Size, Element>::operator>(const Vector<Size, Element>& V) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] <= V[i])
			return false;
	}
	return true;
}


template <uint Size, typename Element>
inline bool Vector<Size, Element>::operator>(const Element& E) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] <= E)
			return false;
	}
	return true;
}


template <uint Size, typename Element>
inline bool Vector<Size, Element>::operator>=(const Vector<Size, Element>& V) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] < V[i])
			return false;
	}
	return true;
}


template <uint Size, typename Element>
inline bool Vector<Size, Element>::operator>=(const Element& E) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] < E)
			return false;
	}
	return true;
}



template <uint Size, typename Element>
inline bool Vector<Size, Element>::operator<(const Vector<Size, Element>& V) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] >= V[i])
			return false;
	}
	return true;
}


template <uint Size, typename Element>
inline bool Vector<Size, Element>::operator<(const Element& E) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] >= E)
			return false;
	}
	return true;
}


template <uint Size, typename Element>
inline bool Vector<Size, Element>::operator<=(const Vector<Size, Element>& V) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] > V[i])
			return false;
	}
	return true;
}


template <uint Size, typename Element>
inline bool Vector<Size, Element>::operator<=(const Element& E) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] > E)
			return false;
	}
	return true;
}


template <uint Size, typename Element>
inline bool Vector<Size, Element>::operator==(const Vector<Size, Element>& V) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] != V[i])
			return false;
	}
	return true;
}


template <uint Size, typename Element>
inline bool Vector<Size, Element>::operator==(const Element& E) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] != E)
			return false;
	}
	return true;
}


template <uint Size, typename Element>
inline bool Vector<Size, Element>::operator!=(const Vector<Size, Element>& V) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] == V[i])
			return false;
	}
	return true;
}


template <uint Size, typename Element>
inline bool Vector<Size, Element>::operator!=(const Element& E) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] == E)
			return false;
	}
	return true;
}


template <uint Size, typename Element>
inline Element& Vector<Size, Element>::operator[](const uint Component)
{
	return Data[Component];
}


template <uint Size, typename Element>
inline Element Vector<Size, Element>::operator[](const uint Component) const
{
	return Data[Component];
}


template <uint Size, typename Element>
template <typename Type>
inline Vector<Size, Type> Vector<Size, Element>::ToType()
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
inline Vector<Size, Type> Vector<Size, Element>::ToType() const
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
inline Vector<Size, float> Vector<Size, Element>::ToFloat()
{
	return ToType<float>();
}


template <uint Size, typename Element>
inline Vector<Size, int> Vector<Size, Element>::ToInt()
{
	return ToType<int>();
}


template <uint Size, typename Element>
inline Vector<Size, double> Vector<Size, Element>::ToDouble()
{
	return ToType<double>();
}


template <uint Size, typename Element>
inline Vector<Size, float> Vector<Size, Element>::ToFloat() const
{
	return ToType<float>();
}


template <uint Size, typename Element>
inline Vector<Size, int> Vector<Size, Element>::ToInt() const
{
	return ToType<int>();
}


template <uint Size, typename Element>
inline Vector<Size, double> Vector<Size, Element>::ToDouble() const
{
	return ToType<double>();
}


template <uint Size, typename Element>
inline void Vector<Size, Element>::CheckNaN() const
{
	if (ContainsNaN())
	{
		printf("Vector contains NaN");
		*const_cast<Vector<Size, Element>*>(this) = Vector<Size, Element>{ 0.0f };
	}
}


template <uint Size, typename Element>
inline bool Vector<Size, Element>::ContainsNaN() const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (TMath::IsFinite(Data[i]))
		{
			return false;
		}
	}
	return true;
}


template <uint Size, typename Element>
inline std::string Vector<Size, Element>::Print(const bool Print) const
{
	std::string Result;
	std::string Temp;
	for (uint i = 0; i < Size; ++i)
	{
		Temp = (i > 0) ? ", " : "";
		Result += Temp;
		Result += std::to_string(Data[i]);
	}

	if (Print)
		std::cout << Result;

	return Result;
}


template <uint Size, typename Element>
inline Vector<3, Element> Vector<Size, Element>::CrossProduct(const Vector<3, Element>& V) const
{
	return *this | V;
}


template <uint Size, typename Element>
inline float Vector<Size, Element>::DotProduct(const Vector<Size, Element>& V) const
{
	return *this ^ V;
}


template <uint Size, typename Element>
inline Vector<Size, Element> Vector<Size, Element>::Max(const Vector<Size, Element>& V) const
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
inline Element Vector<Size, Element>::MaxComp() const
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
inline Vector<Size, Element> Vector<Size, Element>::Min(const Vector<Size, Element>& V) const
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
inline Element Vector<Size, Element>::MinComp() const
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
inline Vector<Size, Element> Vector<Size, Element>::Normalize() const
{
	return *this / DotProduct(*this);
}


template <uint Size, typename Element>
inline bool Vector<Size, Element>::NearlyEqual(const Vector<Size, Element>& Other, const Element& Threshold) const
{
	for (uint i = 0; i < Size; ++i)
	{
		if (Data[i] <= Other[i] - Threshold || Data[i] >= Other[i] + Threshold) return false;
	}
	return true;
}


template <uint Size, typename Element>
inline bool Vector<Size, Element>::NearlyZero(float Threshold) const
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
inline bool Vector<Size, Element>::IsZero()
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
inline Vector<Size, Element> Vector<Size, Element>::Power(uint Amount)
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
inline float Vector<Size, Element>::SizeSquared() const
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
inline Vector<NewSize, Element> Vector<Size, Element>::Resize(const Element& Value) const
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
inline Element& Vector<Size, Element>::GetComponent(const EAxis& Component)
{
	return Data[Component];
}


template <uint Size, typename Element>
inline Element Vector<Size, Element>::GetComponent(const EAxis& Component) const
{
	return Data[Component];
}


template <uint Size, typename Element>
inline Element& Vector<Size, Element>::X()
{
	ASSERT(Size > 0, "This vector does not have a 'X' component.");
	return Data[EAxis::X];
}


template <uint Size, typename Element>
inline Element Vector<Size, Element>::X() const
{
	ASSERT(Size > 0, "This vector does not have a 'X' component.");
	return Data[EAxis::X];
}


template <uint Size, typename Element>
inline Element& Vector<Size, Element>::Y()
{
	ASSERT(Size > 1, "This vector does not have a 'Y' component.");
	return Data[EAxis::Y];
}


template <uint Size, typename Element>
inline Element Vector<Size, Element>::Y() const
{
	ASSERT(Size > 1, "This vector does not have a 'Y' component.");
	return Data[EAxis::Y];
}


template <uint Size, typename Element>
inline Element& Vector<Size, Element>::Z()
{
	ASSERT(Size > 2, "This vector does not have a 'Z' component.");
	return Data[EAxis::Z];
}


template <uint Size, typename Element>
inline Element Vector<Size, Element>::Z() const
{
	ASSERT(Size > 2, "This vector does not have a 'Z' component.");
	return Data[EAxis::Z];
}


template <uint Size, typename Element>
inline Element& Vector<Size, Element>::W()
{
	ASSERT(Size > 3, "This vector does not have a 'W' component.");
	return Data[EAxis::W];
}


template <uint Size, typename Element>
inline Element Vector<Size, Element>::W() const
{
	ASSERT(Size > 3, "This vector does not have a 'W' component.");
	return Data[EAxis::W];
}


template <uint Size, typename Element>
inline Element Vector<Size, Element>::GetX() const
{
	ASSERT(Size > 0, "This vector does not have a 'X' component.");
	return Data[EAxis::X];
}


template <uint Size, typename Element>
inline Element Vector<Size, Element>::GetY() const
{
	ASSERT(Size > 1, "This vector does not have a 'Y' component.");
	return Data[EAxis::Y];
}


template <uint Size, typename Element>
inline Element Vector<Size, Element>::GetZ() const
{
	ASSERT(Size > 2, "This vector does not have a 'Z' component.");
	return Data[EAxis::Z];
}


template <uint Size, typename Element>
inline Element Vector<Size, Element>::GetW() const
{
	ASSERT(Size > 3, "This vector does not have a 'W' component.");
	return Data[EAxis::W];
}


template <uint Size, typename Element>
inline void Vector<Size, Element>::SetX(const Element& Value)
{
	ASSERT(Size > 0, "This vector does not have a 'X' component.");
	Data[EAxis::X] = Value;
	CheckNaN();
}


template <uint Size, typename Element>
inline void Vector<Size, Element>::SetY(const Element& Value)
{
	ASSERT(Size > 1, "This vector does not have a 'Y' component.");
	Data[EAxis::Y] = Value;
	CheckNaN();
}


template <uint Size, typename Element>
inline void Vector<Size, Element>::SetZ(const Element& Value)
{
	ASSERT(Size > 2, "This vector does not have a 'Z' component.");
	Data[EAxis::Z] = Value;
	CheckNaN();
}


template <uint Size, typename Element>
inline void Vector<Size, Element>::SetW(const Element& Value)
{
	ASSERT(Size > 3, "This vector does not have a 'W' component.");
	Data[EAxis::W] = Value;
	CheckNaN();
}