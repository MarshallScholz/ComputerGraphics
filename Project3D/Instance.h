#pragma once
#include <glm/detail/type_mat.hpp>
#include "Application3D.h"

class OBJMesh;
class Shader;
class Instance
{
public:
	void draw(Camera* camera, float windowWidth, float windowHeight, glm::vec3 ambientLight, Light* light);

protected:
	glm::mat4 m_transform;
	aie::OBJMesh* m_mesh;
	aie::ShaderProgram* m_shader;

};

