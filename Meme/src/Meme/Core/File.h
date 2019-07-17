#pragma once

#include <string>

namespace Meme {

	class File {
	public:
		File() {}
		File(const std::string& src);

		void ReadFile(const std::string& src);

		inline const std::string& GetContent() { return m_Content; }

		operator std::string() { return m_Content; }

	private:
		std::string m_Content;

	};
}