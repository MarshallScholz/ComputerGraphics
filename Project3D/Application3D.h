#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"
#include "Light.h"

class Camera;
class Scene;
class Instance;

class Application3D : public aie::Application {
public:

	Application3D();
	virtual ~Application3D();

	bool loadShaders();
	bool loadModels();
	bool loadTextures();

	void createScene();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	glm::mat4	m_viewMatrix;

	glm::mat4	m_projectionMatrix;

	aie::Texture m_gridTexture;

	aie::ShaderProgram m_shader;
	aie::ShaderProgram m_phongShader;
	aie::ShaderProgram m_texturedShader;
	aie::ShaderProgram m_normalMapShader;
	aie::ShaderProgram m_toonShader;
	aie::ShaderProgram m_edgeShader;



	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;

	aie::OBJMesh m_bunnyMesh;
	glm::mat4 m_bunnyTransform;

	aie::OBJMesh m_spearMesh;
	//glm::mat4 m_spearTransform;

	aie::OBJMesh m_lizardMesh;



	Light m_light;
	glm::vec3 m_ambientLight; 

	Camera* m_camera = nullptr;

	Scene* m_scene = nullptr;

	//glm::mat4 m_spearTransform;
	Instance* m_spearInstance;

};
