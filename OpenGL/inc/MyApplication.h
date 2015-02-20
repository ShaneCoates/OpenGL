/*
	Author: Shane Coates
	Description: simple application class

*/

#ifndef APPLICATION_H
#define APPLICATION_H
#include <glm/glm.hpp>

struct GLFWwindow;
class GameStateManager;

class Application
{
public:

	Application();
	~Application();

	void Run();

protected:
private:

	double GetDeltaTime();

	GLFWwindow* window;

	float rotation;
	double currentFrame;
	double deltaTime;
	double lastFrame;

	GameStateManager* m_gameStateManager;


};

#endif