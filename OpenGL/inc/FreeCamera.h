#ifndef FREE_CAMERA_H
#define FREE_CAMERA_H

#include <Camera.h>
#include <GLFW\glfw3.h>

class XboxController;

class FreeCamera : public Camera
{
public:
	FreeCamera() : Camera()
	{
		Init();
	}
	FreeCamera(float flySpeed) : Camera(), m_fFlySpeed(flySpeed)
	{
		
	}
	~FreeCamera() {};

	void Init();

	virtual void Update(double dt);

	void SetFlySpeed(float fSpeed)		{m_fFlySpeed = fSpeed;}
	float GetFlySpeed() const { return m_fFlySpeed;  }

	//TEMP - Pass the window to be used to query the keyboard
	//This will get changed to an Input Manager later
	void SetInputWindow(GLFWwindow* pWindow) { m_pWindow = pWindow; }


	XboxController* GetXboxController()		{return m_controller;}

protected:
	void HandleKeyboardInput(double dt);
	void HandleMouseInput(double dt);
	void HandleControllerInput(double dt);

	void CalculateRotation(double dt, double xOffset, double yOffset);

	GLFWwindow* m_pWindow;
	float m_fFlySpeed;

	bool m_bViewButtonClicked;
	double m_dCursorX, m_dCursorY;

	XboxController* m_controller;

};

#endif