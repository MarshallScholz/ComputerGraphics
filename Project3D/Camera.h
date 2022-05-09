#pragma once
#include <glm/common.hpp>
class Camera
{
public:

	Camera()
	{
	}
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix(float w, float h);
	void update(float deltaTime);

	glm::vec3 getPosition() { return m_position; }

	float m_movementSpeed = 1;
private:
	float m_theta = 0;
	float m_phi = 0;
	glm::vec3 m_position = glm::vec3(-5, 2, 0);

	float m_lastMouseX = 0;
	float m_lastMouseY = 0;
};

