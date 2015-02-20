#include "FollowCamera.h"
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <iostream>
#include "XboxController.h"
#include "Object.h"
#include "DebugGUI.h"

void FollowCamera::Init(Object* _target, DebugGUI* _GUI)
{
	m_target = _target;
	m_GUI = _GUI;
	m_bViewButtonClicked = false;
	m_controller = new XboxController(0);
	cameraRotation.x = 200.0f;
	cameraRotation.y = 100.0f;
	cameraRotation.z = 1.8f;
	m_GUI->AddValue("Camera Rotation X", TW_TYPE_DIR3F, &cameraRotation, "");

}

void FollowCamera::Update(double dt)
{
	m_recalculate = false;
	HandleKeyboardInput(dt);
	HandleMouseInput(dt);
	HandleControllerInput(dt);
	if(m_recalculate)
		CalculatePosition();
}

void FollowCamera::HandleKeyboardInput(double dt)
{
		//Get the cameras forward/up/right
	glm::vec3 vRight = m_worldTransform[0].xyz;
	glm::vec3 vUp = m_worldTransform[1].xyz;
	glm::vec3 vForward = m_worldTransform[2].xyz;

	glm::vec3 moveDir(0.0f);

	if (glfwGetKey(m_pWindow, GLFW_KEY_W) == GLFW_PRESS || 
		(glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS
		&& glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS))
	{
		moveDir -= vForward;
	}

	if (glfwGetKey(m_pWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		moveDir += vForward;
	}

	if (glfwGetKey(m_pWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		moveDir -= vRight;
	}

	if (glfwGetKey(m_pWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		moveDir += vRight;
	}

	if (glfwGetKey(m_pWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		moveDir += glm::vec3(0.0f, 1.0f, 0.0f);
	}
	if (glfwGetKey(m_pWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		moveDir -= glm::vec3(0.0f, 1.0f, 0.0f);
	}

	float fLength = glm::length(moveDir);
	if (fLength > 0.01f)
	{
		moveDir = ((float)dt) * glm::normalize(moveDir);
		SetPosition(GetPosition() + moveDir);
	}
}

void FollowCamera::HandleMouseInput(double dt)
{
	if (glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{
		if (m_bViewButtonClicked == false)
		{
			int width, height;
			glfwGetFramebufferSize(m_pWindow, &width, &height);


			m_dCursorX = width / 2.0;
			m_dCursorY = height / 2.0;
			glfwSetCursorPos(m_pWindow, m_dCursorX, m_dCursorY);
			m_bViewButtonClicked = true;
		}
		else
		{
			double mouseX, mouseY;
			glfwGetCursorPos(m_pWindow, &mouseX, &mouseY);

			double xOffset = mouseX - m_dCursorX;
			double yOffset = mouseY - m_dCursorY;

			m_dCursorX = mouseX;
			m_dCursorY = mouseY;

			std::cout << xOffset << " " << yOffset << std::endl;
		}
	}
	else
	{
		m_bViewButtonClicked = false;
	}
}

void FollowCamera::HandleControllerInput(double dt)
{
	if(m_controller->IsConnected())
	{
		glm::mat4 objTransform = m_target->GetTransform();
		glm::vec3 vRight = m_worldTransform[0].xyz;
		glm::vec3 vUp = objTransform[1].xyz;
		glm::vec3 vForward = m_worldTransform[2].xyz;
		vForward.y = 0;
		vRight.y = 0;
		glm::vec3 moveDir = glm::vec3(0);

		glm::vec2 leftThumb = m_controller->GetLeftThumb();
		moveDir += vForward * -leftThumb.y;
		moveDir += vRight * leftThumb.x;

		float fLength = glm::length(moveDir);
		if (fLength > 0.01f)
		{
			moveDir = ((float)dt) * 100 * glm::normalize(moveDir);
			m_target->Translate(moveDir);
			m_recalculate = true;
		}

		glm::vec2 rightThumb = m_controller->GetRightThumb();
		cameraRotation.z -= rightThumb.x * 0.01f;
		cameraRotation.x -= rightThumb.y;
		fLength = glm::length(cameraRotation);
		if(fLength > 0.01f)
			m_recalculate = true;

	}
}

void FollowCamera::CalculatePosition()
{
	if(cameraRotation.x < 50.0f) cameraRotation.x = 50.0f;

	glm::vec3 cameraPos = m_target->GetPosition() + glm::vec3(cameraRotation.x*cos(cameraRotation.z), cameraRotation.x * 0.5f, cameraRotation.x*sin(cameraRotation.z));
	m_worldTransform[3] = glm::vec4(cameraPos, 1);
	SetLookAt(m_target->GetPosition(), glm::vec3(0, 1, 0));

	/*glm::vec3 targetRotation = glm::normalize(m_target->GetPosition() - cameraPos);
	glm::quat q;
	glm::vec3 a = glm::cross(cameraPos, m_target->GetPosition());
	q.x = a.x; q.y = a.y; q.z - a.z;
	q.w = sqrt((m_target->GetPosition().length() ^ 2) * (cameraPos.length() ^ 2)) + glm::dot(m_target->GetPosition(), cameraPos);
	m_target->RotateTo(q);*/
}

