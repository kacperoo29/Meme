#include "stdafx.h"
#include "Camera.h"

#include "Meme/App.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Meme {

	Camera::Camera(uint32_t windowWidth, uint32_t windowHeight, float fov)
	{
		m_Projection = glm::perspectiveFov(glm::radians(fov),
			(float)windowWidth,
			(float)windowHeight,
			1.0f,
			25.0f);
		
		glm::mat4 viewTranslation = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 viewRotate = glm::rotate(viewTranslation, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0));
		m_View = glm::rotate(viewRotate, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0));

		m_VP = m_Projection * m_View;
	}

	void Camera::CalculateViewMatrix()
	{
		glm::mat4 viewTranslation = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 viewRotate = glm::rotate(viewTranslation, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0));
		m_View = glm::rotate(viewRotate, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0));

		m_VP = m_Projection * m_View;
	}

}
