#include "stdafx.h"
#include "Mesh.h"

namespace Meme {

	void Mesh::LoadOBJ(const std::string& objPath)
	{
		std::ifstream source(objPath);
		if (!source)
			return;

		std::vector<glm::vec3> Vertices;
		std::vector<glm::vec2> TexCoords;
		std::vector<glm::vec3> Normals;
		
		std::string line;
		while (getline(source, line))
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

		source.close();

		std::string filename = objPath.substr(0, objPath.size() - 4);
		if (std::filesystem::exists(filename + ".mtl"))
		{
			LoadMTL(filename + ".mtl");
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

	void Mesh::LoadMTL(const std::string& src)
	{
		std::ifstream source(src);
		if (!source)
			return;

		std::string line;
		int index = -1;
		while (getline(source, line))
		{
			std::stringstream ss(line);
			std::string head;
			ss >> head;

			if (head == "newmtl")
			{
				++index;
				m_Material.push_back(Material());
				ss >> m_Material[index].name;
			}
			else if (head == "Ns")
			{
				ss >> m_Material[index].opticalDensity;
			}
			else if (head == "Ka")
			{
				float x, y, z;
				ss >> x >> y >> z;
				m_Material[index].ambientColor = glm::vec3(x, y, z);
			}
			else if (head == "Kd")
			{
				float x, y, z;
				ss >> x >> y >> z;
				m_Material[index].diffuseColor = glm::vec3(x, y, z);
			}
			else if (head == "Ks")
			{
				float x, y, z;
				ss >> x >> y >> z;
				m_Material[index].specularColor = glm::vec3(x, y, z);
			}
			else if (head == "Ke")
			{
				float x, y, z;
				ss >> x >> y >> z;
				m_Material[index].emmisiveColor = glm::vec3(x, y, z);
			}
			else if (head == "Ni")
			{
				ss >> m_Material[index].specularWeight;
			}
			else if (head == "d")
			{
				ss >> m_Material[index].transparency;
			}
			else if (head == "illum")
			{
				ss >> m_Material[index].illuminationMode;
			}
			else if (head == "map_Kd")
			{
				std::string name;
				ss >> name;
				m_Material[index].mapKd.reset(Texture::Create("res/texture/" + name));
			}
			else if (head == "map_Bump")
			{
				std::string name;
				ss >> name;
				m_Material[index].mapBump.reset(Texture::Create("res/texture/" + name));
			}
			else if (head == "map_Ka")
			{
				std::string name;
				ss >> name;
				m_Material[index].mapKa.reset(Texture::Create("res/texture/" + name));
			}
			else if (head == "map_Ks")
			{
				std::string name;
				ss >> name;
				m_Material[index].mapKs.reset(Texture::Create("res/texture/" + name));
			}
		}

		source.close();
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

	//	for (int i = 0; i < 3; ++i)
	//	{
	//		bool matching = false;
	//		uint32_t matchingIndex;
	//		for (int j = 0; j < 3; ++j)
	//		{
	//			if (target[i] == m_Vertices[j])
	//			{
	//				matching = true;
	//				break;
	//			}
	//		}
	//		if (!matching)
	//		{
	//			auto m = *std::max_element(m_Indices.begin(), m_Indices.end());
	//			m_Vertices.push_back(target[i]);
	//			m_Indices.push_back(m + 1);
	//		}
	//	}

	//}
}
