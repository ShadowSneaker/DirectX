#pragma once
#include "Transform.h"
#include "../MathStatics.h"

#include <DirectXMath.h>


// A 2D arangement of numbers in rows and columns.
template <uint Columns, uint Rows>
struct SMatrix
{
private:
	/// Properties

	// The stored data in the matrix.
	Vector<Rows> Data[Columns];

public:
	/// Constructors

	// Constructor, Default.
	SMatrix() {};

	// Constructor, Floods the entire matrix with a single float value.
	// @param F - The float value used to flood the matrix.
	SMatrix(float F)
	{
		for (uint i = 0; i < Rows; ++i)
		{
			for (uint j = 0; j < Columns; ++j)
			{
				Data[i][j] = F;
			}
		}
	}

	// Constructor, Initiates the matrix using an array of vectors.
	// The vector size must be the same size as the matrix's columns.
	// The array size must be the same as the matrix's rows.
	// @param V - The array of vectors to assign to this matrix.
	SMatrix(Vector<Rows> V[Columns])
		:Data{ V }
	{}

	// Constructor, Initiates a 4x4 matrix with a location, rotation and scale.
	// Note: This constructor multiplies the matrices: Scale * Rotation * Translate.
	// Note: This constructor assumes the location, rotation and scale is a position.
	// @param Transform - The location, rotation and scale this matrix should be created at.
	SMatrix(STransform Transform)
	{
		ASSERT(Columns == 4 && Rows == 4, "Illigal use of constructor, Is the matrix the correct size?");
		SetTransform(Transform);
	}

	// Constructor, Initiates a 4x4 matrix with a location, rotation and scale.
	// Note: This constructor multiplies the matrices: Scale * Rotation * Translate.
	// Note: This constructor allows use of the W component.
	// @param Location - The location this matrix should be placed at.
	// @param Rotation - The rotation this matrix should be at.
	// @param Scale - The scale this matrix should be at.
	SMatrix(SVector4 Location, SQuaternion Rotation, SVector4 Scale)
	{
		ASSERT(Columns == 4 && Rows == 4, "Illigal use of constructor, Is the matrix the correct size?");
		SetTransform(Location, Rotation, Scale);
	}

	// Constructor, Initiates a 4x4 matrix with a location, rotation and scale.
	// Note: This constructor multiplies the matrices: Scale * Rotation * Translate.
	// Note: This constructor assumes the location, rotation and scale is a position.
	// @param Location - The location this matrix should be placed at.
	// @param Rotation - The rotation this matrix should be at.
	// @param Scale - The scale this matrix should be at.
	SMatrix(SVector Location, SQuaternion Rotation, SVector Scale)
	{
		ASSERT(Columns == 4 && Rows == 4, "Illigal use of constructor, Is the matrix the correct size?");
		SetTransform(Location, Rotation, Scale);
	}

	
	/// Operators

	// Adds each component of this matrix by the same component on another matrix.
	inline SMatrix<Columns, Rows> operator+(const SMatrix<Columns, Rows>& M) const;

	// Adds each component of this matrix by a float.
	inline SMatrix<Columns, Rows> operator+(const float& F) const;

	// Sets this matrix to the result of each component of this matrix added by the same component on another matrix.
	inline SMatrix<Columns, Rows> operator+=(const SMatrix<Columns, Rows>& M);

	// Sets this matrix to the result of a float being added to each component of this matrix.
	inline SMatrix<Columns, Rows> operator+=(const float& F);

	// Subtracts each component of this matrix by the same component on another matrix.
	inline SMatrix<Columns, Rows> operator-(const SMatrix<Columns, Rows>& M) const;

	// Subtracts each component of this matrix by a float.
	inline SMatrix<Columns, Rows> operator-(const float& F) const;

	// Sets this matrix to the result of each component of this matrix subtracted by the same component on another matrix.
	inline SMatrix<Columns, Rows> operator-=(const SMatrix<Columns, Rows>& M);

	// Sets this matrix to the result of a float being subtracted to each component of this matrix.
	inline SMatrix<Columns, Rows> operator-=(const float& F);

	// Returns the result of this matrix being multiplied by another matrix.
	// Matrix multiplication requires that the row of this matrix to equal the columns of the other matrix.
	// The return will be a matarix with the columns of the other matrix and the rows of this matrix.
	template <uint Columns2, uint Rows2>
	inline SMatrix<Columns2, Rows> operator*(const SMatrix<Columns2, Rows2>& M) const;

	// Multiplies each component of this matrix by a float.
	inline SMatrix<Columns, Rows> operator*(const float& F) const;

	// Multiplies a vector of the same size as the Rows of this matrix, to this matrix.
	inline Vector<Rows> operator*(const Vector<Rows>& V) const;

	// Sets this matrix to the result of this matrix being multiplied by another matrix.
	// Matrix multiplication requires that the row of this matrix to equal the columns of the other matrix.
	// The return will be a matarix with the columns of the other matrix and the rows of this matrix.
	template <uint Columns2, uint Rows2>
	inline SMatrix<Columns2, Rows> operator*=(const SMatrix<Columns2, Rows2>& M);

	// Sets this matrix to the result of a float being multiplied to each component of this matrix.
	inline SMatrix<Columns, Rows> operator*=(const float& F);

	// Retrieves a row of the matrix based on an index.
	inline Vector<Columns>& operator[](const uint& Index);

	// Retrieves a row of the matrix based on an index.
	inline Vector<Columns> operator[](const uint& Index) const;

