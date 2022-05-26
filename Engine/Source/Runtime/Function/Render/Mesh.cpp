#include "Mesh.h"
#include "../../Core/String/Character.h"

#include <fstream>
#include <sstream>


NAMESPACE_BEGIN(Engine)
#pragma region /* Mesh */
const Mesh Mesh::Triangle = {
	3, 3,
	new Vertex[3]{
		Vertex{Vector3F{0, Sine(Pi<RealType> / 3) / 2, 0}, Vector3F{0, 0, 1}, Vector2F{0.5, 1}, ColorF_Red},
		Vertex{Vector3F{0.5f, Sine(Pi<RealType> / 3) / 2 * -1, 0}, Vector3F{0, 0, 1}, Vector2F{1, 0}, ColorF_Green},
		Vertex{Vector3F{-0.5f, Sine(Pi<RealType> / 3) / 2 * -1, 0}, Vector3F{0, 0, 1}, Vector2F{-1, 0}, ColorF_Blue}
	},
	new UInt32[3]{
		0, 1, 2
	}
};

const Mesh Mesh::Square = {
	4, 6,
	new Vertex[4]{
		Vertex{Vector3F{-0.5f, -0.5f, 0}, Vector3F{0, 0, 1}, Vector2F{0, 0}, ColorF_Red},
		Vertex{Vector3F{0.5f, -0.5f, 0}, Vector3F{0, 0, 1}, Vector2F{1, 0}, ColorF_Green},
		Vertex{Vector3F{0.5f, 0.5f, 0}, Vector3F{0, 0, 1}, Vector2F{1, 1}, ColorF_Blue},
		Vertex{Vector3F{-0.5f, 0.5f, 0}, Vector3F{0, 0, 1}, Vector2F{0, 1}, ColorF_White}
	},
	new UInt32[6]{
		2, 1, 0,
		0, 3, 2
	}
};

const Mesh Mesh::Cube = {
	4 * 6, 6 * 6,
	new Vertex[24]{
		//forward
		Vertex{Vector3F{-0.5f, -0.5f, 0.5f}, Vector3F{0, 0, 1}, Vector2F{0, 0}, ColorF_Red},
		Vertex{Vector3F{0.5f, -0.5f, 0.5f}, Vector3F{0, 0, 1}, Vector2F{1, 0}, ColorF_Green},
		Vertex{Vector3F{0.5f, 0.5f, 0.5f}, Vector3F{0, 0, 1}, Vector2F{1, 1}, ColorF_Blue},
		Vertex{Vector3F{-0.5f, 0.5f, 0.5f}, Vector3F{0, 0, 1}, Vector2F{0, 1}, ColorF_White},

		//back
		Vertex{Vector3F{0.5f, -0.5f, -0.5f}, Vector3F{0, 0, -1}, Vector2F{0, 0}, ColorF_Red},
		Vertex{Vector3F{-0.5f, -0.5f, -0.5f}, Vector3F{0, 0, -1}, Vector2F{1, 0}, ColorF_Green},
		Vertex{Vector3F{-0.5f, 0.5f, -0.5f}, Vector3F{0, 0, -1}, Vector2F{1, 1}, ColorF_Blue},
		Vertex{Vector3F{0.5f, 0.5f, -0.5f}, Vector3F{0, 0, -1}, Vector2F{0, 1}, ColorF_White},

		//left
		Vertex{Vector3F{-0.5f, -0.5f, -0.5f}, Vector3F{-1, 0, 0}, Vector2F{0, 0}, ColorF_Red},
		Vertex{Vector3F{-0.5f, -0.5f, 0.5f}, Vector3F{-1, 0, 0}, Vector2F{1, 0}, ColorF_Green},
		Vertex{Vector3F{-0.5f, 0.5f, 0.5f}, Vector3F{-1, 0, 0}, Vector2F{1, 1}, ColorF_Blue},
		Vertex{Vector3F{-0.5f, 0.5f, -0.5f}, Vector3F{-1, 0, 0}, Vector2F{0, 1}, ColorF_White},

		//right
		Vertex{Vector3F{0.5f, -0.5f, 0.5f}, Vector3F{1, 0, 0}, Vector2F{0, 0}, ColorF_Red},
		Vertex{Vector3F{0.5f, -0.5f, -0.5f}, Vector3F{1, 0, 0}, Vector2F{1, 0}, ColorF_Green},
		Vertex{Vector3F{0.5f, 0.5f, -0.5f}, Vector3F{1, 0, 0}, Vector2F{1, 1}, ColorF_Blue},
		Vertex{Vector3F{0.5f, 0.5f, 0.5f}, Vector3F{1, 0, 0}, Vector2F{0, 1}, ColorF_White},

		//bottom
		Vertex{Vector3F{-0.5f, -0.5f, -0.5f}, Vector3F{0, -1, 0}, Vector2F{0, 0}, ColorF_Red},
		Vertex{Vector3F{0.5f, -0.5f, -0.5f}, Vector3F{0, -1, 0}, Vector2F{1, 0}, ColorF_Green},
		Vertex{Vector3F{0.5f, -0.5f, 0.5f}, Vector3F{0, -1, 0}, Vector2F{1, 1}, ColorF_Blue},
		Vertex{Vector3F{-0.5f, -0.5f, 0.5f}, Vector3F{0, -1, 0}, Vector2F{0, 1}, ColorF_White},

		//top
		Vertex{Vector3F{-0.5f, 0.5f, 0.5f}, Vector3F{0, 1, 0}, Vector2F{0, 0}, ColorF_Red},
		Vertex{Vector3F{0.5f, 0.5f, 0.5f}, Vector3F{0, 1, 0}, Vector2F{1, 0}, ColorF_Green},
		Vertex{Vector3F{0.5f, 0.5f, -0.5f}, Vector3F{0, 1, 0}, Vector2F{1, 1}, ColorF_Blue},
		Vertex{Vector3F{-0.5f, 0.5f, -0.5f}, Vector3F{0, 1, 0}, Vector2F{0, 1}, ColorF_White},
	},
	new UInt32[36]{
		//forward
		2, 1, 0,
		0, 3, 2,

		//back
		6, 5, 4,
		4, 7, 6,

		//left
		10, 9, 8,
		8, 11, 10,

		//right
		14, 13, 12,
		12, 15, 14,

		//bottom
		18, 17, 16,
		16, 19, 18,

		//top
		22, 21, 20,
		20, 23, 22
	}
};


