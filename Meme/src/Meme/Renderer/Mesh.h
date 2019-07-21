#pragma once

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

	class Mesh
	{
	public:
		Mesh(const std::string& objPath);

		inline std::vector<Vertex> GetVertices() { return m_Vertices; }
		inline std::vector<uint32_t> GetIndices() { return m_Indices; }


	private:
		void GenVerticesFromData(std::vector<Vertex>& target,
			const std::vector<glm::vec3>& vertices,
			const std::vector<glm::vec2>& texCoords,
			const std::vector<glm::vec3>& normals,
			const std::string& line
		);

		//TODO: Implement triangle stripping
		/*void StripTriangle(std::vector<Vertex>& target);*/

		std::vector<Vertex> m_Vertices;
		std::vector<uint32_t> m_Indices;

	};
}