	// Compares if this matrix has the same values as another matrix.
	// All values must be the same to return true.
	inline bool operator==(const SMatrix<Columns, Rows>& M) const;

	// Compares if this matrix does not have the same values as another matrix.
	// All values must be different to return true.
	inline bool operator!=(const SMatrix<Columns, Rows>& M) const;


	/// Conversions

	// Adds up all components of every row then puts it in a vector.
	inline Vector<Rows> ToVector() const;

	/// Functions

	// Prints out all the values of this matrix to the console.
	// Temporary function.
	inline void Print()
	{
		for (uint i = 0; i < Rows; ++i)
		{
			Data[i].Print();
		}
	}

	// Sets this matrix to the identity matrix.
	// Note, the last number in the matrix will always be 1.0f.
	// @param Value - The number that will be assigned along the diagonal.
	inline void SetToIdentity(float Value = 1.0f);

	// Moves the position of the matrix by the inputted amount.
	// Note: If the 'W' component = 0.0f, then the matrix will be set to the location instead of move in the direction.
	// @param Position - The location the matrix should move in.
	// @return - Returns the new matrix after the translation.
	inline SMatrix<4, 4> Translate(const SVector4& Position) const;

	// Moves the position of the matrix by the inputted amount.
	// Note: If the 'W' component = 0.0f, then the matrix will be set to the location instead of move in the direction.
	// @param Position - The location the matrix should move in.
	// @param W - Determines if this should be a position or a movement.
	// @return - Returns the new matrix after the translation.
	inline SMatrix<4, 4> Translate(const SVector& Position, const float& W = 1.0f) const;

	// Moves the position of the matrix by the inputted amount.
	// Note: If the 'W' component = 0.0f, then the matrix will be set to the location instead  of move in the direction.
	// @param X - The X location to move in.
	// @param Y - The Y location to move in.
	// @param Z - The Z location to move in.
	// @param W - Determines if this should be a position or a movement.
	// @return Returns the new matrix after the translation.
	inline SMatrix<4, 4> Translate(const float& X, const float& Y, const float& Z, const float& W = 1.0f) const;

	// Moves the position of this matrix by the inputted amount.
	// Note: If the 'W' component = 0.0f, then the matrix will be set to the location instead of move in the direction.
	// @param Position - The location the matrix should move in.
	// @return - Returns the new matrix after the translation.
	inline SMatrix<4, 4> SetTranslate(const SVector4& Position);

	// Moves the position of this matrix by the inputted amount.
	// Note: If the 'W' component = 0.0f, then the matrix will be set to the location instead of move in the direction.
	// @param Position - The location the matrix should move in.
	// @param W - Determines if this should be a position or a movement.
	// @return - Returns the new matrix after the translation.
	inline SMatrix<4, 4> SetTranslate(const SVector& Position, const float& W = 1.0f);

	// Moves the position of this matrix by the inputted amount.
	// Note: If the 'W' component = 0.0f, then the matrix will be set to the location instead  of move in the direction.
	// @param X - The X location to move in.
	// @param Y - The Y location to move in.
	// @param Z - The Z location to move in.
	// @param W - Determines if this should be a position or a movement.
	// @return Returns the new matrix after the translation.
	inline SMatrix<4, 4> SetTranslate(const float& X, const float& Y, const float& Z, const float& W = 1.0f);

	// Roates the matrix on the pitch axis (X axis) by the inputted angle.
	// @param Angle - How much to rotate along this axis (uses radians).
	// @return - Returns the rotated matrix.
	inline SMatrix<4, 4> RotatePitch(const float& Angle) const;

	// Roates the matrix on the yaw axis (Y axis) by the inputted angle.
	// @param Angle - How much to rotate along this axis (uses radians).
	// @return - Returns the rotated matrix.
	inline SMatrix<4, 4> RotateYaw(const float& Angle) const;

	// Roates the matrix on the roll axis (Z axis) by the inputted angle.
	// @param Angle - How much to rotate along this axis (uses radians).
	// @return - Returns the rotated matrix.
	inline SMatrix<4, 4> RotateRoll(const float& Angle) const;

	// Rotates the matrix on the pitch axis (X axis) by the inputted angle.
	// @param Angle - How much to rotate along this axis (uses radians).
	// @return - Returns the rotated matrix.
	inline SMatrix<4, 4> SetRotatePitch(const float& Angle);

	// Rotates the matrix on the yaw axis (Y axis) by the inputted angle.
	// @param Angle - How much to rotate along this axis (uses radians).
	// @return - Returns the rotated matrix.
	inline SMatrix<4, 4> SetRotateYaw(const float& Angle);

	// Rotates the matrix on the roll axis (Z axis) by the inputted angle.
	// @param Angle - How much to rotate along this axis (uses raidans).
	// @return - Returns the rotated matrix.
	inline SMatrix<4, 4> SetRotateRoll(const float& Angle);

	// Rotates the matrix on all axis by the inputted rotation.
	// @param Rotation - The rotation to apply to this matrix.
	// @return - Returns the rotated matrix.
	inline SMatrix<4, 4> Rotate(const SQuaternion& Rotation) const;

	// Rotates the matrix on all axis by the inputted rotation.
	// @param Rotation - The rotation to apply to this matrix.
	// @return - Returns the rotated matrix.
	inline SMatrix<4, 4> Rotate(const SVector4& Rotation) const;

	// Rotates the matrix on all axis by the inputted rotation.
	// @param Rotation - The rotation to apply to this matrix.
	// @param W - The W component for the rotation.
	// @return - Returns the rotated matrix.
	inline SMatrix<4, 4> Rotate(const SVector& Rotation, const float& W = 1.0f) const;

