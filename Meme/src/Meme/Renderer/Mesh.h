#pragma once

#include "Texture.h"

namespace Meme {

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoord;
		glm::vec3 Normal;

		inline bool operator==(const Vertex& v) const
		{
			return (this->Position == v.Position &&
				this->TexCoord == v.TexCoord &&
				this->Normal == v.Normal);
		}
	};

	struct Material
	{
		std::string name;
		float opticalDensity;		// How much light passes through (range 000.1-10.0, 1.52 for glass)
		glm::vec3 ambientColor;
		glm::vec3 diffuseColor;
		glm::vec3 specularColor;
		glm::vec3 emmisiveColor;
		float specularWeight;
		float transparency;				
		uint32_t illuminationMode;

		Ref<Texture> mapKd;
		Ref<Texture> mapBump;
		Ref<Texture> mapKa;
		Ref<Texture> mapKs;

	};

	class Mesh
	{
	public:
		Mesh() {}
		void LoadOBJ(const std::string& objPath);

		inline const std::vector<Vertex>& GetVertices() { return m_Vertices; }
		inline const std::vector<uint32_t>& GetIndices() { return m_Indices; }

		inline float* GetVerticesPointer() { return &m_Vertices[0].Position.x; }
		inline uint32_t* GetIndicesPointer() { return &m_Indices[0]; }

		inline uint32_t GetVerticesSize() { return sizeof(Vertex) * m_Vertices.size(); }
		inline uint32_t GetIndicesSize() { return  m_Indices.size(); }

		inline std::vector<Material> GetMaterial() { return m_Material; }

	private:
		void GenVerticesFromData(std::vector<Vertex>& target,
			const std::vector<glm::vec3>& vertices,
			const std::vector<glm::vec2>& texCoords,
			const std::vector<glm::vec3>& normals,
			const std::string& line
		);

		void LoadMTL(const std::string& src);

		//TODO: Implement triangle stripping
		//void StripTriangle(std::vector<Vertex>& target);

		std::vector<Vertex> m_Vertices;
		std::vector<uint32_t> m_Indices;
		std::vector<Material> m_Material;

	};
}
