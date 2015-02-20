#include "Camera.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using namespace glm;

Camera::Camera()
{
	m_worldTransform = mat4(1);
	UpdateProjectionViewTransform();
}

Camera::Camera(vec3 _position)
{
	m_worldTransform = mat4(1);
	m_worldTransform[3] = vec4(_position, 1);
	UpdateProjectionViewTransform();
}

Camera::Camera(mat4 _transform) : m_worldTransform(_transform)
{
	UpdateProjectionViewTransform();
}

void Camera::SetTransform(mat4 _transform)
{
	m_worldTransform = _transform;
	UpdateProjectionViewTransform();
}

void Camera::SetPosition(glm::vec3 _position)
{
	m_worldTransform[3] = glm::vec4(_position, 1);
	UpdateProjectionViewTransform();
}

void Camera::SetLookAt(glm::vec3 _to, glm::vec3 _up)
{
	glm::vec4 vLocation = m_worldTransform[3];
	m_worldTransform = glm::inverse(glm::lookAt(vLocation.xyz(), _to, _up));
	UpdateProjectionViewTransform();
}

void Camera::SetLookAt(glm::vec3 _from, glm::vec3 _to, glm::vec3 _up)
{
	m_worldTransform = glm::inverse(glm::lookAt(_from, _to, _up));
	UpdateProjectionViewTransform();
}

void Camera::SetPerspective(float _fieldOfView, float _aspectRation, float _near, float _far)
{
	m_projectionTransform = glm::perspective(_fieldOfView, _aspectRation, _near, _far);
	
	UpdateProjectionViewTransform();
}

void Camera::UpdateProjectionViewTransform()
{
	m_viewTransform = glm::inverse(m_worldTransform);
	m_projectionViewTransform = m_projectionTransform * m_viewTransform;
}