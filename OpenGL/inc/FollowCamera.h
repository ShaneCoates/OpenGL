#ifndef FOLLOW_CAMERA_H
#define FOLLOW_CAMERA_H

#include <Camera.h>
#include <GLFW\glfw3.h>

class XboxController;
class Object;
class DebugGUI;
class FollowCamera : public Camera
{
public:
	FollowCamera(Object* _target, DebugGUI* _GUI) : Camera()
	{
		Init(_target, _GUI);
	}
	~FollowCamera() {};

	void Init(Object* _target, DebugGUI* _GUI);

	virtual void Update(double dt);

	//TEMP - Pass the window to be used to query the keyboard
	//This will get changed to an Input Manager later
	void SetInputWindow(GLFWwindow* pWindow) { m_pWindow = pWindow; }

	XboxController* GetXboxController()		{return m_controller;}

protected:
	void HandleKeyboardInput(double dt);
	void HandleMouseInput(double dt);
	void HandleControllerInput(double dt);

	void CalculatePosition();

	GLFWwindow* m_pWindow;

	bool m_bViewButtonClicked;
	double m_dCursorX, m_dCursorY;

	XboxController* m_controller;
	Object* m_target;
	DebugGUI* m_GUI;
	glm::vec3 cameraRotation;

	bool m_recalculate;

};

#endif