Mesh::Mesh(SizeType vertexCount, SizeType indexCount, Vertex* vertices, UInt32* indices, Primitive type)
	: vertexCount(vertexCount), indexCount(indexCount), vertices(vertices), indices(indices), type(type)
{
	CreateVertexBuffer(vertexCount);
}

Mesh::~Mesh()
{
	Allocator::Release(vertices);
	Allocator::Release(indices);
	Allocator::Release(vertexBuffer);
}

Mesh* Mesh::Load(const Path& path)
{
	auto fileStream = std::fstream{ path, std::ios::in };
	if (!fileStream.is_open()) return nullptr;

	//current index of vertices
	UInt32 vi = 0;
	//current index of uvs
	UInt32 ti = 0;
	//current index of normals
	UInt32 ni = 0;
	//current index of indices
	UInt32 ii = 0;

	// Count Annotation
	//  vertex count
	constexpr Char vertexCountAnnotation = 'V';
	//	index count
	constexpr Char indexCountAnnotation = 'I';

	// Vertex Attributes Annotation
	//	position
	constexpr Char positionAnnotation = 'v';
	//	texture coordinate
	constexpr Char textureCoordinateAnnotation = 't';
	//	normal
	constexpr Char normalAnnotation = 'n';
	//	index Data
	constexpr Char indexAnnotation = 'i';

	/* Mesh Data */
	SizeType vertexCount = 0;
	SizeType indexCount = 0;
	Vertex* vertices = nullptr;
	UInt32* indices = nullptr;

	Char buffer[64];
	std::stringstream ss;

	/* -1 is end of file */
	while (fileStream.peek() != -1)
	{
		fileStream.getline(buffer, Character::NewLine);
		ss.clear();

		// read vertex and index count, and allocate memory block
		if (buffer[0] == '[')
		{
			Char annotation = buffer[1];

			fileStream.getline(buffer, Character::NewLine);
			ss << buffer;

			switch (annotation)
			{
			case vertexCountAnnotation:
			{
				ss >> vertexCount;
				vertices = Allocator::Allocate<Vertex>(vertexCount);
			}
			break;
			case indexCountAnnotation:
			{
				ss >> indexCount;
				indices = Allocator::Allocate<UInt32>(indexCount);
			}
			break;
			}
		}

		Char annotation = buffer[0];
		Char* begin = &buffer[2];
		ss << begin;
		// read vertex attributes and index data
		switch (annotation)
		{
		// vertex attributes
		case positionAnnotation:
			for (Int32 i = 0; i < 3; i++) ss >> vertices[vi].position[i];
			vi++;
			break;
		case textureCoordinateAnnotation:
			for (Int32 i = 0; i < 2; i++) ss >> vertices[ti].uv[i];
			ti++;
			break;
		case normalAnnotation:
			for (Int32 i = 0; i < 3; i++) ss >> vertices[ni].normal[i];
			ni++;
			break;
		// index data
		case indexAnnotation:
			ss >> indices[ii++];
			break;
		}
	}

	return new Mesh[1]{ {vertexCount, indexCount, vertices, indices} };
}

