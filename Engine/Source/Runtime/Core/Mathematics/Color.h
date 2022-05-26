#pragma once
#include "Vector.h"


NAMESPACE_BEGIN(Engine)
/**
*	Channels are red, green, blue and alpha(float point type, a channel uses 4 bytes)
*
*	Representation:
*		|<-		 16 bytes	  ->|
*		[red][green][blue][alpha]
*/
using ColorF = Vector4F;
/**
*	Channels are red, green, blue and alpha(byte type, a channel uses 1 byte)
*
*	Representation:
*		|<-		 4 bytes	  ->|
*		[red][green][blue][alpha]
*/
//using ColorB = Vector4<Byte>;

/**
*	Use 4 byte to store a pixel
*/
using Pixel = UInt32;


enum class PixelFormat {
	Unknown,
	R8G8B8A8,
	A8R8G8B8,
	B8G8R8A8,
	A8B8G8R8,
};


/*
enum class ColorSpace
{
	Linear,
	Gamma22
};
*/


inline const ColorF ColorF_Black	= ColorF{ 0, 0, 0, 1 };
inline const ColorF ColorF_White	= ColorF{ 1, 1, 1, 1 };
inline const ColorF ColorF_Red		= ColorF{ 1, 0, 0, 1 };
inline const ColorF ColorF_Green	= ColorF{ 0, 1, 0, 1 };
inline const ColorF ColorF_Blue		= ColorF{ 0, 0, 1, 1 };
inline const ColorF ColorF_Yellow	= ColorF{ 1, 1, 0, 1 };
inline const ColorF ColorF_Cyan		= ColorF{ 0, 1, 1, 1 };
inline const ColorF ColorF_Magenta	= ColorF{ 1, 0, 1, 1 };


/**
*	Blend the color of source and destination by the alpha channel of source
*/
ENGINE_API ColorF Blend(const ColorF& source, const ColorF& destination);
/**
*	Calculate the luminace of color
*/
ENGINE_API RealType Luminance(const ColorF& color);
/**
*	Convert gamma to linear color space
*/
ENGINE_API ColorF ToLinear(const ColorF& color);
/**
*	Convert linear to gamma color space
*/
ENGINE_API ColorF ToSRGB(const ColorF& color);
/**
*	Encode ColorF to Pixel
*/
ENGINE_API Pixel Encode(const ColorF& color, PixelFormat format);
/**
*	Decode Pixel to ColorF
*/
ENGINE_API ColorF Decode(Pixel pixel, PixelFormat format);
NAMESPACE_END(Engine)