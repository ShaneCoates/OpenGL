#include "XboxController.h"

XboxController::XboxController(int _number)
{
	m_controllerNum = _number;
}

XboxController::~XboxController()
{

}

XINPUT_STATE XboxController::GetState()
{
	ZeroMemory(&m_controllerState, sizeof(XINPUT_STATE));

	XInputGetState(m_controllerNum, &m_controllerState);

	return m_controllerState;
}

bool XboxController::IsConnected()
{
    ZeroMemory(&m_controllerState, sizeof(XINPUT_STATE));

    DWORD Result = XInputGetState(m_controllerNum, &m_controllerState);

    if(Result == ERROR_SUCCESS)
        return true;
    else
        return false;
}

void XboxController::Vibrate(int _left, int _right)
{
    XINPUT_VIBRATION Vibration;

    ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

    Vibration.wLeftMotorSpeed = _left;
    Vibration.wRightMotorSpeed = _right;

    XInputSetState(m_controllerNum, &Vibration);
}

glm::vec2 XboxController::GetLeftThumb()
{
	XINPUT_STATE state = GetState();

	float X = state.Gamepad.sThumbLX;
	float Y = state.Gamepad.sThumbLY;

	float magnitude = sqrt(X*X + Y*Y);

	float normalizedX = X / magnitude;
	float normalizedY = Y / magnitude;

	if(magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return glm::vec2(normalizedX, normalizedY);
	else
		return glm::vec2(0, 0);

}

glm::vec2 XboxController::GetRightThumb()
{
	XINPUT_STATE state = GetState();

	float X = state.Gamepad.sThumbRX;
	float Y = state.Gamepad.sThumbRY;

	float magnitude = sqrt(X*X + Y*Y);

	float normalizedX = X / magnitude;
	float normalizedY = Y / magnitude;

	if(magnitude > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return glm::vec2(normalizedX, normalizedY);
	else
		return glm::vec2(0, 0);

}

float XboxController::GetLeftTrigger()
{
	return GetState().Gamepad.bLeftTrigger / 255.0f;
}

float XboxController::GetRightTrigger()
{
	return GetState().Gamepad.bRightTrigger / 255.0f;
}