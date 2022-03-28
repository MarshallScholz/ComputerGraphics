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

	void setPosition(glm::vec3 position) { m_position = position; }
	glm::vec3 getPosition() const { return m_position; }

	glm::vec3 getRotation() const { return m_eularAngles; }
	void setRotation(glm::vec3 eularAngles) { m_eularAngles = eularAngles; }

	glm::vec3 getScale() const { return m_scale; }
	void setScale(glm::vec3 scale) { m_scale = scale; }


	aie::ShaderProgram* getShader() { return m_shader; }

protected:
	glm::mat4 m_transform;
	aie::OBJMesh* m_OBJmesh = nullptr;
	Mesh* m_altMesh = nullptr;
	aie::ShaderProgram* m_shader;
	glm::vec3 m_position;
	glm::vec3 m_eularAngles;
	glm::vec3 m_scale;


};

