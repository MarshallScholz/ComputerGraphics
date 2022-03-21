#include "Application3D.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Mesh.h"
#include <imgui.h>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

Application3D::Application3D() {

}

Application3D::~Application3D() {

}

bool Application3D::startup() {

	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	m_texturedShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/textured.vert");
	m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/textured.frag");
	if (m_texturedShader.link() == false) {
		printf("Shader Error: %s\n",
			m_texturedShader.getLastError());
		return false;
	}
	if (m_gridTexture.load("./textures/numbered_grid.tga") == false) {
		printf("Failed to load texture!\n");
		return false;
	}

	m_quadMesh.initialiseQuad();

	// make the quad 10 units wide
	m_quadTransform = {
	10,0,0,0,
	0,10,0,0,
	0,0,10,0,
	0,0,0,1 };


	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
		getWindowWidth() / (float)getWindowHeight(),
		0.1f, 1000.f);


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
	if (m_bunnyMesh.load("./stanford/bunny.obj") == false) {
		printf("Bunny Mesh Error!\n");
		return false;
	}
	m_bunnyTransform = {
	0.5f,0,0,0,
	0,0.5f,0,0,
	0,0,0.5f,0,
	0,0,0,1
	};

	if (m_spearMesh.load("./soulspear/soulspear.obj",
		true, true) == false) {
		printf("Soulspear Mesh Error!\n");
		return false;
	}
	m_spearTransform = {
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
	};





	m_light.colour = { 1, 1, 1 };
	m_ambientLight = { 0.05f, 0.05f, 0.05f };

	m_light.direction = glm::normalize(vec3(-1, -1, -1));



	//// load imaginary texture
	//aie::Texture texture1;
	//texture1.load("mytexture.png");
	//// create a 2x2 black-n-white checker texture
	//// RED simply means one colour channel, i.e. grayscale
	//aie::Texture texture2;
	//unsigned char texelData[4] = { 0, 255, 255, 0 };
	//texture2.create(2, 2, aie::Texture::RED, texelData);



	return true;
}

void Application3D::shutdown() {

	Gizmos::destroy();
}

void Application3D::update(float deltaTime) {

	// query time since application started
	float time = 1;

	// rotate light
	/*m_light.direction = glm::normalize(vec3(glm::cos(1),
		glm::sin(1), 0));*/

	// rotate camera
	m_viewMatrix = glm::lookAt(vec3(glm::sin(time) * 10, 10, glm::cos(time) * 10),
		vec3(0), vec3(0, 1, 0));

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


	ImGui::Begin("Light Settings");
	ImGui::DragFloat3("Sunlight Direction", &m_light.direction[0], 0.1f, -10.0f,
		10.0f);
	ImGui::DragFloat3("Sunlight Colour", &m_light.colour[0], 0.1f, 0.0f,
		2.0f);
	ImGui::End();


	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application3D::draw() {

	// wipe the screen to the background colour
	clearScreen();
	// update perspective in case window resized
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
		getWindowWidth() / (float)getWindowHeight(),
		0.1f, 1000.f);
	// bind shader programs
	m_phongShader.bind();

	//bind shader light
	m_phongShader.bindUniform("AmbientColour", m_ambientLight);
	m_phongShader.bindUniform("LightColour", m_light.colour);
	m_phongShader.bindUniform("LightDirection", m_light.direction);
	//bind bunny transform
	auto pvm = m_projectionMatrix * m_viewMatrix * m_bunnyTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	//bind transforms for lighting
	m_phongShader.bindUniform("ModelMatrix", m_bunnyTransform);

	//bind camera
	m_phongShader.bindUniform("cameraPosition",
		vec3(glm::inverse(m_viewMatrix)[3]));

	//draw bunny
	//m_bunnyMesh.draw();


	// bind shader
	m_texturedShader.bind();
	// bind transform
	pvm = m_projectionMatrix * m_viewMatrix * m_quadTransform;
	m_texturedShader.bindUniform("ProjectionViewModel", pvm);
	// bind texture location
	m_texturedShader.bindUniform("diffuseTexture", 0);
	// bind texture to specified location
	m_gridTexture.bind(0);
	// draw quad
	m_quadMesh.draw();



	m_texturedShader.bind();
	// bind transform
	pvm = m_projectionMatrix * m_viewMatrix * m_spearTransform;
	m_texturedShader.bindUniform("ProjectionViewModel", pvm);
	// draw mesh
	m_spearMesh.draw();



	// draw 3D gizmos
	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
	// draw 2D gizmos using an orthogonal projection matrix
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());

}