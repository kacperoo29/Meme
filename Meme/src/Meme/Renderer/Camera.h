#pragma once

#include <glm/glm.hpp>

namespace Meme {

	class Camera {
	public:
		Camera() {}
		Camera(uint32_t windowWidth, uint32_t windowHeight, float fov);

		void SetPosition(const glm::vec3& position) 
		{ m_Position = position; CalculateViewMatrix(); }
		void SetRotation(const glm::vec2& rotation) 
		{ m_Rotation = rotation; CalculateViewMatrix(); }

		inline const glm::vec2& GetRotation() const { return m_Rotation; }
		inline const glm::vec3& GetPosition() const { return m_Position; }


		inline const glm::mat4& GetVP() const { return m_VP; }
		inline const glm::mat4& GetViewMatrix() const { return m_View; }
		inline const glm::mat4& GetProjectionMatrix() const { return m_Projection; }

	private:
		void CalculateViewMatrix();

		glm::vec2 m_Rotation = { 0.f, 0.f };
		glm::vec3 m_Position = { 0.f, 0.f, -1.f };

		glm::mat4 m_VP;
		glm::mat4 m_Projection;
		glm::mat4 m_View;
	};

}