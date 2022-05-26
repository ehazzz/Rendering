#pragma once
/**
*	Predefined Micros
*/


/**
*	Target platform
* 
*	Supported:
*		1. Windows
*/
#if defined(_WIN32) | defined(_WIN64)
#define PLATFORM_WINDOWS
#elif 0
/* Insert other check code here */
#else
#define PLATFORM_UNKNOWN
#error "Current platform is not supported!"
#endif


/**
*	C++ Compiler
*/
#if defined(_MSC_VER)
#define COMPILER_MSVC
#elif 0
/* Insert other check code here */
#else
#define COMPILER_UNKNOWN
#error "Unknown C++ compiler"
#endif


/**
*	C++ Standard
*/
#if defined(COMPILER_MSVC)
	#if _MSVC_LANG < 201703L
	#error "C++ 17 is required"
	#endif
#else
	#if __cplusplus < 201703L
	#error "C++ 17 is required"
	#endif
#endif


/**
*	Export/Import Dynamic Link Library
* 
*	Note:
*		Used by this project:	[Export]
*		Used by other project:	[Import]
*/
#if defined(COMPILER_MSVC)
#define DLL_EXPORT	__declspec(dllexport)
#define DLL_IMPORT	__declspec(dllimport)
#else
#define DLL_EXPORT
#define DLL_IMPORT
#endif

#if !defined(ENGINE_API_IMPORTS)
#define ENGINE_API	DLL_EXPORT
#else
#define ENGINE_API	DLL_IMPORT
#endif



/**
*	The beginning part of namespace
*/
#define NAMESPACE_BEGIN(name)	namespace name{
/**
*	The end part of namespace
*/
#define NAMESPACE_END(name)		}


/**
*	Declare class or struct is not copyable
*/
#define NOT_COPYABLE(Type)	Type(const Type&) = delete; Type& operator=(const Type&) = delete
/**
*	Declare class or struct is not movable
*/
#define NOT_MOVABLE(Type)	Type(Type&&) = delete; Type& operator=(Type&&) = delete


/**
*	Define iterators(sequence container only)
*/
#define USE_ITERATORS(pointer, elementCount)			\
auto begin()		{ return pointer; }					\
auto end()			{ return pointer + elementCount; }	\
auto cbegin() const { return pointer; }					\
auto cend() const	{ return pointer + elementCount; }


/**
*	Calculate shading with linear color space
*/
#define LINEAR_COLOR_SPACE