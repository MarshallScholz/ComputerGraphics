#pragma once
#include <glm/common.hpp>
class Light
{
public:
	Light() 
	{
		direction = glm::vec3(0, 0, 0);
		colour = glm::vec3(0, 0, 0);
	};

	Light(glm::vec3 pos, glm::vec3 col, float intensity)
	{
		direction = pos;
		colour = col * intensity;
	}

	void update(float deltaTime);
	void draw();

	glm::vec3 direction;
	glm::vec3 colour;
};

