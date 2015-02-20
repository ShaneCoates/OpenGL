///* 
//	Author: Shane Coates
//	Description: Skybox class loaded from OBJ
//*/
//
//#ifndef SKYBOX_H
//#define	SKYBOX_H
//
//#include <glm\glm.hpp>
//
//class Camera;
//class Skybox
//{
//public:
//	Skybox(unsigned int _programID);
//	Skybox(std::string _path, unsigned int _programID);
//	~Skybox();
//
//	void Init(unsigned int _programID);
//
//	void Update(double dt);
//	void Draw(Camera* _camera);
//
//	void LoadSkybox(std::string _path[6]);
//
//protected:
//private:
//	struct Vertex
//	{
//		glm::vec3 position;
//	};
//
//
//	unsigned int m_VAO;
//	unsigned int m_VBO;
//	unsigned int m_IBO;
//	unsigned int m_vertexCount;
//	unsigned int m_indexCount;
//	unsigned int m_programID;
//
//	int m_textureWidth;
//	int m_textureHeight;
//	int m_textureFormat;
//
//	unsigned int m_texture[6];
//};
//
//#endif