	// Rotates the matrix on all axis by the inputted rotation.
	// @param Pitch - How much to rotate along the X axis.
	// @param Yaw - How much to rotate along the Y axis.
	// @param Roll - How much to rate along the Z axis.
	// @param W - The w component for the rotation.
	// @return - Returns the rotated matrix.
	inline SMatrix<4, 4> Rotate(const float& Pitch, const float& Yaw, const float& Roll, const float& W = 1.0f) const;

	// Rotates the matrix on all axis by the inputted rotation.
	// @param Rotation - The rotation to apply to this matrix.
	// @return - Returns the rotated matrix.
	inline SMatrix<4, 4> SetRotate(const SQuaternion& Rotation);

	// Rotates the matrix on all axis by the inputted rotation.
	// @param Rotation - The rotation to apply to this matrix.
	// @return - Returns the rotated matrix.
	inline SMatrix<4, 4> SetRotate(const SVector4& Rotation);

	// Rotates the matrix on all axis by the inputted rotation.
	// @param Rotation - The rotation to apply to this matrix.
	// @param W - The W component for the rotation.
	// @return - Returns the rotated matrix.
	inline SMatrix<4, 4> SetRotate(const SVector& Rotation, const float& W = 1.0f);

	// Rotates the matrix on all axis by the inputted rotation.
	// @param Pitch - How much to rotate along the X axis.
	// @param Yaw - How much to rotate along the Y axis.
	// @param Roll - How much to rate along the Z axis.
	// @param W - The w component for the rotation.
	// @return - Returns the rotated matrix.
	inline SMatrix<4, 4> SetRotate(const float& Pitch, const float& Yaw, const float& Roll, const float& W = 1.0f);

	// Scales the matrix on all axis by the inputted scale.
	// @param InScale - The amount this object should be scaled.
	// @return - Returns the scaled matrix.
	inline SMatrix<4, 4> Scale(const SVector4& InScale) const;

	// Scales the matrix on all axis by the inputted scale.
	// @param InScale - The amount this object should be scaled.
	// @param W - The W component for the Scale.
	// @return - Returns the scaled matrix.
	inline SMatrix<4, 4> Scale(const SVector& InScale, const float& W = 1.0f) const;

	// Scales the matrix on all axis by the inputted scale.
	// @param X - How much to scale along the X axis.
	// @param Y - How much to scale along the Y axis.
	// @param Z - How much to scale along the Z axis.
	// @param W - The W compoent for the scale.
	// @return - Returns the scaled matrix.
	inline SMatrix<4, 4> Scale(const float& X, const float& Y, const float& Z, const float& W = 1.0f) const;

	// Scales the matrix on all axis by the inputted scale.
	// @param InScale - The amount this object should be scaled.
	// @return - Returns the scaled matrix.
	inline SMatrix<4, 4> SetScale(const SVector4& InScale);

	// Scales the matrix on all axis by the inputted scale.
	// @param InScale - The amount this object should be scaled.
	// @param W - The W component for the Scale.
	// @return - Returns the scaled matrix.
	inline SMatrix<4, 4> SetScale(const SVector& InScale, const float& W = 1.0f);

	// Scales the matrix on all axis by the inputted scale.
	// @param X - How much to scale along the X axis.
	// @param Y - How much to scale along the Y axis.
	// @param Z - How much to scale along the Z axis.
	// @param W - The W compoent for the scale.
	// @return - Returns the scaled matrix.
	inline SMatrix<4, 4> SetScale(const float& X, const float& Y, const float& Z, const float& W = 1.0f);

	// Scales, rotates and translates the matrix by an inputted transform.
	// Note: Transformation is the the order: Scale > Rotate > Translate.
	// @param InTransform - The location, rotation and scale this matrix should be transformed by.
	// @return - Returns the transformed matrix.
	inline SMatrix<4, 4> Transform(const STransform& InTransform) const;

	// Scales, rotates and translates the matrix by an inputted transform.
	// Note: Transformation is the the order: Scale > Rotate > Translate.
	// @param Location - The amount this matrix should be translated.
	// @param Rotation - The amount this matrix should be rotated.
	// @param InScale - The amount this matrix should be scaled.
	// @return - Returns the transformed matrix.
	inline SMatrix<4, 4> Transform(const SVector4& Location, const SQuaternion& Rotation, const SVector4& InScale) const;

	// Scales, rotates and translates the matrix by an inputted transform.
	// Note: Transformation is the the order: Scale > Rotate > Translate.
	// @param InTransform - The location, rotation and scale this matrix should be transformed by.
	// @return - Returns the transformed matrix.
	inline SMatrix<4, 4> SetTransform(const STransform& InTransform);

	// Scales, rotates and translates the matrix by an inputted transform.
	// Note: Transformation is the the order: Scale > Rotate > Translate.
	// @param Location - The amount this matrix should be translated.
	// @param Rotation - The amount this matrix should be rotated.
	// @param InScale - The amount this matrix should be scaled.
	// @return - Returns the transformed matrix.
	inline SMatrix<4, 4> SetTransform(const SVector4& Location, const SQuaternion& Rotation, const SVector4& InScale);

	// 
	inline SMatrix<4, 4> SetLocation(const SVector4& NewLocation);

	// 
	inline SMatrix<4, 4> SetLocation(const SVector3& NewLocation, const float& W = 1.0f);

	//
	inline SMatrix<4, 4> SetLocation(const float& X, const float& Y, const float& Z, const float& W = 1.0f);

