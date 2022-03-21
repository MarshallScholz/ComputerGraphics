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

	float m_movementSpeed = 1;
	void setMovementSpeed(float movementSpeed) { m_movementSpeed = movementSpeed; }
	float getMovementSpeed() { return m_movementSpeed; }
private:
	float m_theta = 0;
	float m_phi = 0;
	glm::vec3 m_position = glm::vec3(-5, 2, 0);

	float m_lastMouseX;
	float m_lastMouseY;
};

