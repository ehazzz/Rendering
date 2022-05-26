#include "Renderer.h"


NAMESPACE_BEGIN(Engine)
Void Renderer::Draw(const Mesh& mesh)
{
	// Preset
	if (CBuffer::MainTexture == nullptr) 
		CBuffer::MainTexture = &Texture2D::White;


	TransformVertex(mesh.vertices, mesh.vertexBuffer, mesh.vertexCount);

	switch (mesh.type)
	{
	case Primitive::Point:
		break;
	case Primitive::Line:
		break;
	case Primitive::Triangle:
		SetTriangle(mesh.vertexBuffer, mesh.indices, mesh.indexCount);
		break;
	}
}

Void Renderer::Draw(const MeshArray& meshArray)
{
	for (Int32 i = 0; i < meshArray.submeshCount; i++) {
		auto map = meshArray.map[i];

		CBuffer::MainTexture = meshArray.textures[map];

		if (meshArray.submeshes[i]) Draw(*meshArray.submeshes[i]);
	}
}

Serface& Renderer::GetSerface()
{
	return serface;
}

Void Renderer::DrawLine(Int32 x0, Int32 y0, Int32 x1, Int32 y1, const ColorF& color)
{
	auto xMin = 0;
	auto xMax = serface.GetWidth() - 1;
	auto yMin = 0;
	auto yMax = serface.GetHeight() - 1;

	// limit x at [0, width - 1]
	// limit y at [0, height - 1]
	x0 = Clamp(x0, xMin, xMax);
	x1 = Clamp(x1, xMin, xMax);
	y0 = Clamp(y0, yMin, yMax);
	y1 = Clamp(y1, yMin, yMax);

	Int32 dx = Absolute(x0 - x1); // distance of horizontal direction
	Int32 dy = Absolute(y0 - y1); // distance of vertical direction

	if (dx == 0 && dy == 0)
		serface.SetPixel(x0, y0, color);
	else
		if (dx > dy) {
			if (x0 > x1) {
				Swap(&x0, &x1);
				Swap(&y0, &y1);
			}

			for (Int32 x = x0; x <= x1; x++) {
				RealType t = (x - x0) / (RealType)dx;
				Int32 y = Lerp(y0, y1, t);

				serface.SetPixel(x, y, color);
			}
		}
		else {
			if (y0 > y1) {
				Swap(&y0, &y1);
				Swap(&x0, &x1);
			}

			for (Int32 y = y0; y <= y1; y++) {
				RealType t = (y - y0) / (RealType)dy;
				Int32 x = Lerp(x0, x1, t);

				serface.SetPixel(x, y, color);
			}
		}
}

Void Renderer::DrawLine(const Vector2F& A, const Vector2F& B, const ColorF& color)
{
	DrawLine(A[0] + 0.5f, A[1] + 0.5f, B[0] + 0.5f, B[1] + 0.5f, color);
}

Void Renderer::DrawTriangle(const Triangle& triangle, const ColorF& color)
{
	DrawLine(triangle.a, triangle.b, color);
	DrawLine(triangle.a, triangle.c, color);
	DrawLine(triangle.b, triangle.c, color);
}

Void Renderer::TransformVertex(Vertex* from, Varyings* to, Int32 vertexCount)
{
	for (Int32 i = 0; i < vertexCount; i++) {
		Varyings& output = to[i];

		// assign
		Attributes input;
		{
			input.positionOS = ToVector4(from[i].position, 1.0f);
			input.normalOS = from[i].normal;
			input.uv = from[i].uv;
			input.color = from[i].color;
		}

		//do vertex shader work here
		output = RenderPipeline::VS(input);

		// perspective div
		RealType w = output.positionCS[3];
		output.positionCS /= w;

		// map to screen space
		RealType x = (output.positionCS[0] + 1) * serface.GetWidth() / 2;
		RealType y = (output.positionCS[1] + 1) * serface.GetHeight() / 2;

		// depth value map to [0, 1] from [1, -1]
		RealType depth = (output.positionCS[2] - 1) * (-0.5f);

		// for interpolating vertex attributes with perspective correction
		output.positionCS = Vector4F{ x, y, depth / w, w };
		output.normalWS /= w;
		output.viewDirectionWS /= w;
		output.uv /= w;
		output.color /= w;
	}
}

Void Renderer::SetTriangle(Varyings* vertexBuffer, UInt32* indices, UInt32 indexCount)
{
	for (Int32 i = 0; i < indexCount; i += 3)
	{
		// indices of the triangle
		auto ia = indices[i];
		auto ib = indices[i + 1];
		auto ic = indices[i + 2];

		// vertex attributes of the triangle
		auto va = &vertexBuffer[ia];
		auto vb = &vertexBuffer[ib];
		auto vc = &vertexBuffer[ic];

		// pre-cull(simple method)
		{
			auto Fn = [&](const Varyings* input) {
				auto x = input->positionCS[0];
				auto y = input->positionCS[1];
				auto z = input->positionCS[2];

				if (x < 0 || x >= serface.GetWidth() ||
					y < 0 || y >= serface.GetHeight() ||
					z < 0 || z > 1.0f)
					return true;
				else
					return false;
			};

			if (Fn(va) || Fn(vb) || Fn(vc)) continue;
		}

		auto triangle = Triangle{
			ToVector2(va->positionCS),
			ToVector2(vb->positionCS),
			ToVector2(vc->positionCS),
		};

		FillTriangle(triangle, va, vb, vc);
	}
}

