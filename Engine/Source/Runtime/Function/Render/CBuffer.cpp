#include "CBuffer.h"


NAMESPACE_BEGIN(Engine)
Matrix4F CBuffer::Model			= Matrix4F_Identity;
Matrix4F CBuffer::View			= Matrix4F_Identity;
Matrix4F CBuffer::Projection	= Matrix4F_Identity;
Matrix4F CBuffer::MV			= Matrix4F_Identity;
Matrix4F CBuffer::VP			= Matrix4F_Identity;
Matrix4F CBuffer::MVP			= Matrix4F_Identity;

ColorF CBuffer::MainLightColor		= ColorF_White;
Vector3F CBuffer::MainLightPosition = Normalize(Vector3F_One);

Vector3F CBuffer::EyePosition		= Vector3F_Zero;

const Texture2D* CBuffer::TextureArray[CBuffer::MaxTextureCount]	= {};
const Texture2D*& CBuffer::MainTexture								= CBuffer::TextureArray[0];
NAMESPACE_END(Engine)