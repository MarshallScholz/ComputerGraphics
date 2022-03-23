#include "Scene.h"
#include "Instance.h"
#include "Light.h"
#include <imgui.cpp>
#include <sstream>
void Scene::addInstance(Instance* instance)
{
	m_instances.push_back(instance);
}
Scene::Scene(Camera* camera, glm::vec2 windowSize, Light& light, glm::vec3 ambientLight)
{
	m_camera = camera;
	m_windowSize = windowSize;
	m_sunLight = light;
	m_ambientLight = ambientLight;
}
Scene::~Scene()
{
	for (auto it = m_instances.begin(); it != m_instances.end(); it++)
		delete* it;
}
void Scene::update(float deltaTime)
{
	ImGui::Begin("Lights");
	for (int i = 0; i < m_pointLights.size(); i++)
	{
		std::string menuText = std::string("Light: ") + std::to_string(i);
		std::string directionText = std::string("Light ") + std::to_string(i) + std::string(" Direction");
		std::string colourText = std::string("Light ") + std::to_string(i) + std::string(" Colour");

		ImGui::BeginMenu(menuText.c_str());
		ImGui::DragFloat3(directionText.c_str(), &m_pointLights[i].direction[0], 0.1f, -100.0f,
			100.0f);
		ImGui::DragFloat3(colourText.c_str(), &m_pointLights[i].colour[0], 0.1f, -50.0f,
			50.0f);
	}
	ImGui::End();
}
void Scene::draw()
{
	for (int i = 0; i < MAX_LIGHTS && i < m_pointLights.size(); i++)
	{
		m_pointLightPositions[i] = m_pointLights[i].direction;
		m_pointLightColours[i] = m_pointLights[i].colour;
		m_pointLights[i].draw();
	}
	for (auto it = m_instances.begin(); it != m_instances.end(); it++)
	{
		Instance* instance = *it;
		instance->draw(this);
	}
}