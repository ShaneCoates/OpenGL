#include "FreeCamera.h"
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <iostream>
#include "XboxController.h"

void FreeCamera::Init()
{
	m_fFlySpeed = 10.0f;
	m_bViewButtonClicked = false;
	m_controller = new XboxController(0);
}

void FreeCamera::Update(double dt)
{
	HandleKeyboardInput(dt);
	HandleMouseInput(dt);
	HandleControllerInput(dt);
}

void FreeCamera::HandleKeyboardInput(double dt)
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
		moveDir = ((float)dt * m_fFlySpeed) * glm::normalize(moveDir);
		SetPosition(GetPosition() + moveDir);
	}
}

void FreeCamera::HandleMouseInput(double dt)
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

			CalculateRotation(dt, xOffset, yOffset);

			std::cout << xOffset << " " << yOffset << std::endl;
		}
	}
	else
	{
		m_bViewButtonClicked = false;
	}
}

void FreeCamera::HandleControllerInput(double dt)
{
	if(m_controller->IsConnected())
	{
		glm::vec3 vRight = m_worldTransform[0].xyz;
		glm::vec3 vUp = m_worldTransform[1].xyz;
		glm::vec3 vForward = m_worldTransform[2].xyz;
		glm::vec3 moveDir = glm::vec3(0);

		glm::vec2 leftThumb = m_controller->GetLeftThumb();

		moveDir += vForward * -leftThumb.y;
		moveDir += vRight * leftThumb.x;

		float fLength = glm::length(moveDir);
		if (fLength > 0.01f)
		{
			moveDir = ((float)dt * m_fFlySpeed) * glm::normalize(moveDir);
			SetPosition(GetPosition() + moveDir);
		}

		glm::vec2 rightThumb = m_controller->GetRightThumb();
		CalculateRotation(dt, rightThumb.x, -rightThumb.y);
	}
}

void FreeCamera::CalculateRotation(double dt, double xOffset, double yOffset)
{
	if (xOffset != 0)
	{
		glm::mat4 rot = glm::rotate((float)(dt * -xOffset), glm::vec3(0, 1, 0));
		SetTransform(GetTransform() * rot);
	}

	if (yOffset != 0)
	{
		glm::mat4 rot = glm::rotate((float)(dt * -yOffset), glm::vec3(1, 0, 0));

		SetTransform(GetTransform() * rot);
	}

	glm::mat4 oldTrans = GetTransform();

	glm::vec3 worldUp = glm::vec3(0, 1, 0);

	glm::mat4 trans;

	trans[0] = glm::normalize(glm::vec4(glm::cross(worldUp, oldTrans[2].xyz()), 0));

	trans[1] = glm::normalize(glm::vec4(glm::cross(oldTrans[2].xyz(), trans[0].xyz()), 0));

	trans[2] = glm::normalize(oldTrans[2]);

	trans[3] = oldTrans[3];

	SetTransform(trans);

}

