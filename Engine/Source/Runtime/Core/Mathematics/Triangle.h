#pragma once
#include "Vector.h"


NAMESPACE_BEGIN(Engine)
struct Triangle
{
	Vector2F a, b, c;


	Triangle(const Vector2F& a, const Vector2F& b, const Vector2F& c)
		: a(a), b(b), c(c)
	{

	}


	/**
	*	Calculate the barycentric coordinates of triangle about point p
	* 
	*	Note:
	*		Vector3F[0] - alpha
	*		Vector3F[1] - beta
	* 		Vector3F[2] - gamma
	*/
	Vector3F BarycentricCoordinates(const Vector2F& p) const
	{
		RealType areaA	= Cross(c - b, p - b);
		RealType areaB	= Cross(a - c, p - c);
		RealType areaC	= Cross(b - a, p - a);
		RealType sum	= areaA + areaB + areaC;

		RealType alpha	= areaA / sum;
		RealType beta	= areaB / sum;
		RealType gamma	= 1 - (alpha + beta);

		return Vector3F{ alpha, beta, gamma };
	}

	/**
	*	Confirm if point p is inside of the triangle
	*/
	Bool IsInside(const Vector2F& p) const
	{
		return IsInside(BarycentricCoordinates(p));
	}

	Bool IsInside(const Vector3F& barycentricCoordinates) const
	{
		return barycentricCoordinates[0] > 0 && barycentricCoordinates[1] > 0 && barycentricCoordinates[2] > 0;
	}
};
NAMESPACE_END(Engine)