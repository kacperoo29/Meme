#include "stdafx.h"
#include "Mesh.h"

#include "Meme/Core/File.h"

namespace Meme {

	Mesh::Mesh(const std::string& objPath)
	{
		File obj(objPath);

		std::vector<glm::vec3> Vertices;
		std::vector<glm::vec2> TexCoords;
		std::vector<glm::vec3> Normals;

		std::istringstream lines(obj.GetContent());
		std::string line;
		while (getline(lines, line))
		{
			std::stringstream ss(line);
			std::string head;
			ss >> head;
			if (head == "v")
			{
				float x, y, z;
				ss >> x >> y >> z;
				Vertices.push_back(glm::vec3(x, y, z));
			}

			else if (head == "vt")
			{
				float x, y;
				ss >> x >> y;
				TexCoords.push_back(glm::vec2(x, y));
			}

			else if (head == "vn")
			{
				float x, y, z;
				ss >> x >> y >> z;
				Normals.push_back(glm::vec3(x, y, z));
			}

			else if (head == "f")
			{
				std::vector<Vertex> target;
				GenVerticesFromData(target, Vertices, TexCoords, Normals, line);
				/*StripTriangle(target);*/
				for (int i = 0; i < target.size(); i++)
				{
					m_Indices.push_back(m_Vertices.size());
					m_Vertices.push_back(target[i]);					
				}
			}
		}
	}

	void Mesh::GenVerticesFromData(std::vector<Vertex>& target,
		const std::vector<glm::vec3>& vertices,
		const std::vector<glm::vec2>& texCoords,
		const std::vector<glm::vec3>& normals,
		const std::string& line)
	{
		std::string ln = line;
		std::replace(ln.begin(), ln.end(), '/', ' ');
		uint32_t indices[9];
		std::stringstream ss(ln);
		ss >> ln;

		ss >> indices[0]
			>> indices[1]
			>> indices[2]
			>> indices[3]
			>> indices[4]
			>> indices[5]
			>> indices[6]
			>> indices[7]
			>> indices[8];

		for (int i = 0; i < 9; ++i)
			--indices[i];

		Vertex vertex;
		for (int i = 0; i < 3; ++i)
		{
			vertex.Position = vertices[indices[3 * i]];
			vertex.TexCoord = texCoords[indices[3 * i + 1]];
			vertex.Normal = normals[indices[3 * i + 2]];
			target.push_back(vertex);
		}
	}

	//void Mesh::StripTriangle(std::vector<Vertex>& target)
	//{
	//	if (m_Vertices.size() == 0)
	//	{
	//		m_Indices.push_back(0);
	//		m_Indices.push_back(1);
	//		m_Indices.push_back(2);
	//		return;
	//	}

	//	std::vector<std::pair<uint32_t, uint32_t>> matchingIndicies;

	//	for (int i = 0; i < m_Vertices.size(); ++i)
	//	{
	//		for (int j = 0; j < target.size(); ++j)
	//		{
	//			if (target[j] == m_Vertices[i])
	//			{
	//				matchingIndicies.push_back({i, j});
	//			}
	//		}
	//	}



	//}
}