Void Mesh::CreateVertexBuffer(SizeType count)
{
	vertexBuffer = Allocator::Allocate<Varyings>(count);
}
#pragma endregion


#pragma region /* MeshArray */
MeshArray::MeshArray(SizeType submeshCount, SizeType textureCount, Int32* map, Mesh** submeshes, Texture2D** textures)
	: submeshCount(submeshCount), textureCount(textureCount), map(map), submeshes(submeshes), textures(textures) {}

MeshArray::~MeshArray()
{
	if (submeshes)
		for (auto i = 0; i < submeshCount; i++)
			Allocator::Release(submeshes[i]);

	if (textures)
		for (auto i = 0; i < textureCount; i++)
			Allocator::Release(textures[i]);

	Allocator::Release(submeshes);
	Allocator::Release(textures);
	Allocator::Release(map);
}

MeshArray* MeshArray::Load(const Path& path)
{
	auto fileStream = std::fstream{ path, std::ios::in };
	if (!fileStream.is_open()) return nullptr;

	auto relativePath = Path(path).remove_filename();

	auto sperator = relativePath.preferred_separator;
	constexpr const Char* submeshFolderName = "Splits";
	constexpr const Char* textureFolderName = "Textures";

	// Annotation
	//	element count
	constexpr Char countAnnotation = 'C';
	//	submesh
	constexpr Char submeshAnnotation = 'S';
	//	texture
	constexpr Char textureAnnotation = 'T';
	//	map
	constexpr Char mapAnnotation = 'M';

	/* Mesh Array Data */
	SizeType submeshCount = 0;
	SizeType textureCount = 0;
	Int32* map = nullptr;
	Mesh** submeshes = nullptr;
	Texture2D** textures = nullptr;

	Char buffer[128];
	std::stringstream ss;

	/* -1 is end of file */
	while (fileStream.peek() != -1) {
		fileStream.getline(buffer, Character::NewLine);
		ss.clear();

		// annotation begin
		if (buffer[0] != '[') continue;

		// annotation
		auto first = buffer[1]; // first annotation
		auto secondary = buffer[8]; // secondary annotation

		// lamda function
		auto GetElementCount = [&]() {
			ss.clear();
			ss << buffer;

			SizeType count = 0;
			ss >> count;

			return count;
		};

		switch (first)
		{
		case submeshAnnotation:
			if (secondary == countAnnotation) {
				fileStream.getline(buffer, Character::NewLine);

				submeshCount = GetElementCount();
				map = Allocator::Allocate<Int32>(submeshCount);
				submeshes = Allocator::Allocate<Mesh*>(submeshCount);
			}
			else
				for (Int32 i = 0; i < submeshCount; i++) {
					fileStream.getline(buffer, Character::NewLine);

					auto path = relativePath / submeshFolderName / buffer;

					submeshes[i] = Mesh::Load(path);
				}
			break;
		case textureAnnotation:
			if (secondary == countAnnotation) {
				fileStream.getline(buffer, Character::NewLine);

				textureCount = GetElementCount();
				textures = Allocator::Allocate<Texture2D*>(submeshCount);
			}
			else
				for (Int32 i = 0; i < textureCount; i++) {
					fileStream.getline(buffer, Character::NewLine);

					auto path = relativePath / textureFolderName / buffer;

					textures[i] = Texture2D::Load(path);
				}
			break;
		case mapAnnotation:
			for (Int32 i = 0; i < submeshCount; i++) {
				fileStream.getline(buffer, Character::NewLine);

				ss.clear();
				ss << buffer;
				ss >> map[i];
			}
			break;
		}
	}
	
	return new MeshArray[1]{ {submeshCount, textureCount, map, submeshes, textures} };
}
#pragma endregion
NAMESPACE_END(Engine)