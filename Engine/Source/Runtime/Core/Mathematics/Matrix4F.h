#pragma once
#include "Matrix.h"


NAMESPACE_BEGIN(Engine)
using Matrix4F = Matrix4<RealType>;


inline const Matrix4F Matrix4F_Identity = Matrix4F
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1,
};


/* Transformation */
ENGINE_API Matrix4F RotateX(RealType radians);
ENGINE_API Matrix4F RotateY(RealType radians);
ENGINE_API Matrix4F RotateZ(RealType radians);
ENGINE_API Matrix4F Scale(const Vector3F& s);
ENGINE_API Matrix4F Translate(const Vector3F& t);

/* View */
ENGINE_API Matrix4F LookAt(const Vector3F& eye, const Vector3F& forward, const Vector3F& up);

/* Projection */
ENGINE_API Matrix4F OrthographicProjection(RealType left, RealType right, RealType bottom, RealType top, RealType nearZ, RealType farZ);
ENGINE_API Matrix4F Frustum(RealType left, RealType right, RealType bottom, RealType top, RealType nearZ, RealType farZ);
ENGINE_API Matrix4F PerspectiveProjection(RealType fovy, RealType aspect, RealType nearZ, RealType farZ);

/* remap */
ENGINE_API Matrix4F HomogeneousClipSpaceToScreenSpace(RealType width, RealType height);
NAMESPACE_END(Engine)