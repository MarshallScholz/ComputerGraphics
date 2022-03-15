#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"

class Application3D : public aie::Application {
public:

	Application3D();
	virtual ~Application3D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	aie::ShaderProgram m_shader;
	aie::ShaderProgram m_phongShader;
	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;

	aie::OBJMesh m_bunnyMesh;
	glm::mat4 m_bunnyTransform;

	struct Light {
		glm::vec3 direction;
		glm::vec3 colour;
	};
	Light m_light;
	glm::vec3 m_ambientLight;

	glm::vec3 m_camera;

};
