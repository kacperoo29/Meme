#pragma once

namespace Meme {

	class Mesh 
	{
	public:
		Mesh(const std::string& objPath);

		inline std::vector<glm::vec3> GetVertices() const { return m_Vertices; }
		inline std::vector<glm::vec3> GetNormals() const { return m_Normals; }
		inline std::vector<glm::vec2> GetTextureVertices() const { return m_TextureVertices; }
		inline std::vector<uint32_t> GetVertexIndices() const { return m_VertexIndices; }		
		inline std::vector<uint32_t> GetTextureIndices() const { return m_TextureIndices; }
		inline std::vector<uint32_t> GetNormalIndices() const { return m_NormalIndices; }

	private:
		std::vector<glm::vec3> m_Vertices;
		std::vector<glm::vec3> m_Normals;
		std::vector<glm::vec2> m_TextureVertices;		
		std::vector<uint32_t> m_VertexIndices;		
		std::vector<uint32_t> m_TextureIndices;
		std::vector<uint32_t> m_NormalIndices;

	};
}
