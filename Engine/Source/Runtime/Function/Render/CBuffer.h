#pragma once
#include "Texture2D.h"
#include "../../Core/Mathematics/Matrix4F.h"


NAMESPACE_BEGIN(Engine)
/**
*	Shared by vertex or pixel shader(similar function as cbuffer(Constant Buffer) of DirectX)
*
*	Note:
*		Rendering stage thier value are not modified
*/
struct ENGINE_API CBuffer
{
	/**
	*	Transform
	*/
	static Matrix4F Model;
	static Matrix4F View;
	static Matrix4F Projection;
	static Matrix4F MV;
	static Matrix4F VP;
	static Matrix4F MVP;

	/**
	*	Properties of main directional light
	*/
	static ColorF MainLightColor;
	static Vector3F MainLightPosition;

	/**
	*	Main camera
	*/
	static Vector3F EyePosition;

	/**
	*	Shader resources(Texture2D)
	*/
	static constexpr SizeType MaxTextureCount = 16;
	static const Texture2D* TextureArray[MaxTextureCount];
	static const Texture2D*& MainTexture;
};
NAMESPACE_END(Engine)