#pragma once
#include <glm/common.hpp>
#include "Application3D.h"
#include <map>
#include <list>
#include "Light.h"
class Instance;
class Camera;
#define MAX_LIGHTS 4
class Scene
{
public:
	Scene(Camera* camera, glm::vec2 windowSize, Light& sunLight, glm::vec3
		ambientLight);

	~Scene();

	void addInstance(Instance* instance);

	void update(float deltaTime);
	void draw();

	Camera* getCamera() const { return m_camera; }

	glm::vec2 getWindowSize() const { return m_windowSize; }

	glm::vec3 getAmbientLight() const { return m_ambientLight; }
	void setAmbientLight(glm::vec3 ambientLight) { m_ambientLight = ambientLight; }

	void setLight(Light sunLight) { m_sunLight = sunLight; }

	Light getLight() const { return m_sunLight; }

	int getNumLights() { return (int)m_pointLights.size(); }
	glm::vec3* getPointlightPositions() { return &m_pointLightPositions[0]; }
	glm::vec3* getPointlightColours() { return &m_pointLightColours[0]; }
	std::vector<Light>& getPointLights() { return m_pointLights; }


protected:
	Camera* m_camera = nullptr;
	glm::vec2 m_windowSize = glm::vec2(0, 0);
	Light m_sunLight = Light();
	std::vector<Light> m_pointLights = std::vector<Light>();
	glm::vec3 m_ambientLight = glm::vec3(0, 0, 0);
	std::list<Instance*> m_instances = std::list<Instance*>();

	glm::vec3 m_pointLightPositions[MAX_LIGHTS];
	glm::vec3 m_pointLightColours[MAX_LIGHTS];

	std::map<aie::ShaderProgram*, int> shaderMap;
	aie::ShaderProgram* shaderKey[10] = {nullptr};

};