	// Calculates the inverse of this matrix.
	// Note: This does not apply the inverse to this matrix.
	// Note: If the result is an empty matrix then the inputted matrix could not be inversed.
	// @param Inversed - A pass-by-reference to return if this matrix was successfully inverted.
	// @return - The inversed matrix.
	inline SMatrix<Columns, Rows> Inverse(bool& Inversed) const;

	// Calculates the inverse of this matrix.
	// Note: This does not apply the inverse to this matrix.
	// Note: If the result is an empty matrix then the inputted matrix could not be inversed.
	// @return - The inversed matrix.
	inline SMatrix<Columns, Rows> Inverse() const;

	// Calculates the transposes of this matrix.
	// Note: This does not apply the transpose to this matrix.
	// @return - The transposed matrix.
	inline SMatrix<Columns, Rows> Transpose() const;

	// Calculates the determinant of this matrix.
	// Note: This function can only run if the matrix it is being used on is a squared matrix.
	// @param Size - The X and Y size of the matrix.
	inline float Determinant(const uint& Size = Columns) const;

	// Creates a matrix by taking the transpose of the cofactor matrix.
	inline SMatrix<Columns, Rows> Adjoint() const;

	inline SMatrix<4, 4> Merge(SMatrix<4, 4> Mat);

	// Sets a vertical row of vectors in a specified column.
	inline SMatrix<Columns, Rows> SetColumn(const uint& Col, Vector<Rows> Vec);
	
	



	/// Setters


	/// Getters

	// Returns a value at a specific element of the matrix.
	// @param X - The column value to be retrieved.
	// @param Y - The row value to be retrieved.
	// @return The value at the specified columns and row.
	inline float& GetValue(const uint X, const uint Y);

	// Returns a value at a specific element of the matrix.
	// @param X - The column value to be retrieved.
	// @param Y - The row value to be retrieved.
	// @return The value at the specified columns and row.
	inline float GetValue(const uint X, const uint Y) const;

	// Gets a matrix by removing a row and column from this matrix.
	// @param Row - The row to be removed.
	// @param Column - The column to be removed.
	// @param Size - The column and row size of the new matrix.
	// @return - Returns a copy of this matrix after being confactored.
	inline SMatrix<Columns, Rows> GetCofactor(const uint& Row, const uint& Column, const uint& Size) const;

	// 
	inline Vector<Columns> GetScaledAxis(EAxis Axis) const;

	// Returns a column of the matrix based on an axis.
	// @return - The vector retrieved from the inputted column.
	inline Vector<Rows> GetColumn(EAxis Axis) const;


	/// Statics

	static SMatrix<Columns, Rows> Indentity()
	{
		SMatrix<Columns, Rows> Matrix;
		Matrix.SetToIdentity();
		return Matrix;
	}


	static inline SMatrix<4, 4> PersepctiveFovLH(float FovAngleY, float AspectRatio, float NearZ, float FarZ)
	{
		//ASSERT(NearZ > 0.0f && FarZ > 0.0f);
		//ASSERT(!TMath::ScalarNearEqual(FovAngleY, 0.0f, 0.00001f * 2.0f));
		//ASSERT(!TMath::ScalarNearEqual(AspectRatio, 0.0f, 0.00001f));
		//ASSERT(!TMath::ScalarNearEqual(FarZ, NearZ, 0.00001f));

		assert(NearZ > 0.0f && FarZ > 0.0f);
		assert(!TMath::ScalarNearEqual(FovAngleY, 0.0f, 0.00001f * 2.0f));
		assert(!TMath::ScalarNearEqual(AspectRatio, 0.0f, 0.00001f));
		assert(!TMath::ScalarNearEqual(FarZ, NearZ, 0.00001f));

		float SinFOV;
		float CosFOV;
		TMath::ScalarSinCos(&SinFOV, &CosFOV, 0.5f * FovAngleY);

		float Height = CosFOV / SinFOV;
		float Width = Height / AspectRatio;
		float FRange = FarZ / (FarZ - NearZ);

		SMatrix<4, 4> Result{ 0.0f };
		Result[0][0] = Width;
		Result[1][1] = Height;
		Result[2][2] = FRange;
		Result[2][3] = 1.0f;
		Result[3][2] = -FRange * NearZ;

		return Result;
	}


	static inline SMatrix<4, 4> LookAt(SVector4 EyePosition, SVector4 FocusPosition, SVector4 UpDirection)
	{
		SVector4 EyeDirection{ FocusPosition - EyePosition };
		return LookTo(EyePosition, EyeDirection, UpDirection);
	}


