#include "Button.h"
#include "../../Global/RuntimeContext.h"

#include "../../Core/System/Timer.h"


NAMESPACE_BEGIN(Engine)
Button::Button(const Char* name, Action<> OnClick, Action<> OnPress)
{
	normal		= ColorF_White;
	highlighted = normal * 0.8;
	pressed		= normal * 0.5f;

	transitionFactor = 0.2f;

	borderNormal = ColorF_Black * 0.5f;
	borderHighlighted = ColorF_Red * 0.85f;
	borderWidth = 1;

	this->text	= name;
	textColor	= ColorF_Black * 0.5f;

	position = {};

	this->OnClicked = OnClick;
	this->OnPressed = OnPress;

	current = normal;
	left = right = bottom = top = 0;
}

Void Button::Update(RealType timestep)
{
	auto& input = runtimeContext.input;

	Bool isHover = IsHover(input.GetMousePosition());
	Bool isPressed = input.ButtonPressed(MouseButton::Left);

	auto t = Clamp01(timestep / transitionFactor);
	if (isHover)
		if (isPressed)
		{
			if (OnPressed) OnPressed();
			current = Lerp<const ColorF&>(current, pressed, t);
		}
		else
			current = Lerp<const ColorF&>(current, highlighted, t);
	else
		current = Lerp<const ColorF&>(current, normal, t);

	if (isHover && isPressed && input.ButtonReleased(MouseButton::Left))
		if (OnClicked) OnClicked();


	if (isHover)
	{
		borderCurrent = borderHighlighted;
		borderWidth = 2;
	}
	else
	{
		borderCurrent = borderNormal;
		borderWidth = 1;
	}
}

Void Button::Render(Serface* serface)
{
	if (IsOutOfRange(serface)) return;

	auto Fn = [&](auto x, auto y, const ColorF& color)
	{
		serface->SetPixel(x, y, Blend(color, serface->GetPixel(x, y)));
	};

	// draw background
	for (Int32 y = bottom; y <= top; y++)
		for (Int32 x = left; x <= right; x++)
			Fn(x, y, current);

	// draw border
	{
		for (Int32 y = bottom; y < bottom + borderWidth; y++)
			for (Int32 x = left; x <= right; x++)
				Fn(x, y, borderCurrent);

		for (Int32 y = top - borderWidth + 1; y <= top; y++)
			for (Int32 x = left; x <= right; x++)
				Fn(x, y, borderCurrent);

		for (Int32 x = left; x < left + borderWidth; x++)
			for (Int32 y = bottom + borderWidth; y <= top - borderWidth; y++)
				Fn(x, y, borderCurrent);

		for (Int32 x = right - borderWidth + 1; x <= right; x++)
			for (Int32 y = bottom + borderWidth; y <= top - borderWidth; y++)
				Fn(x, y, borderCurrent);
	}

	// draw text
	AsciiGlyph::Render(serface, Vector2Int{ left + AsciiGlyph::Width, bottom + AsciiGlyph::Height * 0.25f }, text.c_str(), textColor);
}

Bool Button::IsHover(const Vector2Int& mousePosition)
{
	left = position[0];
	right = left + (text.size() + 2) * AsciiGlyph::Width;
	bottom = position[1];
	top = bottom + 1.5f * AsciiGlyph::Height;

	Int32 mx = mousePosition[0];
	Int32 my = mousePosition[1];
	if (mx >= left && mx <= right && my >= bottom && my <= top)
		return true;

	return false;
}

Bool Button::IsOutOfRange(Serface* serface)
{
	// no enough space for display
	if (left < 0 || left >= serface->GetWidth() ||
		right < 0 || right >= serface->GetWidth() ||
		bottom < 0 || bottom >= serface->GetHeight() ||
		top < 0 || top >= serface->GetHeight())
		return true;

	return false;
}
NAMESPACE_END(Engine)