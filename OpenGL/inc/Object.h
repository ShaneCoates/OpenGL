/* 
	Author: Shane Coates
	Description: Object class loaded from OBJ
*/

#ifndef OBJECT_H
#define	OBJECT_H

#include <glm\glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Camera;
class Object
{
public:
	Object(unsigned int _programID);
	Object(const char* _path, unsigned int _programID);
	~Object();

	void Init(unsigned int _programID);

	void Update(double dt);
	void Draw(Camera* _camera);

	void LoadFromObj(const char* _path);
	void LoadTexture(const char* _path);

	glm::vec3 GetLightPos() {return lightPos;}

	void Translate(glm::vec3 _translation);
	void SetScale(glm::vec3 _scale);
	void Rotate(glm::vec3 _facing);

	void SetLightSpeed(float _speed) {m_lightSpeed = _speed;}

	glm::vec3 GetPosition();
	glm::mat4 GetTransform() const			{return m_MVP;}

protected:
private:
	struct Vertex
	{
		glm::vec4 position;		
		glm::vec3 normal;
		glm::vec2 texCoord;
	};

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	unsigned int m_vertexCount;
	unsigned int m_indexCount;
	unsigned int m_programID;

	unsigned int m_drawMode;

	int m_textureWidth;
	int m_textureHeight;
	int m_textureFormat;

	unsigned int m_texture;

	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specColor;
	glm::vec3 lightPos;

	glm::mat4 m_MVP;

	float m_lightSpeed;
	double m_time;
	double m_rotationTimer;

	glm::vec3 m_scale;


};

#endif