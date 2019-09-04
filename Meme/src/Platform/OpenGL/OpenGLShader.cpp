#include "stdafx.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Meme {

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		uint32_t vs, fs;

		vs = glCreateShader(GL_VERTEX_SHADER);

		std::string temp;
		std::ifstream in(vertexSrc);
		in.seekg(0, std::ios::end);
		temp.resize(in.tellg());
		in.seekg(0);
		in.read(temp.data(), temp.size());
		in.close();

		const char* src = (const char*)temp.c_str();
		glShaderSource(vs, 1, &src, 0);
		glCompileShader(vs);

		temp.clear();

		int32_t isCompiled;
		glGetShaderiv(vs, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int32_t maxLength = 0;
			glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);			
			char* infoLog = new char[maxLength];
			glGetShaderInfoLog(vs, maxLength, &maxLength, &infoLog[0]);		

			glDeleteShader(vs);

			MEME_CORE_ERROR("Vertex shader compilation error!");
			MEME_CORE_ERROR("{0}", infoLog);
			delete infoLog;
			return;
		}

		fs = glCreateShader(GL_FRAGMENT_SHADER);
		
		in.open(fragmentSrc);		
		in.seekg(0, std::ios::end);
		temp.resize(in.tellg());
		in.seekg(0);
		in.read(temp.data(), temp.size());
		in.close();

		src = (const char*)temp.c_str();
		glShaderSource(fs, 1, &src, 0);
		glCompileShader(fs);
		
		glGetShaderiv(fs, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int32_t maxLength = 0;
			glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);
			char* infoLog = new char[maxLength];
			glGetShaderInfoLog(fs, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vs);
			glDeleteShader(fs);

			MEME_CORE_ERROR("Fragment shader compilation error!");
			MEME_CORE_ERROR("{0}", infoLog);
			delete infoLog;
			return;
		}

		m_ID = glCreateProgram();

		glAttachShader(m_ID, vs);
		glAttachShader(m_ID, fs);

		glLinkProgram(m_ID);

		int32_t isLinked = 0;
		glGetProgramiv(m_ID, GL_LINK_STATUS, (int32_t*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			int32_t maxLength = 0;
			glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &maxLength);
						
			char* infoLog = new char[maxLength];
			glGetProgramInfoLog(m_ID, maxLength, &maxLength, &infoLog[0]);
			
			glDeleteProgram(m_ID);		
			glDeleteShader(vs);
			glDeleteShader(fs);

			MEME_CORE_ERROR("Program linking error!");
			MEME_CORE_ERROR("{0}", infoLog);
			delete infoLog;
			return;
		}
		
		glDetachShader(m_ID, vs);
		glDetachShader(m_ID, fs);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_ID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniform3f(const std::string& name, const glm::vec3& vector)
	{
		uint32_t location = glGetUniformLocation(m_ID, name.c_str());
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void OpenGLShader::UploadUniformMat4f(const std::string& name, const glm::mat4& matrix)
	{
		uint32_t location = glGetUniformLocation(m_ID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}
