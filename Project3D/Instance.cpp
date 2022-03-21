#include "Instance.h"
#include "Camera.h"

//void Instance::draw(Camera* camera, float windowWidth, float windowHeight,
//	glm::vec3 ambientLight, Application3D::Light* light)
//{
//	// set the shader pipeline
//	m_shader->bind();
//	// bind transform and other uniforms
//	auto pvm = camera->getProjectionMatrix(windowWidth, windowHeight) * camera -
//> getViewMatrix() * m_transform;
//	m_shader->bindUniform("ProjectionViewModel", pvm);
//
//	m_shader->bindUniform("ModelMatrix", m_transform);
//	m_shader->bindUniform("AmbientColour", ambientLight);
//	m_shader->bindUniform("LightColour", light->colour);
//	m_shader->bindUniform("LightDirection", light->direction);
//	m_shader->bindUniform("cameraPosition", camera->getPosition());
//	// draw mesh
//	m_mesh->draw();
//}
