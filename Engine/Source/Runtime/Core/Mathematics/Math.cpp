#include "Math.h"

#include <cmath>


NAMESPACE_BEGIN(Engine)
RealType Power(RealType value, RealType p)
{
	return std::powf(value, p);
}

RealType SquareRoot(RealType value)
{
	return std::sqrtf(value);
}

RealType Sine(RealType radians)
{
	return std::sinf(radians);
}

RealType Cosine(RealType radians)
{
	return std::cosf(radians);
}

RealType Tangent(RealType radians)
{
	return std::tanf(radians);
}
NAMESPACE_END(Engine)