#include "Geometry.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "FollowCamera.h"
#include "Object.h"
#include "DebugGUI.h"
#include "XboxController.h"

using namespace glm;
using namespace std;
void GeometryTutorial::Init(GLFWwindow* _window)
{
	SetUpdateBlocking(false);
	SetDrawBlocking(false);

	window = _window;

	LoadShaders();

	
	white = vec4(1, 1, 1, 1);
	black = vec4(0.2f,0.2f,0.2f,1);
	glClearColor(black.r, black.g, black.b, black.a);

	rotation = 0.0f;

	m_testObject = new Object("data/Bloodwing.obj", m_programID);
	m_testObject2 = new Object("data/battledroid.obj", m_programID);
	m_testObject2->Translate(glm::vec3(30, 0, 0));
	m_testObject->SetScale(glm::vec3(0.05f));
	m_testObject2->SetScale(glm::vec3(0.1f));
	m_GUI = new DebugGUI(_window);
	m_GUI->AddValue("Clear Colour", TW_TYPE_COLOR4F, &black, "");


	camera = new FollowCamera(m_testObject, m_GUI);
	camera->SetInputWindow(window);
	camera->SetPerspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	camera->SetLookAt(vec3(50, 50, 50), vec3(0, 0, 0), vec3(0, 1, 0));
}

GeometryTutorial::~GeometryTutorial()
{

}

void GeometryTutorial::Update(double dt)
{
	if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		m_testObject->Translate(vec3(0, dt * 10, 0));
		//camera->Translate(vec3(0, dt * 10 , 0));
	}
	if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		m_testObject->Translate(vec3(0, -dt * 10, 0));

	float speed = 1 + camera->GetXboxController()->GetRightTrigger() - camera->GetXboxController()->GetLeftTrigger();
	m_testObject->SetLightSpeed(speed);
	m_testObject2->SetLightSpeed(speed);

	camera->Update(dt);
	m_testObject->Update(dt);
	m_testObject2->Update(dt);
	m_GUI->Update(dt);
	glClearColor(black.r, black.g, black.b, black.a);
}

void GeometryTutorial::Draw()
{
	m_testObject->Draw(camera);
	m_testObject2->Draw(camera);
	Gizmos::clear();
	Gizmos::addSphere(m_testObject->GetLightPos(), 1, 10, 10, vec4(1, 1, 0, 1));
	Gizmos::draw( camera->GetProjection(), camera->GetView());

	m_GUI->Draw();
}

void GeometryTutorial::LoadShaders()
{	
	std::string vsSource, fsSource;
	std::ifstream vertFile("data/shader.vert", std::ios::in);
	if(!vertFile.is_open())
		std::cerr << "Could not read vertex shader" << std::endl;
	
	std::string line = "";
	while(!vertFile.eof())
	{
		std::getline(vertFile, line);
		vsSource.append(line + "\n");
	}
	vertFile.close();
	std::ifstream fragFile("data/shader.frag", std::ios::in);
	if(!fragFile.is_open())
		std::cerr << "Could not read fragment shader" << std::endl;
	
	line = "";
	
	while(!fragFile.eof())
	{
		std::getline(fragFile, line);
		fsSource.append(line + "\n");
	}
	
	fragFile.close();


	const char* vertShader = vsSource.c_str();
	const char* fragShader = fsSource.c_str();

	int success = GL_FALSE;
	unsigned int vertexShader =		glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (const char**)&vertShader, 0);
	glShaderSource(fragmentShader, 1, (const char**)&fragShader, 0);
	
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	m_programID = glCreateProgram();
	 
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
	glLinkProgram(m_programID);

	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if(success == GL_FALSE) 
	{
		int infoLogLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetProgramInfoLog(m_programID, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

}