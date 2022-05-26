#pragma once
#include "Shader.h"


NAMESPACE_BEGIN(Engine)
enum class Primitive {
	Point,
	Line,
	Triangle
};


struct Vertex {
	Vector3F position;
	Vector3F normal;
	Vector2F uv;
	ColorF color;

	Vertex(const Vector3F& position = Vector3F(), const Vector3F& normal = Vector3F(), const Vector2F& uv = Vector2F(), const ColorF& color = ColorF())
		: position(position), normal(normal), uv(uv), color(color) {}
};


struct ENGINE_API Mesh
{
	NOT_COPYABLE(Mesh);


	SizeType vertexCount;
	SizeType indexCount;
	Vertex* vertices;
	UInt32* indices;
	Primitive type;
	// Storing transformed vertex attributes
	Varyings* vertexBuffer;


	static const Mesh Triangle;
	static const Mesh Square;
	static const Mesh Cube;


	Mesh(SizeType vertexCount, SizeType indexCount, Vertex* vertices, UInt32* indices, Primitive type = Primitive::Triangle);
	~Mesh();


	static Mesh* Load(const Path& path);
private:
	Void CreateVertexBuffer(SizeType count);
};


struct ENGINE_API MeshArray {
	NOT_COPYABLE(MeshArray);


	SizeType submeshCount;
	SizeType textureCount;
	/*submesh <--> texture
	* use it to set main texture of current submesh
	* if map[?] == -1, use default texture(Texture2D::White)
	*/
	Int32* map;
	Mesh** submeshes;
	Texture2D** textures;


	MeshArray(SizeType submeshCount, SizeType textureCount, Int32* map, Mesh** submeshes, Texture2D** textures);
	~MeshArray();


	static MeshArray* Load(const Path& path);
};
NAMESPACE_END(Engine)