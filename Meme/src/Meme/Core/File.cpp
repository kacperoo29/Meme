#include "stdafx.h"
#include "File.h"

namespace Meme {

	File::File(const std::string& src)		
	{
		std::ifstream in(src);
		std::string buffer;
		while (getline(in, buffer))
		{
			m_Content += buffer;
			m_Content += '\n';
		}
		in.close();
	}

	void File::ReadFile(const std::string& src)
	{
		std::ifstream in(src);
		std::string buffer;
		while (getline(in, buffer))
		{
			m_Content += buffer;
			m_Content += '\n';
		}
		in.close();
	}
}
