#include "Light.h"
#include <Gizmos.h>
#include <imgui.h>
void Light::update(float deltaTime)
{
	//ImGui::DragFloat3("Light Direction", &this->direction[0], 10.0f, -10.0f,
	//	0.01f);
	//ImGui::DragFloat3("Light Colour", &this->colour[0], 5.f, 0.0f,
	//	2.0f);
}
void Light::draw()
{
	aie::Gizmos::addSphere(direction, 0.1f, 8, 16, glm::vec4(colour,1));
}
