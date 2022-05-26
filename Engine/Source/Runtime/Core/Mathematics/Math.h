#pragma once
#include "../Base/Type.h"


NAMESPACE_BEGIN(Engine)
/**
*	The well-known 3.14159..
*/
template<typename T> inline constexpr T Pi = 3.14159265358979323846;
template<typename T> inline constexpr T TwoPi = Pi<T> * 2;
template<typename T> inline constexpr T HalfPi = Pi<T> / 2;

/**
*	Degrees to radians conversion constant
*/
template<typename T> constexpr T DegreesToRadians = Pi<T> / 180;
/**
*	Radians to degrees conversion constant
*/
template<typename T> constexpr T RadiansToDegrees = 180 / Pi<T>;


/**
*	Return the absolute value of value
*/
template<typename T> constexpr T Absolute(T value);
/**
*	Clamp the value between a range defined by the given minimum and maximum
*/
template<typename First, typename Second, typename Third> constexpr auto Clamp(First value, Second minimum, Third maximum);
/**
*	Linearly interpolate between [from, to] by t
*/
template<typename TypeA, typename TypeB> constexpr auto Lerp(TypeA from, TypeA to, TypeB t);
/**
*	Return the largest of two or more
*/
template<typename First, typename Second, typename ...Types> constexpr auto Maximum(First a, Second b, Types ...arguments);
/**
*	Return the smallest of two or more
*/
template<typename First, typename Second, typename ...Types> constexpr auto Minimum(First a, Second b, Types ...arguments);

/**
*	Clame the value between [0, 1]
*/
constexpr RealType Clamp01(RealType value);
/**
*	Linearly interpolate between [0, 1]
*/
constexpr RealType Lerp01(RealType t);


/**
*	Return the value raised to power p
*/
ENGINE_API RealType Power(RealType value, RealType p);
/**
*	Return the square root of value
*/
ENGINE_API RealType SquareRoot(RealType value);

/**
*	Return the sine of radians in radians
*/
ENGINE_API RealType Sine(RealType radians);
/**
*	Return the cosine of radians in radians
*/
ENGINE_API RealType Cosine(RealType radians);
/**
*	Return the tangent of radians in radians
*/
ENGINE_API RealType Tangent(RealType radians);


#pragma region /* Implementation */
template<typename T>
inline constexpr T Absolute(T value)
{
	return value < 0 ? -value : value;
}

template<typename First, typename Second, typename Third>
inline constexpr auto Clamp(First value, Second minimum, Third maximum)
{
	return value < minimum ? minimum : value > maximum ? maximum : value;
}

template<typename TypeA, typename TypeB>
inline constexpr auto Lerp(TypeA from, TypeA to, TypeB t)
{
	return from + (to - from) * t;
}

template<typename First, typename Second, typename ...Types>
inline constexpr auto Maximum(First a, Second b, Types ...arguments)
{
	auto result = a > b ? a : b;

	if constexpr (ArgumentPackHelper<Types ...>::Count > 0)
		return Maximum(result, arguments...);

	return result;
}

template<typename First, typename Second, typename ...Types> 
inline constexpr auto Minimum(First a, Second b, Types ...arguments)
{
	auto result = a < b ? a : b;

	if constexpr (ArgumentPackHelper<Types ...>::Count > 0)
		return Minimum(result, arguments...);

	return result;
}

inline constexpr RealType Clamp01(RealType value) 
{ 
	return Clamp<RealType, RealType, RealType>(value, 0, 1);
}

inline constexpr RealType Lerp01(RealType t)
{
	return Lerp<RealType, RealType>(0, 1, t);
}
#pragma endregion
NAMESPACE_END(Engine)