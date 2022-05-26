#pragma once
#include "Math.h"
#include "../System/Memory.h"


NAMESPACE_BEGIN(Engine)
template<Dimension, typename T> struct Vector;

template<typename T> using Vector2 = Vector<2, T>;
template<typename T> using Vector3 = Vector<3, T>;
template<typename T> using Vector4 = Vector<4, T>;

using Vector2Int = Vector2<Int32>;
using Vector3Int = Vector3<Int32>;
using Vector4Int = Vector4<Int32>;

using Vector2F = Vector2<RealType>;
using Vector3F = Vector3<RealType>;
using Vector4F = Vector4<RealType>;


/**
*	Vector Conversion
*/
template<typename T> Vector2<T> ToVector2(const Vector3<T>& vector3);
template<typename T> Vector2<T> ToVector2(const Vector4<T>& vector4);
template<typename T> Vector3<T> ToVector3(const Vector2<T>& vector2, T z = T());
template<typename T> Vector3<T> ToVector3(const Vector4<T>& vector4);
template<typename T> Vector4<T> ToVector4(const Vector2<T>& vector2, T z = T(), T w = T());
template<typename T> Vector4<T> ToVector4(const Vector3<T>& vector3, T w = T());

/**
*	Cross Product
*
*	Note:
*		The dimension of Vector must be 2 or 3
*/
template<Dimension D, typename T> auto Cross(const Vector<D, T>& a, const Vector<D, T>& b);
/**
*	Dot Product
*/
template<Dimension D, typename T> T Dot(const Vector<D, T>& a, const Vector<D, T>& b);
/**
*	Calculate the length of Vector
*/
template<Dimension D, typename T> T Magnitude(const Vector<D, T>& vector);
/**
*	Normalized vector(unit vector)
*/
template<Dimension D, typename T> Vector<D, T> Normalize(const Vector<D, T>& vector);


template<Dimension D, typename T> struct Vector
{
	static_assert((D >= 2) && (D <= 4), "The Dimension of Vector must be 2, 3 or 4");
	//static_assert(IsInteger<T>::Value | IsFloatPoint<T>::Value, "T must be integer or float point");


	USE_ITERATORS(components, D);


	T components[D];


	/**
	*	Dont anything for efficiency
	*/
	Vector();
	/**
	*	The element count of argument pack must be euqal with the Dimension of Vector
	*/
	template<typename ...Arguments>
	explicit Vector(Arguments ...arguments);
	Vector(const Vector<D, T>& other);


	Vector<D, T>& operator=(const Vector<D, T>& other);
	T& operator[](Int32 index);
	const T& operator[](Int32 index) const;


	Vector<D, T> operator+() const;
	Vector<D, T> operator-() const;

	Vector<D, T> operator+(const Vector<D, T>& other) const;
	Vector<D, T> operator-(const Vector<D, T>& other) const;
	Vector<D, T> operator*(const Vector<D, T>& other) const;
	Vector<D, T> operator/(const Vector<D, T>& other) const;

	Vector<D, T>& operator+=(const Vector<D, T>& other);
	Vector<D, T>& operator-=(const Vector<D, T>& other);
	Vector<D, T>& operator*=(const Vector<D, T>& other);
	Vector<D, T>& operator/=(const Vector<D, T>& other);

	Vector<D, T> operator+(T scalar) const;
	Vector<D, T> operator-(T scalar) const;
	Vector<D, T> operator*(T scalar) const;
	Vector<D, T> operator/(T scalar) const;

	Vector<D, T>& operator+=(T scalar);
	Vector<D, T>& operator-=(T scalar);
	Vector<D, T>& operator*=(T scalar);
	Vector<D, T>& operator/=(T scalar);
};


#pragma region /* Constant */
template<typename T> inline const auto Vector2_Zero		= Vector2<T>{  0,  0 };
template<typename T> inline const auto Vector2_One		= Vector2<T>{  1,  1 };
template<typename T> inline const auto Vector2_Left		= Vector2<T>{ -1,  0 };
template<typename T> inline const auto Vector2_Right	= Vector2<T>{  1,  0 };
template<typename T> inline const auto Vector2_Down		= Vector2<T>{  0, -1 };
template<typename T> inline const auto Vector2_Up		= Vector2<T>{  0,  1 };

template<typename T> inline const auto Vector3_Zero		= Vector3<T>{  0,  0,  0 };
template<typename T> inline const auto Vector3_One		= Vector3<T>{  1,  1,  1 };
template<typename T> inline const auto Vector3_Left		= Vector3<T>{ -1,  0,  0 };
template<typename T> inline const auto Vector3_Right	= Vector3<T>{  1,  0,  0 };
template<typename T> inline const auto Vector3_Down		= Vector3<T>{  0, -1,  0 };
template<typename T> inline const auto Vector3_Up		= Vector3<T>{  0,  1,  0 };
template<typename T> inline const auto Vector3_Back		= Vector3<T>{  0,  0, -1 };
template<typename T> inline const auto Vector3_Forward	= Vector3<T>{  0,  0,  1 };

