#pragma once
#include "CBuffer.h"


NAMESPACE_BEGIN(Engine)
/**
*	Tips:
*		OS - Object(Model) Space
*		WS - World Space
*		VS - View Space
*		CS - Homogeneous Clip Space
*/


/**
*	Vertex shader input
*/
struct Attributes
{
	Vector4F positionOS;
	Vector3F normalOS;
	Vector2F uv;
	ColorF color;
};


/**
*	Pixel shader input
*/
struct Varyings
{
	Vector4F positionCS;
	Vector3F normalWS;
	Vector3F viewDirectionWS;
	Vector2F uv;
	ColorF color;
};


/**
*	Vertex shader
*/
ENGINE_API Varyings DefaultVertexShader(const Attributes& attributes);
/**
*	Pixel shader
*/
ENGINE_API ColorF BlinnPhong(const Varyings& varyings);
ENGINE_API ColorF Toon(const Varyings& varyings);
ENGINE_API ColorF Unlit(const Varyings& varyings);
/**
*	Debug
*/
ENGINE_API ColorF OutputNormal(const Varyings& varyings);
ENGINE_API ColorF OutputUV(const Varyings& varyings);
ENGINE_API ColorF OutputColor(const Varyings& varyings);
#pragma endregion
NAMESPACE_END(Engine)