	static inline SMatrix<4, 4> LookTo(SVector4 EyePosition, SVector4 EyeDirection, SVector4 UpDirection)
	{
		assert(!(EyeDirection == 0.0f));
		assert(!(UpDirection == 0.0f));


		SVector4 R2{ SVector4::Normalize(EyeDirection) };
		SVector4 R0{ SVector4::CrossProduct(UpDirection, R2) };
		R0 = SVector4::Normalize(R0);

		SVector4 R1{ SVector4::CrossProduct(R2, R0) };
		SVector4 NegEyePos{ -EyePosition };

		SVector4 D0 = SVector4::DotProduct(R0, NegEyePos);
		SVector4 D1 = SVector4::DotProduct(R1, NegEyePos);
		SVector4 D2 = SVector4::DotProduct(R2, NegEyePos);

		//Vector<4, uint> Control{ 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 };
		Vector<4, bool> Control{ false, false, false, true };

		SMatrix<4, 4> Mat;
		//Mat[0] = SVector4::Select(D0, R0, Control);
		//Mat[1] = SVector4::Select(D1, R1, Control);
		//Mat[2] = SVector4::Select(D2, R2, Control);

		Mat.SetColumn(EAxis::X, SVector4::Select(D0, R0, Control));
		Mat.SetColumn(EAxis::Y, SVector4::Select(D1, R1, Control));
		Mat.SetColumn(EAxis::Z, SVector4::Select(D2, R2, Control));
		Mat.SetColumn(EAxis::W, SVector4{ 0.0f, 0.0f, 0.0f, 1.0f });

		//Mat[0] = SVector4{ 1.0f, 0.0f, 0.0f, 0.0f };
		//Mat[1] = SVector4{ 0.0f, 1.0f, 0.0f, 0.0f };
		//Mat[2] = SVector4{ 0.0f, 0.0f, 1.0f, 0.0f };
		//Mat[3] = SVector4{ 0.0f, 0.0f, 5.0f, 1.0f };

		Mat.Merge(Mat);
		return Mat;
	}


	//static SMatrix<4, 4> ToMatrixM(DirectX::XMMATRIX Mat)
	//{
	//	SMatrix<4, 4> Result;
	//	for (uint x = 0; x < Columns; ++x)
	//	{
	//		for (uint y = 0; y < Rows; ++y)
	//		{
	//			Result[x][y] = Mat.m[x][y];
	//		}
	//	}
	//	return Result;
	//}


	static SMatrix<4, 4> ToMatrixR(DirectX::XMMATRIX Mat)
	{
		SMatrix<4, 4> Result;
		for (uint x = 0; x < Columns; ++x)
		{
			for (uint y = 0; y < Rows; ++y)
			{
				Result[x][y] = Mat.r[x][y];
			}
		}
	}

	
};


// A matrix with 1 column and 2 rows.
typedef SMatrix<1, 2> SMatrix1x2;

// A matrix with 2 columns and 1 row.
typedef SMatrix<2, 1> SMatrix2x1;

// A matrix with 1 column and 3 rows.
typedef SMatrix<1, 3> SMatrix1x3;

// A matrix with 3 columns and 1 row.
typedef SMatrix<3, 1> SMatrix3x1;

// A matrix with 1 column and 4 rows.
typedef SMatrix<1, 4> SMatrix1x4;

// A matrix with 4 columns and 1 row.
typedef SMatrix<4, 1> SMatrix4x1;

// A matrix with 2 columns and 2 rows.
typedef SMatrix<2, 2> SMatrix2;

// A matrix with 2 columns and 3 rows.
typedef SMatrix<2, 3> SMatrix2x3;

// A matrix with 3 columns and 2 rows.
typedef SMatrix<3, 2> SMatrix3x2;

// A matrix with 2 columns and 4 rows.
typedef SMatrix<2, 4> SMatrix2x4;

// A matrix with 4 columns and 2 rows.
typedef SMatrix<4, 2> SMatrix4x2;

// A matrix with 3 columns and 3 rows.
typedef SMatrix<3, 3> SMatrix3;

// A matrix with 3 columns and 4 rows.
typedef SMatrix<3, 4> SMatrix3x4;

// A matrix with 4 columns and 3 rows.
typedef SMatrix<4, 3> SMatrix4x3;

// A matrix with 4 columns and 4 rows.
typedef SMatrix<4, 4> SMatrix4;


template <uint Columns, uint Rows>
inline SMatrix<Columns, Rows> SMatrix<Columns, Rows>::operator+(const SMatrix<Columns, Rows>& M) const
{
	SMatrix<Columns, Rows> Result;
	for (uint i = 0; i < Rows; ++i)
	{
		Result[i] = Data[i] + M[i];
	}
	return Result;
}


template <uint Columns, uint Rows>
inline SMatrix<Columns, Rows> SMatrix<Columns, Rows>::operator+(const float& F) const
{
	SMatrix<Columns, Rows> Result;
	for (uint i = 0; i < Rows; ++i)
	{
		Result[i] = Data[i] + F;
	}
	return Result;
}


template <uint Columns, uint Rows>
inline SMatrix<Columns, Rows> SMatrix<Columns, Rows>::operator+=(const SMatrix<Columns, Rows>& M)
{
	for (uint i = 0; i < Rows; ++i)
	{
		Data[i] += M[i];
	}
	return *this;
}


template <uint Columns, uint Rows>
inline SMatrix<Columns, Rows> SMatrix<Columns, Rows>::operator+=(const float& F)
{
	for (uint i = 0; i < Rows; ++i)
	{
		Data[i] += F;
	}
	return *this;
}


template <uint Columns, uint Rows>
inline SMatrix<Columns, Rows> SMatrix<Columns, Rows>::operator-(const SMatrix<Columns, Rows>& M) const
{
	SMatrix<Columns, Rows> Result;
	for (uint i = 0; i < Rows; ++i)
	{
		Result[i] = Data[i] - M[i];
	}
	return Result;
}


template <uint Columns, uint Rows>
inline SMatrix<Columns, Rows> SMatrix<Columns, Rows>::operator-(const float& F) const
{
	SMatrix<Columns, Rows> Result;
	for (uint i = 0; i < Rows; ++i)
	{
		Result[i] = Data[i] - F;
	}
	return Result;
}


template <uint Columns, uint Rows>
inline SMatrix<Columns, Rows> SMatrix<Columns, Rows>::operator-=(const SMatrix<Columns, Rows>& M)
{
	for (uint i = 0; i < Rows; ++i)
	{
		Data[i] -= M[i];
	}
	return *this;
}


