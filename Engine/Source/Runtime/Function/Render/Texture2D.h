#pragma once
#include "../../Core/Mathematics/Color.h"
#include "../../Core/IO/File.h"


NAMESPACE_BEGIN(Engine)
/*Coordinate System(Texture Space)
*		y axis
*		^[0, 1]
*		|
*		|
*		|
*		|
*		|
*		+------------>x axis
*		[0, 0]		[1, 0]
*/


enum class FilterMode {
	Point,
	Bilinear, // unused
	Trilinear, // unused
};


class ENGINE_API Texture2D {
public:
	NOT_COPYABLE(Texture2D);


	static const Texture2D Black;
	static const Texture2D White;


	Texture2D(Pixel* buffer = nullptr, UInt32 width = 0, UInt32 height = 0);
	~Texture2D();


	Void FlipVertical();
	Void FlipHorizontal();
	ColorF Sample(const Vector2F& uv, FilterMode mode = FilterMode::Point) const;


	Pixel* GetBuffer();
	UInt32 GetWidth();
	UInt32 GetHeight();

	static Texture2D* Load(const Path& path);
private:
	/**
	*	Pixel format is R8G8B8A8
	*/
	Pixel* buffer;
	UInt32 width;
	UInt32 height;
};
NAMESPACE_END(Engine)