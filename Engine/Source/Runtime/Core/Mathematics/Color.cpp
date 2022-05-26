#include "Color.h"


NAMESPACE_BEGIN(Engine)
ColorF Blend(const ColorF& source, const ColorF& destination)
{
    return ColorF
    {
        source[0] * source[3] + destination[0] * (1 - source[3]),
        source[1] * source[3] + destination[1] * (1 - source[3]),
        source[2] * source[3] + destination[2] * (1 - source[3]),
        1
    };
}

RealType Luminance(const ColorF& color)
{
    return 0.2126f * color[0] + 0.7152f * color[1] + 0.0722f * color[2];
}

ColorF ToLinear(const ColorF& color)
{
    constexpr RealType p = 2.2f;

    return ColorF
    {
        Power(color[0], p),
        Power(color[1], p),
        Power(color[2], p),
        color[3]
    };
}

ColorF ToSRGB(const ColorF& color)
{
    constexpr RealType p = 1 / 2.2f;

    return ColorF
    {
        Power(color[0], p),
        Power(color[1], p),
        Power(color[2], p),
        color[3]
    };
}

Pixel Encode(const ColorF& color, PixelFormat format)
{
    Byte r = Clamp01(color[0]) * 255;
    Byte g = Clamp01(color[1]) * 255;
    Byte b = Clamp01(color[2]) * 255;
    Byte a = Clamp01(color[3]) * 255;

    switch (format)
    {
    case PixelFormat::R8G8B8A8:
        return r | (g << 8) | (b << 16) | (a << 24);
    case PixelFormat::A8R8G8B8:
        return a | (r << 8) | (g << 16) | (b << 24);
    case PixelFormat::B8G8R8A8:
        return b | (g << 8) | (r << 16) | (a << 24);
    case PixelFormat::A8B8G8R8:
        return a | (b << 8) | (g << 16) | (r << 24);
    default:
        return Pixel();
    }
}

ColorF Decode(Pixel pixel, PixelFormat format)
{
    RealType r, g, b, a;

    switch (format)
    {
    case PixelFormat::R8G8B8A8:
        r = ((pixel >> 0)  & 0xFF) / 255.0f;
        g = ((pixel >> 8)  & 0xFF) / 255.0f;
        b = ((pixel >> 16) & 0xFF) / 255.0f;
        a = ((pixel >> 24) & 0xFF) / 255.0f;
        break;
    case PixelFormat::A8R8G8B8:
        a = ((pixel >> 0)  & 0xFF) / 255.0f;
        r = ((pixel >> 8)  & 0xFF) / 255.0f;
        g = ((pixel >> 16) & 0xFF) / 255.0f;
        b = ((pixel >> 24) & 0xFF) / 255.0f;
        break;
    case PixelFormat::B8G8R8A8:
        b = ((pixel >> 0)  & 0xFF) / 255.0f;
        g = ((pixel >> 8)  & 0xFF) / 255.0f;
        r = ((pixel >> 16) & 0xFF) / 255.0f;
        a = ((pixel >> 24) & 0xFF) / 255.0f;
        break;
    case PixelFormat::A8B8G8R8:
        a = ((pixel >> 0)  & 0xFF) / 255.0f;
        b = ((pixel >> 8)  & 0xFF) / 255.0f;
        g = ((pixel >> 16) & 0xFF) / 255.0f;
        r = ((pixel >> 24) & 0xFF) / 255.0f;
        break;
    default:
        r = g = b = 1.0f;
        a = 1.0f;
        break;
    }

    return ColorF{ r, g, b, a };
}
NAMESPACE_END(Engine)