template <uint Columns, uint Rows>
inline SMatrix<Columns, Rows> SMatrix<Columns, Rows>::operator-=(const float& F)
{
	for (uint i = 0; i < Rows; ++i)
	{
		Data[i] -= F;
	}
	return *this;
}


template <uint Columns, uint Rows>
template <uint Columns2, uint Rows2>
inline SMatrix<Columns2, Rows> SMatrix<Columns, Rows>::operator*(const SMatrix<Columns2, Rows2>& M) const
{
	ASSERT(Columns == Rows2, "These matrices can not be multiplied together.");
	SMatrix<Columns2, Rows> Result{ 0.0f };
	for (uint y = 0; y < Rows; ++y)
	{
		for (uint x = 0; x < Columns2; ++x)
		{
			for (uint i = 0; i < Columns; ++i)
			{
				Result[y][x] += (Data[y][i] * M[i][x]);
			}
		}
	}
	return Result;
}


template <uint Columns, uint Rows>
inline SMatrix<Columns, Rows> SMatrix<Columns, Rows>::operator*(const float& F) const
{
	SMatrix<Columns, Rows> Result;
	for (uint i = 0; i < Rows; ++i)
	{
		Result[i] = Data[i] * F;
	}
	return Result;
}


template <uint Columns, uint Rows>
inline Vector<Rows> SMatrix<Columns, Rows>::operator*(const Vector<Rows>& V) const
{
	return (*this * SMatrix<1, Rows>::ToMatrix(V)).ToVector();
}


template <uint Columns, uint Rows>
template <uint Columns2, uint Rows2>
inline SMatrix<Columns2, Rows> SMatrix<Columns, Rows>::operator*=(const SMatrix<Columns2, Rows2>& M)
{
	*this = *this * M;
	return *this;
}


template <uint Columns, uint Rows>
inline SMatrix<Columns, Rows> SMatrix<Columns, Rows>::operator*=(const float& F)
{
	for (uint i = 0; i < Rows; ++i)
	{
		Data[i] *= F;
	}
	return *this;
}


template <uint Columns, uint Rows>
inline Vector<Columns>& SMatrix<Columns, Rows>::operator[](const uint& Index)
{
	return Data[Index];
}


template <uint Columns, uint Rows>
inline Vector<Columns> SMatrix<Columns, Rows>::operator[](const uint& Index) const
{
	return Data[Index];
}


template <uint Columns, uint Rows>
inline bool SMatrix<Columns, Rows>::operator==(const SMatrix<Columns, Rows>& M) const
{
	for (uint i = 0; i < Rows; ++i)
	{
		if (Data[i] != M[i]) return false;
	}
	return true;
}


template <uint Columns, uint Rows>
inline bool SMatrix<Columns, Rows>::operator!=(const SMatrix<Columns, Rows>& M) const
{
	for (uint i = 0; i < Rows; ++i)
	{
		if (Data[i] == M[i]) return false;
	}
	return true;
}


template <uint Columns, uint Rows>
inline Vector<Rows> SMatrix< Columns, Rows>::ToVector() const
{
	Vector<Rows> Result{ 0.0f };
	for (uint y = 0; y < Rows; ++y)
	{
		for (uint x = 0; x < Columns; ++x)
		{
			Result[y] += Data[y][x];
		}
	}
	return Result;
}