Void Renderer::FillTriangle(const Triangle& triangle, Varyings* varyingsA, Varyings* varyingsB, Varyings* varyingsC)
{
	// vertex attributes of the triangle
	auto& va = *varyingsA;
	auto& vb = *varyingsB;
	auto& vc = *varyingsC;

	if (CullOp(
		RenderPipeline::cullMode,
		ToVector3(CBuffer::View.GetRow(2)),
		Cross(ToVector3(va.positionCS - vb.positionCS), ToVector3(vc.positionCS - vb.positionCS))
	))
		return;

	if ((RenderPipeline::fillMode & FillMode::Solid) == FillMode::Solid)
	{
		RealType inverseWA = 1 / va.positionCS[3];
		RealType inverseWB = 1 / vb.positionCS[3];
		RealType inverseWC = 1 / vc.positionCS[3];

		auto aabb = CalculateAABB(triangle);
		for (Int32 x = aabb[0]; x <= aabb[1]; x++)
			for (Int32 y = aabb[2]; y <= aabb[3]; y++)
			{
				// any point of a plane, position of the pixel add (0.5, 0.5) is center of the pixel
				auto p = Vector2F{ x + 0.5f, y + 0.5f };
				auto barycentricCoordinate = triangle.BarycentricCoordinates(p);

				if (!triangle.IsInside(barycentricCoordinate)) continue;

				RealType weight = 1.0f / (inverseWA * barycentricCoordinate[0] + inverseWB * barycentricCoordinate[1] + inverseWC * barycentricCoordinate[2]);
				auto interpParams = Vector4F{ barycentricCoordinate[0], barycentricCoordinate[1], barycentricCoordinate[2], weight };

				// interpolate depth
				RealType depth = InterpolateAttributes(va.positionCS[2], vb.positionCS[2], vc.positionCS[2], interpParams);

				// depth test failed
				if (!DepthTestOp(RenderPipeline::depthTestMode, x, y, depth)) continue;

				// interpolate vertex attributes
				Varyings in;
				in.normalWS = InterpolateAttributes(va.normalWS, vb.normalWS, vc.normalWS, interpParams);
				in.viewDirectionWS = InterpolateAttributes(va.viewDirectionWS, vb.viewDirectionWS, vc.viewDirectionWS, interpParams);
				in.uv = InterpolateAttributes(va.uv, vb.uv, vc.uv, interpParams);
				in.color = InterpolateAttributes(va.color, vb.color, vc.color, interpParams);

				// do pixel shader work here
				auto shade = RenderPipeline::PS(in);

				if (RenderPipeline::discarded) continue;

				// update depth buffer
				if (RenderPipeline::depthWriteMode == DepthWriteMode::Enable) serface.SetDepth(x, y, depth);

				// blend
				auto output = BlendOp(RenderPipeline::blendMode, shade, serface.GetPixel(x, y));

#ifdef LINEAR_COLOR_SPACE
				output = ToSRGB(output);
#endif //

				// update color buffer(frame buffer)
				serface.SetPixel(x, y, output);
			}
	}

	if ((RenderPipeline::fillMode & FillMode::Wireframe) == FillMode::Wireframe)
		DrawTriangle(triangle);
}

Bool Renderer::CullOp(CullMode mode, const Vector3F& viewDirection, const Vector3F& triangleNormal)
{
	Bool isBackface = false;
	if (Dot(viewDirection, triangleNormal) < 0) isBackface = true;

	RenderPipeline::backface = isBackface;

	switch (mode)
	{
	case CullMode::Disable:
		return false;
	case CullMode::Back:
		return isBackface ? true : false;
		break;
	case CullMode::Front:
		return !isBackface ? true : false;
	}
}

Bool Renderer::DepthTestOp(DepthTestMode mode, Int32 x, Int32 y, RealType depth)
{
	switch (mode)
	{
	case DepthTestMode::Disable:
		return false;
	case DepthTestMode::Less:
		return depth < serface.GetDepth(x, y) ? true : false;
	case DepthTestMode::LEqual:
		return depth <= serface.GetDepth(x, y) ? true : false;
	case DepthTestMode::Equal:
		return depth == serface.GetDepth(x, y) ? true : false;
	case DepthTestMode::Greater:
		return depth > serface.GetDepth(x, y) ? true : false;
	case DepthTestMode::GEqual:
		return depth >= serface.GetDepth(x, y) ? true : false;
	case DepthTestMode::Always:
		return true;
	}
}

ColorF Renderer::BlendOp(BlendMode mode, const ColorF& source, const ColorF& destination)
{
	switch (mode)
	{
	case BlendMode::Disable:
		return source;
	case BlendMode::SrcAlpha_OneMinusSrcAlpha:
		return Blend(source, destination);
	default:
		return ColorF_Red;
	}
}

Vector4Int Renderer::CalculateAABB(const Triangle& triangle)
{
	auto& a = triangle.a;
	auto& b = triangle.b;
	auto& c = triangle.c;

	Int32 left		= Minimum(a[0], b[0], c[0]);
	Int32 right		= Maximum(a[0], b[0], c[0]);
	Int32 bottom	= Minimum(a[1], b[1], c[1]);
	Int32 top		= Maximum(a[1], b[1], c[1]);

	return Vector4Int{ left, right, bottom, top };
}
NAMESPACE_END(Engine)