template<typename T> inline const auto Vector4_Zero		= Vector4<T>{  0,  0,  0,  0 };
template<typename T> inline const auto Vector4_One		= Vector4<T>{  1,  1,  1,  1 };


inline const auto Vector2Int_Zero	= Vector2_Zero<Int32>;
inline const auto Vector2Int_One	= Vector2_One<Int32>;
inline const auto Vector2Int_Left	= Vector2_Left<Int32>;
inline const auto Vector2Int_Right	= Vector2_Right<Int32>;
inline const auto Vector2Int_Down	= Vector2_Down<Int32>;
inline const auto Vector2Int_Up		= Vector2_Up<Int32>;

inline const auto Vector3Int_Zero	= Vector3_Zero<Int32>;
inline const auto Vector3Int_One	= Vector3_One<Int32>;
inline const auto Vector3Int_Left	= Vector3_Left<Int32>;
inline const auto Vector3Int_Right	= Vector3_Right<Int32>;
inline const auto Vector3Int_Down	= Vector3_Down<Int32>;
inline const auto Vector3Int_Up		= Vector3_Up<Int32>;
inline const auto Vector3Int_Back	= Vector3_Back<Int32>;
inline const auto Vector3Int_Forward = Vector3_Forward<Int32>;

inline const auto Vector4Int_Zero	= Vector4_Zero<Int32>;
inline const auto Vector4Int_One	= Vector4_One<Int32>;


inline const auto Vector2F_Zero		= Vector2_Zero<RealType>;
inline const auto Vector2F_One		= Vector2_One<RealType>;
inline const auto Vector2F_Left		= Vector2_Left<RealType>;
inline const auto Vector2F_Right	= Vector2_Right<RealType>;
inline const auto Vector2F_Down		= Vector2_Down<RealType>;
inline const auto Vector2F_Up		= Vector2_Up<RealType>;

inline const auto Vector3F_Zero		= Vector3_Zero<RealType>;
inline const auto Vector3F_One		= Vector3_One<RealType>;
inline const auto Vector3F_Left		= Vector3_Left<RealType>;
inline const auto Vector3F_Right	= Vector3_Right<RealType>;
inline const auto Vector3F_Down		= Vector3_Down<RealType>;
inline const auto Vector3F_Up		= Vector3_Up<RealType>;
inline const auto Vector3F_Back		= Vector3_Back<RealType>;
inline const auto Vector3F_Forward	= Vector3_Forward<RealType>;

inline const auto Vector4F_Zero		= Vector4_Zero<RealType>;
inline const auto Vector4F_One		= Vector4_One<RealType>;
#pragma endregion


#pragma region /* Generic Operations */
template<typename T>
inline Vector2<T> ToVector2(const Vector3<T>& vector3)
{
	return Vector2<T>(vector3[0], vector3[1]);
}

template<typename T>
inline Vector2<T> ToVector2(const Vector4<T>& vector4)
{
	return Vector2<T>(vector4[0], vector4[1]);
}

template<typename T>
inline Vector3<T> ToVector3(const Vector2<T>& vector2, T z)
{
	return Vector3<T>(vector2[0], vector2[1], z);
}

template<typename T>
inline Vector3<T> ToVector3(const Vector4<T>& vector4)
{
	return Vector3<T>(vector4[0], vector4[1], vector4[2]);
}

template<typename T>
inline Vector4<T> ToVector4(const Vector2<T>& vector2, T z, T w)
{
	return Vector4<T>(vector2[0], vector2[1], z, w);
}

template<typename T>
inline Vector4<T> ToVector4(const Vector3<T>& vector3, T w)
{
	return Vector4<T>(vector3[0], vector3[1], vector3[2], w);
}

template<Dimension D, typename T>
inline auto Cross(const Vector<D, T>& a, const Vector<D, T>& b)
{
	if constexpr (D == 2)
		return a[0] * b[1] - a[1] * b[0];

	if constexpr (D == 3)
		return Vector3<T>
		{
			a[1] * b[2] - a[2] * b[1],
			a[2] * b[0] - a[0] * b[2],
			a[0] * b[1] - a[1] * b[0]
		};
}

template<Dimension D, typename T>
inline T Dot(const Vector<D, T>& a, const Vector<D, T>& b)
{
	T sum = T();
	for (SizeType index = 0; index < D; index++)
		sum += a[index] * b[index];

	return sum;
}

template<Dimension D, typename T>
inline T Magnitude(const Vector<D, T>& vector)
{
	return SquareRoot(Dot(vector, vector));
}

template<Dimension D, typename T>
inline Vector<D, T> Normalize(const Vector<D, T>& vector)
{
	return vector / Magnitude(vector);
}
#pragma endregion


#pragma region /* Implementation(Vector) */
template<Dimension D, typename T>
inline Vector<D, T>::Vector()
{

}

template<Dimension D, typename T>
template<typename ...Arguments>
inline Vector<D, T>::Vector(Arguments ...arguments)
{
	//static_assert(ArgumentPackHelper<Arguments ...>::Count == D, "Unexpected condition");

	ArgumentPackHelper<Arguments ...>::Copy(components, arguments...);
}

