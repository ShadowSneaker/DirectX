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
	Element Data[Size]{Element(0.0f)};

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

	// Constructor, Initializes a Vector3 using a Vector2 and a Value.
	Vector<Size, Element>(Vector<2, Element> InV, Element InZ)
	{
		ASSERT(Size == 3, "Error: Illigal use of constructor. Is the vector the correct size?");
		Data[0] = InV[0];
		Data[1] = InV[1];
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

	// Constructor, Initializes a Vector4 using a Vector3 and a Value.
	Vector<Size, Element>(Vector<3, Element> InV, Element InW)
	{
		ASSERT(Size == 4, "Error: Illigal use of constructor. Is the vector the correct size?");
		Data[0] = InV[0];
		Data[1] = InV[1];
		Data[2] = InV[2];
		Data[3] = InW;
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


	/// Statics

	// Returns the dot product between two vectors.
	static inline float DotProduct(const Vector<Size, Element>& A, const Vector<Size, Element>& B)
	{
		return A ^ B;
	}


	// Returns the cross product between two vector3s.
	static inline Vector<Size, Element> CrossProduct(const Vector<Size, Element>& A, const Vector<Size, Element>& B)
	{
		return A | B;
	}


	// Gets the value between two vectors based on a percentage value.
	static inline Vector<Size, Element> Lerp(const Vector<Size, Element>& Min, const Vector<Size, Element>& Max, float Value)
	{
		return ((Max - Min) * Value) + Min;
	}


	// Powers the entire vector a specified amount of times.
	// @param V - The vector to Power.
	// @param Amount - The Power.
	static inline Vector<Size, Element> Power(const Vector<Size, Element>& V, uint Amount)
	{
		return V.Power(Amount);
	}


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
	static inline Vector<Size, Element> Max(const Vector<Size, Element>& A, const Vector<Size, Element>& B)
	{
		return A.Max(B);
	}


	// Gets the highest value in the inputted vector.
	static inline Element MaxComp(const Vector<Size, Element>& V)
	{
		return V.MaxComp();
	}


	// Creates a vector with the lowest values in each dimension between both inputted vectors.
	static inline Vector<Size, Element> Min(const Vector<Size, Element>& A, const Vector<Size, Element>& B)
	{
		return A.Min(B);
	}


	// Gets the lowest value in the inputted vector.
	static inline Element MinComp(const Vector<Size, Element>& V)
	{
		return V.MinComp();
	}


	// Calculates the distance between two vectors.
	static inline float Distance(const Vector<Size, Element>& V1, const Vector<Size, Element>& V2)
	{
		float Result{ 0.0f };
		for (uint i = 0; i < Size; ++i)
		{
			Element Temp{ (V1[i] + V2[i]) };
			Result += float(Temp * Temp);
		}

		return Result;
	}


	static inline Vector<Size, Element> Select(Vector<Size, Element> V1, Vector<Size, Element> V2, Vector<Size, bool> Control)
	{
		Vector<Size, Element> Result;
		for (uint i = 0; i < Size; ++i)
		{
			//Result[i] = V1[i] & ~Control[i] | V2[i] & Control[0]; 
			Result[i] = ((Control[i]) ? V1[i] : V2[i]);
		}
		return Result;
	}


	static inline Vector<4, Element> Merge(Vector<4, Element> V1, Vector<4, Element> V2, EAxis A, EAxis B)
	{
		return Vector<4, Element>
		{
			V1[A],
			V2[A],
			V1[B],
			V2[B]
		};
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
	return *this;
}


template <uint Size, typename Element>
inline Vector<Size, Element> Vector<Size, Element>::operator+=(const Element& E)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] += E;
	}
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
	return *this;
}


template <uint Size, typename Element>
inline Vector<Size, Element> Vector<Size, Element>::operator-=(const Element& E)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] -= E;
	}
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
	return *this;
}


template <uint Size, typename Element>
inline Vector<Size, Element> Vector<Size, Element>::operator*=(const Element& E)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] *= E;
	}
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
	return *this;
}


template <uint Size, typename Element>
inline Vector<Size, Element> Vector<Size, Element>::operator/=(const Element& E)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] /= E;
	}
	return *this;
}


template <uint Size, typename Element>
inline Vector<Size, Element> Vector<Size, Element>::operator++()
{
	for (uint i = 0; i < Size; ++i)
	{
		++Data[i];
	}
	return *this;
}


template <uint Size, typename Element>
inline Vector<Size, Element> Vector<Size, Element>::operator--()
{
	for (uint i = 0; i < Size; ++i)
	{
		--Data[i];
	}
	return *this;
}


template <uint Size, typename Element>
inline Vector<Size, Element> Vector<Size, Element>::operator=(const Element& E)
{
	for (uint i = 0; i < Size; ++i)
	{
		Data[i] = E;
	}
	return *this;
}


template <uint Size, typename Element>
inline Vector<Size, Element> Vector<Size, Element>::operator|(const Vector<Size, Element>& V) const
{
	Vector<Size, Element> Result{ 0.0f };
	Result[EAxis::X] = (Data[EAxis::Y] * V[EAxis::Z]) - (Data[EAxis::Z] * V[EAxis::Y]);
	Result[EAxis::Y] = (Data[EAxis::Z] * V[EAxis::X]) - (Data[EAxis::X] * V[EAxis::Z]);
	Result[EAxis::Z] = (Data[EAxis::X] * V[EAxis::Y]) - (Data[EAxis::Y] * V[EAxis::X]);

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


//template <uint Size, typename Element>
//inline DirectX::XMVECTOR Vector<Size, Element>::ToXMVector() const
//{
//	DirectX::XMVECTOR Result;
//	for (uint i = 0; i < Size; ++i)
//	{
//		Result.vector4_f32[i] = Data[i];
//	}
//	return Result;
//}


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