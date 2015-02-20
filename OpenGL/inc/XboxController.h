#ifndef XBOX_CONTROLLER_H
#define	XBOX_CONTROLLER_H

#include <Windows.h>
#include <Xinput.h>
#include <glm/glm.hpp>

#pragma comment(lib, "Xinput.lib")

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD    30

class XboxController
{
public:
	XboxController(int _number);
	~XboxController();

	XINPUT_STATE GetState();
	bool IsConnected();
	void Vibrate(int _left, int _right);

	glm::vec2 GetLeftThumb();
	glm::vec2 GetRightThumb();
	float GetLeftTrigger();
	float GetRightTrigger();

protected:

private:

	XINPUT_STATE m_controllerState;
	int m_controllerNum;
};

#endif