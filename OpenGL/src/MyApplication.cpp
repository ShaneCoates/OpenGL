#include "MyApplication.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameStateManager.h"
#include "Geometry.h"



using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

Application::Application()
{
	if (glfwInit() == false)
		return;
	window = glfwCreateWindow(1240, 768, "Computer Graphics", nullptr, nullptr);

	if (window == nullptr) 
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) 
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return;
	}

	Gizmos::create();
	glClearColor( 0.0f, 0.0f, 0.0f, 1 );
	glEnable(GL_DEPTH_TEST); // enables the depth buffer

	rotation = 0.0f;
	
	currentFrame = 0.0f;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	
	m_gameStateManager = new GameStateManager();
	m_gameStateManager->RegisterState("GEOMETRY", new GeometryTutorial(window));
	m_gameStateManager->Push("GEOMETRY");
	//m_geometry->GenerateObj("data/gun.obj");

}

Application::~Application()
{
	Gizmos::destroy();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void Application::Run()
{
	while (glfwWindowShouldClose(window) == false &&
	glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) 
	{
		double dt = GetDeltaTime();
		
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		m_gameStateManager->Update(dt);		
		m_gameStateManager->Draw();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

double Application::GetDeltaTime()
{
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	return deltaTime;
}