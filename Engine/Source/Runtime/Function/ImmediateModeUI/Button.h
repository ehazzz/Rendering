#pragma once
#include "../../Core/Mathematics/Color.h"

#include "AsciiGlyph.h"

#include <string>


NAMESPACE_BEGIN(Engine)
using String = std::string;


class ENGINE_API Button {
public:
	ColorF normal;
	ColorF highlighted;
	ColorF pressed;
	RealType transitionFactor;

	ColorF borderNormal;
	ColorF borderHighlighted;
	Int32 borderWidth;

	String text;
	ColorF textColor;

	Vector2Int position; //

	Action<> OnClicked;
	Action<> OnPressed;

	Button(const Char* name = "Button", Action<> OnClick = nullptr, Action<> OnPress = nullptr);

	Void Update(RealType timestep);
	Void Render(Serface* serface);
private:
	Bool IsHover(const Vector2Int& mousePosition);
	Bool IsOutOfRange(Serface* serface);
private:
	ColorF current; // background color
	ColorF borderCurrent; // border color

	Int32 left, right, bottom, top;
};
NAMESPACE_END(Engine)