template <uint Columns, uint Rows>
inline void SMatrix<Columns, Rows>::SetToIdentity(float Value)
{
	ASSERT(Columns == 4 && Rows == 4, "The matrix must be a 4x4 matrix in order to be translated.");
	for (uint y = 0; y < Rows; ++y)
	{
		for (uint x = 0; x < Columns; ++x)
		{
			Data[y][x] = ((x == y) * Value);
		}
	}
	Data[Columns - 1][Rows - 1] = 1.0f;
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::Translate(const SVector4& Location) const
{
	ASSERT(Columns == 4 && Rows == 4, "The matrix must be a 4x4 matrix in order to be translated.");
	SMatrix<4, 4> Matrix;
	Matrix.SetToIdentity();

	for (uint i = 0; i < 4; ++i)
	{
		Matrix[i][W] = Location[i];
	}
	return *this * Matrix;
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::Translate(const SVector& Location, const float& W) const
{
	return Translate(SVector4{ Location, W });
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::Translate(const float& X, const float& Y, const float& Z, const float& W) const
{
	return Translate(SVector4{ X, Y, Z, W });
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetTranslate(const SVector4& Location)
{
	ASSERT(Columns == 4 && Rows == 4, "The matrix must be a 4x4 matrix in order to be translated.");
	SMatrix<4, 4> Matrix;

	for (uint i = 0; i < 4; ++i)
	{
		Matrix[i][W] = Location[i];
	}
	*this *= Matrix;
	return *this;
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetTranslate(const SVector& Location, const float& W)
{
	return SetTranslate(SVector4{ Location, W });
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetTranslate(const float& X, const float& Y, const float& Z, const float& W)
{
	return SetTranslate(SVector4{ X, Y, Z, W });
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::RotatePitch(const float& Angle) const
{
	ASSERT(Columns == 4 && Rows == 4, "The matrix must be a 4x4 matrix in order to be rotated.");
	// Rotates along the X axis.

	SMatrix<4, 4> Result;
	Result.SetToIdentity();

	Result[1][1] = TMath::Cos(Angle);
	Result[1][2] = TMath::Sin(Angle);
	Result[2][1] = -TMath::Sin(Angle);
	Result[2][2] = TMath::Cos(Angle);

	return Result;
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::RotateYaw(const float& Angle) const
{
	ASSERT(Columns == 4 && Rows == 4, "The matrix must be a 4x4 matrix in order to be rotated.");
	// Rotates along the Y axis.

	SMatrix<4, 4> Result;
	Result.SetToIdentity();

	Result[0][0] = TMath::Cos(Angle);
	Result[0][2] = -TMath::Sin(Angle);
	Result[2][0] = TMath::Sin(Angle);
	Result[2][2] = TMath::Cos(Angle);

	return Result;
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::RotateRoll(const float& Angle) const
{
	ASSERT(Columns == 4 && Rows == 4, "The matrix must be a 4x4 matrix in order to be rotated.");
	// Rotate along the Z axis.

	SMatrix<4, 4> Result;
	Result.SetToIdentity();

	Result[0][0] = TMath::Cos(Angle);
	Result[0][1] = TMath::Sin(Angle);
	Result[1][0] = -TMath::Sin(Angle);
	Result[1][1] = TMath::Cos(Angle);

	return Result;
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetRotatePitch(const float& Angle)
{
	*this *= RotatePitch(Angle);
	return *this;
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetRotateYaw(const float& Angle)
{
	*this *= RotateYaw(Angle);
	return *this;
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetRotateRoll(const float& Angle)
{
	*this *= RotateRoll(Angle);
	return *this;
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::Rotate(const SQuaternion& Rotation) const
{
	ASSERT(Columns == 4 && Rows == 4, "The matrix must be a 4x4 matrix in order to be rotated.");

	SMatrix<4, 4> Result;

	Result = RotatePitch(Rotation.X);
	Result *= RotateYaw(Rotation.Y);
	Result *= RotateRoll(Rotation.Z);

	return Result;
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::Rotate(const SVector4& Rotation) const
{
	return Rotate(SQuaternion{ Rotation });
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::Rotate(const SVector& Rotation, const float& W) const
{
	return Rotate(SQuaternion{ Rotation, W });
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::Rotate(const float& X, const float& Y, const float& Z, const float& W) const
{
	return Rotate(SQuaternion{ X, Y, Z, W });
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetRotate(const SQuaternion& Rotation)
{
	ASSERT(Columns == 4 && Rows == 4, "The matrix must be a 4x4 matrix in order to be rotated.");

	SetRotatePitch(Rotation.X);
	SetRotateYaw(Rotation.Y);
	SetRotateRoll(Rotation.Z);

	return *this;
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetRotate(const SVector4& Rotation)
{
	return SetRotate(SQuaternion{ Rotation });
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetRotate(const SVector& Rotation, const float& W)
{
	return SetRotate(SQuaternion{ Rotation, W });
}

template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetRotate(const float& X, const float& Y, const float& Z, const float& W)
{
	return SetRotate(SQuaternion{ X, Y, Z, W });
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::Scale(const SVector4& InScale) const
{
	ASSERT(Columns == 4 && Rows == 4, "The matrix must be a 4x4 matrix in order to be scaled.");

	SMatrix<4, 4> Result{ 0.0f };
	for (uint i = 0; i < 4; ++i)
	{
		Result[i][i] = InScale[i];
	}

	return *this * Result;
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::Scale(const SVector& InScale, const float& W) const
{
	return Scale(SVector4{ InScale, W });
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::Scale(const float& X, const float& Y, const float& Z, const float& W) const
{
	return Scale(SVector4{ X, Y, Z, W });
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetScale(const SVector4& InScale)
{
	ASSERT(Columns == 4 && Rows == 4, "The matrix must be a 4x4 matrix in order to be scaled.");

	SMatrix<4, 4> Result{ 0.0f };
	for (uint i = 0; i < 4; ++i)
	{
		Result[i][i] = InScale[i];
	}

	*this *= Result;
	return *this;
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetScale(const SVector& InScale, const float& W)
{
	return SetScale(SVector4{ InScale, W });
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetScale(const float& X, const float& Y, const float& Z, const float& W)
{
	return SetScale(SVector4{ X, Y, Z, W });
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::Transform(const STransform& InTransform) const
{
	return Scale(InTransform.Scale) * Rotate(InTransform.Rotation) * Translate(InTransform.Location);
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::Transform(const SVector4& Location, const SQuaternion& Rotation, const SVector4& InScale) const
{
	return Transform(STransform{ Location, Rotation, InScale });
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetTransform(const STransform& InTransform)
{
	SetScale(InTransform.Scale);
	SetRotate(InTransform.Rotation);
	SetTranslate(InTransform.Location);
	return *this;
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetTransform(const SVector4& Location, const SQuaternion& Rotation, const SVector4& InScale)
{
	return SetTransform(STransform{ Location, Rotation, InScale });
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetLocation(const SVector4& NewLocation)
{
	for (uint i = 0; i < Rows; ++i)
	{
		Data[EAxis::W][i] = NewLocation[i];
	}
	return *this;
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetLocation(const SVector3& NewLocation, const float& W)
{
	return SetLocation(SVector4{ NewLocation[X], NewLocation[Y], NewLocation[Z], W });
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::SetLocation(const float& X, const float& Y, const float& Z, const float& W)
{
	return SetLocation(SVector4{ X, Y, Z, W });
}


template <uint Columns, uint Rows>
inline SMatrix<Columns, Rows> SMatrix<Columns, Rows>::Inverse(bool& Inversed) const
{
	ASSERT(Columns == Rows, "This matrix size must be the same in both dimensions to calculate the inverse.");
	float Det{ Determinant() };
	if (Det == 0.0f)
	{
		Inversed = false;
		return 0.0f;
	}

	SMatrix<Columns, Rows> Result;
	SMatrix<Columns, Rows> Adj{ Adjoint() };
	for (uint x = 0; x < Columns; ++x)
	{
		for (uint y = 0; y < Rows; ++y)
		{
			Result[x][y] = Adj[x][y] / Det;
		}
	}
	Inversed = true;
	return Result;
}


template <uint Columns, uint Rows>
inline SMatrix<Columns, Rows> SMatrix<Columns, Rows>::Inverse() const
{
	ASSERT(Columns == Rows, "This matrix size must be the same in both dimensions to calculate the inverse.");
	float Det{ Determinant() };
	if (Det == 0.0f)
	{
		return 0.0f;
	}

	SMatrix<Columns, Rows> Result;
	SMatrix<Columns, Rows> Adj{ Adjoint() };
	for (uint x = 0; x < Columns; ++x)
	{
		for (uint y = 0; y < Rows; ++y)
		{
			Result[x][y] = Adj[x][y] / Det;
		}
	}
	return Result;
}


template <uint Columns, uint Rows>
inline SMatrix<Columns, Rows> SMatrix<Columns, Rows>::Transpose() const
{
	// TODO
}


template <uint Columns, uint Rows>
inline float SMatrix<Columns, Rows>::Determinant(const uint& Size) const
{
	ASSERT(Columns == Rows, "This matrix must be the same in both dimensions to calculate the determinate.");
	float Result{ 0.0f };

	if (Size == 1) return Data[0][0];

	SMatrix<Columns, Rows> Matrix;
	int8 Sign{ 1 };

	for (uint i = 0; i < Size; ++i)
	{
		Matrix = GetCofactor(0, i, Size);
		Result += Sign * Data[0][i] * Matrix.Determinant(Size - 1);
		Sign = -Sign;
	}
	return Result;
}


template <uint Columns, uint Rows>
inline SMatrix<Columns, Rows> SMatrix<Columns, Rows>::Adjoint() const
{
	ASSERT(Columns == Rows, "This matrix size must be the same in both dimensions to calculate the adjoint.");
	SMatrix<Columns, Rows> Result;

	if (Columns == 1)
	{
		Result[0][0] = 1.0f;
		return Result;
	}

	int8 Sign{ 1 };
	SMatrix<Columns, Rows> Matrix;
	for (uint x = 0; x < Columns; ++x)
	{
		for (uint y = 0; y < Rows; ++y)
		{
			Matrix = GetCofactor(x, y, Columns);
			Sign = ((x + y) % 2 == 0) ? 1 : -1;
			Result[y][x] = Sign * Matrix.Determinant(Columns - 1);
		}
	}
	return Result;
}


template <uint Columns, uint Rows>
inline SMatrix<4, 4> SMatrix<Columns, Rows>::Merge(SMatrix<4, 4> Mat)
{
	SMatrix4 P;
	P[0] = SVector4::Merge(Mat[0], Mat[2], X, Y);
	P[1] = SVector4::Merge(Mat[1], Mat[3], X, Y);
	P[2] = SVector4::Merge(Mat[0], Mat[2], Z, W);
	P[3] = SVector4::Merge(Mat[1], Mat[3], Z, W);


	SMatrix4 MT;
	MT[0] = SVector4::Merge(P[0], P[1], X, Y);
	MT[1] = SVector4::Merge(P[0], P[1], Z, W);
	MT[2] = SVector4::Merge(P[2], P[3], X, Y);
	MT[3] = SVector4::Merge(P[2], P[3], Z, W);
	return MT;
}


template <uint Columns, uint Rows>
inline SMatrix<Columns, Rows> SMatrix<Columns, Rows>::SetColumn(const uint& Col, Vector<Rows> Vec)
{
	for (uint i = 0; i < Rows; ++i)
	{
		Data[i][Col] = Vec[i];
	}
	return *this;
}


template <uint Columns, uint Rows>
inline float& SMatrix<Columns, Rows>::GetValue(const uint X, const uint Y)
{
	return Data[Y][X];
}


template <uint Columns, uint Rows>
inline float SMatrix<Columns, Rows>::GetValue(const uint X, const uint Y) const
{
	return Data[Y][X];
}


template <uint Columns, uint Rows>
inline SMatrix<Columns, Rows> SMatrix<Columns, Rows>::GetCofactor(const uint& Row, const uint& Column, const uint& Size) const
{
	int8 i{ 0 };
	int8 j{ 0 };

	SMatrix<Columns, Rows> Result;

	for (uint y = 0; y < Size; ++y)
	{
		for (uint x = 0; x < Size; ++x)
		{
			if (y != Row && x != Column)
			{
				Result[i][j++] = Data[y][x];
				if (j == Size - 1)
				{
					j = 0;
					++i;
				}
			}
		}
	}
	return Result;
}


template <uint Columns, uint Rows>
inline Vector<Columns> SMatrix<Columns, Rows>::GetScaledAxis(EAxis Axis) const
{
	// TODO:
	// Is this correct?
	return Data[Axis];
}


template <uint Columns, uint Rows>
inline Vector<Rows> SMatrix<Columns, Rows>::GetColumn(EAxis Axis) const
{
	Vector<Rows> Result;
	for (uint i = 0; i < Rows; ++i)
	{
		Result[i] = Data[i][Axis];
	}
	return Result;
}