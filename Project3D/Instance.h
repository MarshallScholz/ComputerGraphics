#pragma once
#include <glm/detail/type_mat.hpp>
#include <glm/common.hpp>
#include <glm/matrix.hpp>

#include "OBJMesh.h"
#include "Shader.h"
#include "Application3D.h"


class Instance
{
public:
	Instance(glm::mat4 transform, aie::OBJMesh* mesh, aie::ShaderProgram* shader) 
	{
		m_transform = transform;
		m_OBJmesh = mesh;
		m_shader = shader;
	}

	Instance(glm::mat4 transform, Mesh* mesh, aie::ShaderProgram* shader)
	{
		m_transform = transform;
		m_altMesh = mesh;
		m_shader = shader;
	}

	void initializeShader(Scene* scene);

	void draw(Camera* camera, float windowWidth, float windowHeight, glm::vec3 ambientLight, Light* light);

	void draw(Scene* scene);

	glm::mat4 makeTransform(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale);

	void setTransform(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale);

	aie::ShaderProgram* getShader() { return m_shader; }

protected:
	glm::mat4 m_transform;
	aie::OBJMesh* m_OBJmesh = nullptr;
	Mesh* m_altMesh = nullptr;
	aie::ShaderProgram* m_shader;


};

