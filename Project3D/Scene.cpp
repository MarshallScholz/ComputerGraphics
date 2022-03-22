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
	for (int i = 0; i < m_pointLights.size(); i++)
	{
		//int a = 10;
		//char* intStr = std::itoa itoa(a);
		//std::string str = std::string(intStr);

		ImGui::Begin("Light: " /* + string*/);
		ImGui::DragFloat3("Light Direction", &m_pointLights[i].direction[i], 0.1f, -10.0f,
		10.0f);
		ImGui::DragFloat3("Light Colour", &m_pointLights[i].colour[i], 0.1f, 0.0f,
		2.0f);
		ImGui::End();
	}
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