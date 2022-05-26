#include "Shader.h"
#include "RenderPipeline.h"


NAMESPACE_BEGIN(Engine)
Varyings DefaultVertexShader(const Attributes& attributes)
{
	auto& M		= CBuffer::Model;
	auto& V		= CBuffer::View;
	auto& P		= CBuffer::Projection;
	auto& MV	= CBuffer::MV;
	auto& VP	= CBuffer::VP;
	auto& MVP	= CBuffer::MVP;

	auto&& normal		= ToVector3(M * ToVector4(attributes.normalOS));
	auto&& positionWS	= ToVector3(M * attributes.positionOS);

	Varyings varyings;
	varyings.positionCS			= MVP * attributes.positionOS;
	varyings.normalWS			= Normalize(normal);
	varyings.viewDirectionWS	= Normalize(CBuffer::EyePosition - positionWS);
	varyings.uv					= attributes.uv;
	varyings.color				= attributes.color;
	return varyings;
}

ColorF BlinnPhong(const Varyings& varyings)
{
	constexpr RealType Gloss = 400;

	auto N	= RenderPipeline::backface ? -varyings.normalWS : varyings.normalWS;
	auto& L = CBuffer::MainLightPosition;
	auto& V = varyings.viewDirectionWS;

	RealType NDotL	= Dot(N, L);
	RealType NDotV	= Dot(N, V);
	Vector3F H		= Normalize(L + V);

	RealType diffuse	= Maximum(NDotL, 0.0f);
	RealType specular	= Power(Maximum(Dot(N, H), 0.0f), Gloss);

	ColorF albedo = CBuffer::MainTexture->Sample(varyings.uv);
	ColorF finalColor = albedo * CBuffer::MainLightColor * (diffuse + specular);
	finalColor[3] = albedo[3];

	return finalColor;
}

ColorF Toon(const Varyings& varyings)
{
	constexpr auto shadowThreshold = 0.5F;
	constexpr auto lighting = 0.9F;
	constexpr auto shadow = lighting * 0.7F;

	auto N	= RenderPipeline::backface ? -varyings.normalWS : varyings.normalWS;
	auto& L = CBuffer::MainLightPosition;
	auto& V = varyings.viewDirectionWS;

	RealType NDotL = Dot(N, L);

	auto diffuse = NDotL > shadowThreshold ? lighting : shadow;

	ColorF albedo = CBuffer::MainTexture->Sample(varyings.uv);
	ColorF finalColor = albedo * CBuffer::MainLightColor * diffuse;
	finalColor[3] = albedo[3];

	return finalColor;
}

ColorF Unlit(const Varyings& varyings)
{
	return CBuffer::MainTexture->Sample(varyings.uv);
}

ColorF OutputNormal(const Varyings& varyings)
{
	auto normal = RenderPipeline::backface ?
		-varyings.normalWS : varyings.normalWS;

#ifdef LINEAR_COLOR_SPACE
	return ToLinear(ToVector4((normal + Vector3F(1.0f)) * 0.5, 1.0f));
#else
	return ToVector4((normal + Vector3F(1.0f)) * 0.5, 1.0f);
#endif // LINEAR_COLOR_SPACE
}

ColorF OutputUV(const Varyings& varyings)
{
#ifdef LINEAR_COLOR_SPACE
	return ToLinear(ToVector4(varyings.uv, 0.0f, 1.0f));
#else
	return ToVector4(varyings.uv, 0.0f, 1.0f);
#endif // LINEAR_COLOR_SPACE
}

ColorF OutputColor(const Varyings& varyings)
{
#ifdef LINEAR_COLOR_SPACE
	return ToLinear(varyings.color);
#else
	return varyings.color;
#endif // LINEAR_COLOR_SPACE
}
NAMESPACE_END(Engine)