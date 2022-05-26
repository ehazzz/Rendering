#include "Matrix4F.h"


NAMESPACE_BEGIN(Engine)
Matrix4F RotateX(RealType radians)
{
	RealType cosine = Cosine(radians);
	RealType sine = Sine(radians);

	auto result = Matrix4F_Identity;
	result[1][1] = cosine;
	result[2][1] = sine;
	result[1][2] = -sine;
	result[2][2] = cosine;

	return result;
}

Matrix4F RotateY(RealType radians)
{
	RealType cosine = Cosine(radians);
	RealType sine = Sine(radians);

	auto result = Matrix4F_Identity;
	result[0][0] = cosine;
	result[2][0] = -sine;
	result[0][2] = sine;
	result[2][2] = cosine;

	return result;
}

Matrix4F RotateZ(RealType radians)
{
	RealType cosine = Cosine(radians);
	RealType sine = Sine(radians);

	auto result = Matrix4F_Identity;
	result[0][0] = cosine;
	result[1][0] = sine;
	result[0][1] = -sine;
	result[1][1] = cosine;

	return result;
}

Matrix4F Scale(const Vector3F& s)
{
	auto result = Matrix4F_Identity;
	for (SizeType index = 0; index < 3; index++)
		result[index][index] = s[index];

	return result;
}

Matrix4F Translate(const Vector3F& t)
{
	auto result = Matrix4F_Identity;
	for (SizeType index = 0; index < 3; index++)
		result[index][3] = t[index];

	return result;
}

Matrix4F LookAt(const Vector3F& eye, const Vector3F& forward, const Vector3F& up)
{
	auto g = Normalize(forward);
	auto t = Normalize(up);
	auto gxt = Cross(g, t);

	auto R = Matrix4F_Identity;
	R.SetRow(0, ToVector4(gxt));
	R.SetRow(1, ToVector4(t));
	R.SetRow(2, ToVector4(-g));

	return R * Translate(-eye);
}

Matrix4F OrthographicProjection(RealType left, RealType right, RealType bottom, RealType top, RealType nearZ, RealType farZ)
{
	auto S = Scale( 
		Vector3F{
			2 / (right - left),
			2 / (top - bottom),
			2 / (nearZ - farZ) 
		}
	);

	auto T = Translate(
		Vector3F{
			-(right + left) / 2,
			-(top + bottom) / 2,
			-(nearZ + farZ) / 2 
		}
	);

	return S * T;
}

Matrix4F Frustum(RealType left, RealType right, RealType bottom, RealType top, RealType nearZ, RealType farZ)
{
	Matrix4F perspToOrtho;
	Memory::Set(perspToOrtho.components, 0.0f, Matrix4F::Count);
	perspToOrtho[0][0] = nearZ;
	perspToOrtho[1][1] = nearZ;
	perspToOrtho[2][2] = nearZ + farZ;
	perspToOrtho[2][3] = -nearZ * farZ;
	perspToOrtho[3][2] = 1.0f;

	return OrthographicProjection(left, right, bottom, top, nearZ, farZ) * perspToOrtho;
}

Matrix4F PerspectiveProjection(RealType fovy, RealType aspect, RealType nearZ, RealType farZ)
{
	RealType halfWidth, halfHeight;
	halfHeight = Tangent(fovy / 2) * nearZ;
	halfWidth = aspect * halfHeight;

	return Frustum(-halfWidth, halfWidth, -halfHeight, halfHeight, nearZ, farZ);
}

Matrix4F HomogeneousClipSpaceToScreenSpace(RealType width, RealType height)
{
	auto halfWidth = width / 2;
	auto halfHeight = height / 2;

	auto S = Scale(
		Vector3F
		{
			halfWidth,
			halfHeight,
			1.0f
		}
	);

	auto T = Translate(
		Vector3F
		{
			halfWidth,
			halfHeight,
			0.0f
		}
	);

	return T * S;
}
NAMESPACE_END(Engine)