/*
	Author: Shane Coates
	Description: Camera class

*/

#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm\ext.hpp>


class Camera
{
public:

	Camera();
	Camera(glm::vec3 _position);
	Camera(glm::mat4 _transform); 

	virtual void Update(double _deltaTime) = 0;

	void SetTransform(glm::mat4 _transform);
	const glm::mat4 GetTransform() const	{return m_worldTransform;}

	void SetPosition(glm::vec3 _position);
	glm::vec3 GetPosition() const			{return m_worldTransform[3].xyz();}

	void SetLookAt(glm::vec3 _to, glm::vec3 _up);
	void SetLookAt(glm::vec3 _from, glm::vec3 _to, glm::vec3 _up);	
	
	void SetPerspective(float _fieldOfView, float _aspectRation, float _near, float _far);

	const glm::mat4& GetProjection()		const { return m_projectionTransform; }
	const glm::mat4& GetView()				const { return m_viewTransform; }
	const glm::mat4& GetProjectionView()	const { return m_projectionViewTransform; }

	void Translate(glm::vec3 _translation)	{m_worldTransform *= glm::translate(_translation);}

protected:	
	glm::mat4 m_worldTransform;	
	void UpdateProjectionViewTransform();

private:


	glm::mat4 m_viewTransform;
	glm::mat4 m_projectionTransform;
	glm::mat4 m_projectionViewTransform;
	
};

#endif