template<Dimension D, typename T>
inline Vector<D, T>::Vector(const Vector<D, T>& other)
{
	Memory::Copy(other.components, components, D);
}

template<Dimension D, typename T>
inline Vector<D, T>& Vector<D, T>::operator=(const Vector<D, T>& other)
{
	Memory::Copy(other.components, components, D);
	return *this;
}

template<Dimension D, typename T>
inline T& Vector<D, T>::operator[](Int32 index)
{
	return components[index];
}

template<Dimension D, typename T>
inline const T& Vector<D, T>::operator[](Int32 index) const
{
	return components[index];
}

template<Dimension D, typename T>
inline Vector<D, T> Vector<D, T>::operator+() const
{
	return *this;
}

template<Dimension D, typename T>
inline Vector<D, T> Vector<D, T>::operator-() const
{
	Vector<D, T> result;
	for (SizeType index = 0; index < D; index++)
		result[index] = -components[index];

	return result;
}

template<Dimension D, typename T>
inline Vector<D, T> Vector<D, T>::operator+(const Vector<D, T>& other) const
{
	Vector<D, T> result;
	for (SizeType index = 0; index < D; index++)
		result[index] = components[index] + other[index];

	return result;
}

template<Dimension D, typename T>
inline Vector<D, T> Vector<D, T>::operator-(const Vector<D, T>& other) const
{
	Vector<D, T> result;
	for (SizeType index = 0; index < D; index++)
		result[index] = components[index] - other[index];

	return result;
}

template<Dimension D, typename T>
inline Vector<D, T> Vector<D, T>::operator*(const Vector<D, T>& other) const
{
	Vector<D, T> result;
	for (SizeType index = 0; index < D; index++)
		result[index] = components[index] * other[index];

	return result;
}

template<Dimension D, typename T>
inline Vector<D, T> Vector<D, T>::operator/(const Vector<D, T>& other) const
{
	Vector<D, T> result;
	for (SizeType index = 0; index < D; index++)
		result[index] = components[index] / other[index];

	return result;
}

template<Dimension D, typename T>
inline Vector<D, T>& Vector<D, T>::operator+=(const Vector<D, T>& other)
{
	for (SizeType index = 0; index < D; index++)
		components[index] += other[index];

	return *this;
}

template<Dimension D, typename T>
inline Vector<D, T>& Vector<D, T>::operator-=(const Vector<D, T>& other)
{
	for (SizeType index = 0; index < D; index++)
		components[index] -= other[index];

	return *this;
}

template<Dimension D, typename T>
inline Vector<D, T>& Vector<D, T>::operator*=(const Vector<D, T>& other)
{
	for (SizeType index = 0; index < D; index++)
		components[index] *= other[index];

	return *this;
}

template<Dimension D, typename T>
inline Vector<D, T>& Vector<D, T>::operator/=(const Vector<D, T>& other)
{
	for (SizeType index = 0; index < D; index++)
		components[index] /= other[index];

	return *this;
}

template<Dimension D, typename T>
inline Vector<D, T> Vector<D, T>::operator+(T scalar) const
{
	Vector<D, T> result;
	for (SizeType index = 0; index < D; index++)
		result[index] = components[index] + scalar;

	return result;
}

template<Dimension D, typename T>
inline Vector<D, T> Vector<D, T>::operator-(T scalar) const
{
	Vector<D, T> result;
	for (SizeType index = 0; index < D; index++)
		result[index] = components[index] - scalar;

	return result;
}

template<Dimension D, typename T>
inline Vector<D, T> Vector<D, T>::operator*(T scalar) const
{
	Vector<D, T> result;
	for (SizeType index = 0; index < D; index++)
		result[index] = components[index] * scalar;

	return result;
}

template<Dimension D, typename T>
inline Vector<D, T> Vector<D, T>::operator/(T scalar) const
{
	Vector<D, T> result;
	for (SizeType index = 0; index < D; index++)
		result[index] = components[index] / scalar;

	return result;
}

template<Dimension D, typename T>
inline Vector<D, T>& Vector<D, T>::operator+=(T scalar)
{
	for (SizeType index = 0; index < D; index++)
		components[index] += scalar;

	return *this;
}

template<Dimension D, typename T>
inline Vector<D, T>& Vector<D, T>::operator-=(T scalar)
{
	for (SizeType index = 0; index < D; index++)
		components[index] -= scalar;

	return *this;
}

template<Dimension D, typename T>
inline Vector<D, T>& Vector<D, T>::operator*=(T scalar)
{
	for (SizeType index = 0; index < D; index++)
		components[index] *= scalar;

	return *this;
}

template<Dimension D, typename T>
inline Vector<D, T>& Vector<D, T>::operator/=(T scalar)
{
	for (SizeType index = 0; index < D; index++)
		components[index] /= scalar;

	return *this;
}
#pragma endregion
NAMESPACE_END(Engine)