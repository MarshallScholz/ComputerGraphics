#pragma once
#include <glm/common.hpp>
#include "Application3D.h"
#include <list>

class Instance;
class Camera;

class Scene
{
public:
	Scene(Camera* camera, glm::vec2 windowSize, Application3D::Light& light, glm::vec3
		ambientLight);

	~Scene();

	void addInstance(Instance* instance);

	void draw();

	Camera* getCamera() const { return m_camera; }

	glm::vec2 getWindowSize() const { return m_windowSize; }

	glm::vec3 getAmbientLight() const { return m_ambientLight; }
	void setAmbientLight(glm::vec3 ambientLight) { m_ambientLight = ambientLight; }

	void setLight(Application3D::Light light) { m_light = light; }

	Application3D::Light getLight() const { return m_light; }


protected:
	Camera* m_camera;
	glm::vec2 m_windowSize;
	Application3D::Light m_light;
	glm::vec3 m_ambientLight;
	std::list<Instance*> m_instances;
};


