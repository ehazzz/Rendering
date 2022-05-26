#pragma once
#include "Type.h"


NAMESPACE_BEGIN(Engine)
#define ENABLE_BIT_MASK_OPERATORS(EnumClass)			\
template<> struct EnableBitMaskOperators<EnumClass>		\
{														\
	static constexpr Bool Value = true;					\
}


template<typename EnumClass>
struct EnableBitMaskOperators
{
	static constexpr Bool Value = false;
};


using EnumClassExplicitCastType = Int32;


template<typename EnumClass>
inline constexpr typename EnableIf<EnableBitMaskOperators<EnumClass>::Value, EnumClass>::Type
operator&(EnumClass leftHandSide, EnumClass rightHandSide)
{
	return EnumClass(Cast<EnumClassExplicitCastType>(leftHandSide) & Cast<EnumClassExplicitCastType>(rightHandSide));
}


template<typename EnumClass>
inline constexpr typename EnableIf<EnableBitMaskOperators<EnumClass>::Value, EnumClass>::Type
operator|(EnumClass leftHandSide, EnumClass rightHandSide)
{
	return EnumClass(Cast<EnumClassExplicitCastType>(leftHandSide) | Cast<EnumClassExplicitCastType>(rightHandSide));
}


template<typename EnumClass>
inline constexpr typename EnableIf<EnableBitMaskOperators<EnumClass>::Value, EnumClass>::Type&
operator&=(EnumClass& leftHandSide, EnumClass rightHandSide)
{
	leftHandSide = leftHandSide & rightHandSide;
	return leftHandSide;
}


template<typename EnumClass>
inline constexpr typename EnableIf<EnableBitMaskOperators<EnumClass>::Value, EnumClass>::Type&
operator|=(EnumClass& leftHandSide, EnumClass rightHandSide)
{
	leftHandSide = leftHandSide | rightHandSide;
	return leftHandSide;
}
NAMESPACE_END(Engine)