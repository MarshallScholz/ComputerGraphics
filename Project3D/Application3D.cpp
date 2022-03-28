#include "Application3D.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Mesh.h"
#include <imgui.h>
#include "Camera.h"
#include "Instance.h"
#include "Scene.h"
#include "Light.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

Application3D::Application3D() {

}

Application3D::~Application3D() {

}

bool Application3D::loadShaders()
{
	m_texturedShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/textured.vert");
	m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/textured.frag");
	if (m_texturedShader.link() == false) {
		printf("Shader Error: %s\n",
			m_texturedShader.getLastError());
		return false;
	}

	m_normalMapShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/normalmap.vert");
	m_normalMapShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/normalmap.frag");

	if (m_normalMapShader.link() == false) {
		printf("Shader Error: %s\n",
			m_normalMapShader.getLastError());
		return false;
	}

	m_shader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/simple.frag");

	m_phongShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/phong.frag");

	if (m_shader.link() == false) {
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}
	if (m_phongShader.link() == false) {
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}
}

bool Application3D::loadModels()
{

	if (m_bunnyMesh.load("./stanford/bunny.obj") == false) {
		printf("Bunny Mesh Error!\n");
		return false;
	}

	if (m_spearMesh.load("./soulspear/soulspear.obj",
		true, true) == false) {
		printf("Soulspear Mesh Error!\n");
		return false;
	}
	if (m_lizardMesh.load("./lizard/JosephStevenson_Lizard.obj",
		true, true) == false) {
		printf("Lizard Mesh Error!\n");
		return false;
	}

}

bool Application3D::loadTextures()
{
	if (m_gridTexture.load("./textures/numbered_grid.tga") == false) {
		printf("Failed to load texture!\n");
		return false;
	}
}

void Application3D::createScene()
{
	m_quadMesh.initialiseQuad();

	// make the quad 10 units wide
	m_quadTransform = {
	10,0,0,0,
	0,10,0,0,
	0,0,10,0,
	0,0,0,1 };

	m_bunnyTransform = {
	0.5f,0,0,0,
	0,0.5f,0,0,
	0,0,0.5f,0,
	0,0,0,1
	};

	m_light.colour = { 1, 1, 1 };
	m_ambientLight = { 0.05f, 0.05f, 0.05f };

	m_light.direction = glm::normalize(vec3(-1, -1, -1));

	m_scene = new Scene(m_camera, glm::vec2(getWindowWidth(),
		getWindowHeight()), m_light, glm::vec3(0.25f, 0.25f, 0.25f));


	glm::mat4 spearTransform
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	Instance* spearInstance1 = new Instance(spearTransform, &m_spearMesh,
		&m_normalMapShader);
	spearInstance1->setTransform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	m_scene->addInstance(spearInstance1);

	//Instance* spearInstance2 = new Instance(spearTransform, &m_spearMesh,
	//	&m_normalMapShader);
	//spearInstance2->setTransform(glm::vec3(3, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	//m_scene->addInstance(spearInstance2);

	//Instance* bunnyInstance = new Instance(m_bunnyTransform, &m_bunnyMesh, &m_phongShader);
	//bunnyInstance->setTransform(glm::vec3(-3, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.5f, 0.5f, 0.5f));

	//m_scene->addInstance(bunnyInstance);


	//glm::mat4 lizardTransform
	//{
	//	1,0,0,0,
	//	0,1,0,0,
	//	0,0,1,0,
	//	0,0,0,1
	//};
	//Instance* lizardInstance = new Instance(lizardTransform, &m_lizardMesh, &m_normalMapShader);
	//lizardInstance->setTransform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.1f, 0.1f, 0.1f));
	//m_scene->addInstance(lizardInstance);
	// red light on the left
	m_scene->getPointLights().push_back(Light(vec3(5, 3, 0), vec3(1, 0, 0), 50));
	// green light on the right
	m_scene->getPointLights().push_back(Light(vec3(-5, 3, 0), vec3(0, 1, 0), 50));
}


bool Application3D::startup() {

	setBackgroundColour(0.25f, 0.25f, 0.25f);

	m_camera = new Camera();
	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	//if any of these fail to load, exit the application
	if (loadShaders() == false) { return false; }
	if (loadModels() == false) { return false; }
	if (loadTextures() == false) { return false; }

	createScene();
	
	return true;
}

void Application3D::shutdown() {

	Gizmos::destroy();
	delete m_scene;
}

void Application3D::update(float deltaTime) 
{
	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));


	//Update sunlight
	ImGui::Begin("Global Settings");
	ImGui::DragFloat3("Sunlight Direction", &m_light.direction[0], 0.1f, -10.0f,
		10.0f);
	ImGui::DragFloat3("Sunlight Colour", &m_light.colour[0], 0.1f, 0.0f,
		2.0f);
	ImGui::DragFloat("Camera Speed", &m_camera->m_movementSpeed, 0.1f, 1.0f,
		10.0f);
	ImGui::End();
	m_scene->setLight(m_light);


	m_scene->update(deltaTime);

	// rotate camera
	m_camera->update(deltaTime);

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application3D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// bind transform
	glm::mat4 projectionMatrix = m_camera->getProjectionMatrix(getWindowWidth(),
		(float)getWindowHeight());
	glm::mat4 viewMatrix = m_camera->getViewMatrix();


	//-==========================================================================================
	//Draw grid
	m_scene->draw();
	// bind shader
	m_texturedShader.bind();
	// bind transform
	auto pvm = projectionMatrix * viewMatrix * m_quadTransform;
	m_texturedShader.bindUniform("ProjectionViewModel", pvm);
	// bind texture location
	m_texturedShader.bindUniform("diffuseTexture", 0);
	// bind texture to specified location
	m_gridTexture.bind(0);
	// draw quad
	m_quadMesh.draw();

	//-==========================================================================================
	//Draw scene
	m_scene->draw();


	//-==========================================================================================
	// draw 3D gizmos
	Gizmos::draw(projectionMatrix * viewMatrix);
	// draw 2D gizmos using an orthogonal projection matrix
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());

}