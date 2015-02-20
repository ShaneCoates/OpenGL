/*
	Author: Shane Coates
	Description: Geometry tutorial state
*/

#ifndef GEOMETRY_H
#define	GEOMETRY_H

#include <glm\glm.hpp>
#include "GameStateManager.h"
class FollowCamera;
struct GLFWwindow;
class Object;
class DebugGUI;
class Skybox;

class GeometryTutorial : public IGameState
{
public:
	GeometryTutorial(GLFWwindow* _window) : IGameState()
	{
		Init(_window);		
	};
	~GeometryTutorial();

	void Init(GLFWwindow* _window);

	void Update(double dt);
	void Draw();

	void GenerateGrid(unsigned int rows, unsigned int cols);

	void GenerateObj(const char* _path);

protected:

private:

	void LoadShaders();

	unsigned int m_programID;
	unsigned int m_skyboxProgramID;

	FollowCamera* camera;
	glm::vec4 white;
	glm::vec4 black;

	float rotation;

	GLFWwindow* window;
	Object* m_testObject;
	Object* m_testObject2;
	Skybox* m_skybox;
	DebugGUI* m_GUI;

};

#endif