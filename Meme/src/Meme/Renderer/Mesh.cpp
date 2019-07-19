#include "stdafx.h"
#include "Mesh.h"

#include "Meme/Core/File.h"

namespace Meme {

	Mesh::Mesh(const std::string& objPath)
	{
		File obj(objPath);	

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
				m_Vertices.push_back(glm::vec3(x, y, z));
			}

			else if (head == "vt")
			{
				float x, y;
				ss >> x >> y;
				m_TextureVertices.push_back(glm::vec2(x, y));
			}

			else if (head == "vn")
			{
				float x, y, z;
				ss >> x >> y >> z;
				m_Normals.push_back(glm::vec3(x, y, z));
			}

			else if (head == "f")
			{
				std::string part;
				int index = 0;
				while (ss >> part)
				{
					int x, y, z;
					std::replace(part.begin(), part.end(), '/', ' ');
					std::stringstream n(part);
					n >> x >> y >> z;
					m_VertexIndices.push_back(x - 1);
					m_TextureIndices.push_back(y - 1);
					m_NormalIndices.push_back(z - 1);
					++index;
				}
			}
		}
	}

}
