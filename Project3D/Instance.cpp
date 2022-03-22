#include "Instance.h"
#include "Camera.h"
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"


void Instance::draw(Camera* camera, float windowWidth, float windowHeight, glm::vec3 ambientLight, Application3D::Light* light)
{
	// set the shader pipeline
	m_shader->bind();
	// bind transform and other uniforms
	auto pvm = camera->getProjectionMatrix(windowWidth, windowHeight) * camera -> getViewMatrix() * m_transform;
	m_shader->bindUniform("ProjectionViewModel", pvm);

	m_shader->bindUniform("ModelMatrix", m_transform);
	m_shader->bindUniform("AmbientColour", ambientLight);
	m_shader->bindUniform("LightColour", light->colour);
	m_shader->bindUniform("LightDirection", light->direction);
	m_shader->bindUniform("cameraPosition", camera->getPosition());
	// draw mesh
	m_mesh->draw();
}

void Instance::draw(Scene* scene)
{

	// set the shader pipeline
	m_shader->bind();
	// bind transform and other uniforms
	auto pvm = scene->getCamera()->getProjectionMatrix(scene->getWindowSize().x,
		scene->getWindowSize().y)
		* scene->getCamera()->getViewMatrix() * m_transform;
	m_shader->bindUniform("ProjectionViewModel", pvm);

	m_shader->bindUniform("ModelMatrix", m_transform);
	m_shader->bindUniform("AmbientColour", scene->getAmbientLight());
	m_shader->bindUniform("LightColour", scene->getLight().colour);
	m_shader->bindUniform("LightDirection", scene->getLight().direction);
	m_shader->bindUniform("cameraPosition", scene->getCamera()->getPosition());
	// draw mesh
	m_mesh->draw();
}

void Instance::setTransform(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale)
{
	m_transform = glm::translate(glm::mat4(1), position)
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.x), glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), scale);
}
