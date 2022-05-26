#pragma once
/**
*	Base Types Redefined
*/
#include "Micro.h"


NAMESPACE_BEGIN(Engine)
using Byte		= unsigned char;
using SByte		= char;

using Int8		= SByte;
using Int16		= short;
using Int32		= int;
using Int64		= long long;

using UInt8		= Byte;
using UInt16	= unsigned short;
using UInt32	= unsigned int;
using UInt64	= unsigned long long;

using Float32	= float;
using Float64	= double;

using Char		= SByte;
using WChar		= wchar_t;

using Bool		= bool;

using Void		= void;
using Handle	= Void*;

using SizeType	= UInt64;
using Dimension = SizeType;
using RealType	= Float32;


/**
*	Cast argument to other type
*/
template<typename ReturnType, typename InputType> inline constexpr ReturnType Cast(InputType argument) { return static_cast<ReturnType>(argument); }
/**
*	Apply offset to pointer and cast it to other pointer type
*/
template<typename AnyPointer, typename AnyType> inline constexpr AnyPointer Cast(AnyType* pointer, SizeType offset = 0) { return reinterpret_cast<AnyPointer>(reinterpret_cast<Byte*>(pointer) + offset); }


/**
*	Swap the value of a and b
*/
template<typename T> inline Void Swap(T* a, T* b) { T temporary = *a; *a = *b; *b = temporary; }


template<typename TypeName> struct RemoveReferenceT { using Type = TypeName; };
/**
*	Remove lvalue reference
*/
template<typename TypeName> struct RemoveReferenceT<TypeName&> { using Type = TypeName; };
/**
*	Remove rvalue reference
*/
template<typename TypeName> struct RemoveReferenceT<TypeName&&> { using Type = TypeName; };
/**
*	Remove lvalue or rvalue reference
*/
template<typename Type>
using RemoveReference = typename RemoveReferenceT<Type>::Type;


/**
*	Forward argument as movable
*/
template<typename Type> inline constexpr RemoveReference<Type>&& Move(Type&& argument) { return static_cast<RemoveReference<Type>&&>(argument); }


/**
*	Function pointer(with return)
*/
template<typename ReturnType, typename ...InputTypes>
using Function = ReturnType(*)(InputTypes ...);
/**
*	Function pointer(no return)
*/
template<typename ...InputTypes>
using Action = Function<Void, InputTypes ...>;


/**
*	No member "Type" if !Predicate
*/
template<Bool Predicate, typename TypeName> struct EnableIf { using Type = TypeName; };
template<typename TypeName> struct EnableIf<false, TypeName> {};


/**
*	Condition Predication
* 
*	Note:
*		Type is False if !Predicate otherwise True
*/
template<Bool Predicate, typename False, typename True> struct Condition { using Type = False; };
template<typename False, typename True> struct Condition<true, False, True> { using Type = True; };


/**
*	Confirm if two or more types are same
*/
template<typename ...Types> struct TypesAreSame;
template<typename Type> struct TypesAreSame<Type, Type> { static constexpr Bool Value = true; };
template<typename First, typename Second> struct TypesAreSame<First, Second> { static constexpr Bool Value = false; };
template<typename First, typename Second, typename ...Types> struct TypesAreSame<First, Second, Types ...> { static constexpr Bool Value = TypesAreSame<First, Second>::Value & TypesAreSame<Second, Types ...>::Value; };


/**
*	Confirm if input types include expected type
*/
template<typename ExpectType, typename ...InputTypes> struct TypesContain;
template<typename ExpectType, typename Type> struct TypesContain<ExpectType, Type> { static constexpr Bool Value = TypesAreSame<ExpectType, Type>::Value; };
template<typename ExpectType, typename First, typename ...InputTypes> struct TypesContain<ExpectType, First, InputTypes ...> { static constexpr Bool Value = TypesAreSame<ExpectType, First>::Value | TypesAreSame<ExpectType, InputTypes ...>::Value; };


/**
*	Confirm if Type is signed integer
*/
template<typename Type> struct IsSignedInteger { static constexpr Bool Value = TypesContain<Type, Int8, Int16, Int32, Int64>::Value; };
/**
*	Confirm if Type is unsigned integer
*/
template<typename Type> struct IsUnsignedInteger { static constexpr Bool Value = TypesContain<Type, UInt8, UInt16, UInt32, UInt64, SizeType, Dimension>::Value; };
/**
*	Confirm if Type is integer
*/
template<typename Type> struct IsInteger { static constexpr Bool Value = IsSignedInteger<Type>::Value | IsUnsignedInteger<Type>::Value; };


/**
*	Confirm if Type is float point
*/
template<typename Type> struct IsFloatPoint { static constexpr Bool Value = TypesContain<Type, Float32, Float64, RealType>::Value; };


template<typename ...Arguments> struct ArgumentPackHelper
{
	/**
	*	Element count of argument pack
	*/
	static constexpr SizeType Count = sizeof...(Arguments);

	/**
	*	Copy the value from argument pack recursively to pointer point to memory
	*/
	template<typename Type, typename First, typename ...Inputs>
	static Void Copy(Type* pointer, First value, Inputs ...inputs)
	{
		constexpr SizeType elementCount = ArgumentPackHelper<Inputs ...>::Count;
		pointer[Count - (elementCount + 1)] = static_cast<Type>(value);

		if constexpr (elementCount > 0) 
			Copy(pointer, inputs...);
	}
};
NAMESPACE_END(Engine)