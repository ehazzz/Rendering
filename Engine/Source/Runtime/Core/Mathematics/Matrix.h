#pragma once
#include "Vector.h"


NAMESPACE_BEGIN(Engine)
template<Dimension, typename T> struct Matrix;

template<typename T> using Matrix2 = Matrix<2, T>;
template<typename T> using Matrix3 = Matrix<3, T>;
template<typename T> using Matrix4 = Matrix<4, T>;


template<Dimension D, typename T> Vector<D, T> Mul(const Matrix<D, T>& matrix, const Vector<D, T>& columnMajorVector);
template<Dimension D, typename T> Matrix<D, T> Mul(const Matrix<D, T>& A, const Matrix<D, T>& B);
template<Dimension D, typename T> Matrix<D, T> Transpose(const Matrix<D, T>& matrix);


template<Dimension D, typename T> struct Matrix
{
	static_assert((D >= 2) && (D <= 4), "The Dimension of Matrix must be 2, 3 or 4");
	static_assert(IsInteger<T>::Value | IsFloatPoint<T>::Value, "T must be integer or float point");


	USE_ITERATORS(rows, D);


	/**
	*	Element count
	*/
	static constexpr SizeType Count = D * D;


	union
	{
		T components[Count];
		Vector<D, T> rows[D];
	};


	/**
	*	Dont anything for efficiency
	*/
	Matrix();
	/**
	*	The element count of argument pack must be euqal with the Count of Matrix
	*/
	template<typename ...Arguments>
	explicit Matrix(Arguments ...arguments);
	Matrix(const Matrix<D, T>& other);


	const Vector<D, T>& GetRow(Int32 rowIndex) const;
	Vector<D, T> GetColumn(Int32 columnIndex) const;
	Void SetRow(Int32 rowIndex, const Vector<D, T>& vector);
	Void SetColumn(Int32 columnIndex, const Vector<D, T>& vector);


	Matrix<D, T>& operator=(const Matrix<D, T>& other);
	Vector<D, T>& operator[](Int32 index);
	const Vector<D, T>& operator[](Int32 index) const;


	Vector<D, T> operator*(const Vector<D, T>& vector);
	Matrix<D, T> operator*(const Matrix<D, T>& other);
};


#pragma region /* Generic Operations */
template<Dimension D, typename T>
inline Vector<D, T> Mul(const Matrix<D, T>& matrix, const Vector<D, T>& columnMajorVector)
{
	Vector<D, T> result;
	for (SizeType index = 0; index < D; index++) 
		result[index] = Dot(matrix[index], columnMajorVector);

	return result;
}

template<Dimension D, typename T>
inline Matrix<D, T> Mul(const Matrix<D, T>& A, const Matrix<D, T>& B)
{
	Matrix<D, T> result;
	for (SizeType columnIndex = 0; columnIndex < D; columnIndex++)
	{
		auto column = B.GetColumn(columnIndex);
		for (SizeType rowIndex = 0; rowIndex < D; rowIndex++)
			result[rowIndex][columnIndex] = Dot(A.GetRow(rowIndex), column);
	}

	return result;
}

template<Dimension D, typename T>
inline Matrix<D, T> Transpose(const Matrix<D, T>& matrix)
{
	Matrix<D, T> result;
	for (SizeType rowIndex = 0; rowIndex < D; rowIndex++)
		for (SizeType columnIndex = 0; columnIndex < D; columnIndex++)
			result[columnIndex][rowIndex] = matrix[rowIndex][columnIndex];

	return result;
}
#pragma endregion


#pragma region /* Implementation */
template<Dimension D, typename T>
inline Matrix<D, T>::Matrix()
{

}

template<Dimension D, typename T>
template<typename ...Arguments>
inline Matrix<D, T>::Matrix(Arguments ...args)
{
	static_assert(ArgumentPackHelper<Arguments ...>::Count == Count, "Unexpected condition");

	ArgumentPackHelper<Arguments ...>::Copy(components, args...);
}

template<Dimension D, typename T>
inline Matrix<D, T>::Matrix(const Matrix<D, T>& other)
{
	Memory::Copy(other.components, components, Count);
}

template<Dimension D, typename T>
inline const Vector<D, T>& Matrix<D, T>::GetRow(Int32 rowIndex) const
{
	return rows[rowIndex];
}

template<Dimension D, typename T>
inline Vector<D, T> Matrix<D, T>::GetColumn(Int32 columnIndex) const
{
	Vector<D, T> result;
	for (SizeType index = 0; index < D; index++)
		result[index] = rows[index][columnIndex];

	return result;
}

template<Dimension D, typename T>
inline Void Matrix<D, T>::SetRow(Int32 rowIndex, const Vector<D, T>& vector)
{
	rows[rowIndex] = vector;
}

template<Dimension D, typename T>
inline Void Matrix<D, T>::SetColumn(Int32 columnIndex, const Vector<D, T>& vector)
{
	for (SizeType index = 0; index < D; index++)
		rows[index][columnIndex] = vector[index];
}

template<Dimension D, typename T>
inline Matrix<D, T>& Matrix<D, T>::operator=(const Matrix<D, T>& other)
{
	Memory::Copy(other.components, components, Count);
	return *this;
}

template<Dimension D, typename T>
inline Vector<D, T>& Matrix<D, T>::operator[](Int32 index)
{
	return rows[index];
}

template<Dimension D, typename T>
inline const Vector<D, T>& Matrix<D, T>::operator[](Int32 index) const
{
	return rows[index];
}

template<Dimension D, typename T>
inline Vector<D, T> Matrix<D, T>::operator*(const Vector<D, T>& vector)
{
	return Mul(*this, vector);
}

template<Dimension D, typename T>
inline Matrix<D, T> Matrix<D, T>::operator*(const Matrix<D, T>& other)
{
	return Mul(*this, other);
}
#pragma endregion
NAMESPACE_END(Engine)