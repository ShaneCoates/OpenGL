//#include "Skybox.h"
//#include <gl_core_4_4.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include <sstream>
//#include <string>
//#include <fstream>
//#include <vector>
//#include <glm/glm.hpp>
//#include <glm/ext.hpp>
//#include "FreeCamera.h"
//#include "gizmos.h"
//
//#include <stb_image.h>
//
//Skybox::Skybox(unsigned int _programID)
//{
//	Init(_programID);
//}
//
//Skybox::Skybox(std::string _path, unsigned int _programID)
//{
//	Init(_programID);
//	std::string paths[6];
//	paths[0] = _path+"_ft";
//	paths[1] = _path+"_bk";
//	paths[2] = _path+"_lf";
//	paths[3] = _path+"_rt";
//	paths[4] = _path+"_up";
//	paths[5] = _path+"_dn";
//
//	LoadSkybox(paths);
//}
//
//void Skybox::Init(unsigned int _programID)
//{
//	m_indexCount = 0;
//	m_vertexCount = 0;
//	m_programID = _programID;
//}
//
//Skybox::~Skybox()
//{
//
//}
//
//void Skybox::Update(double dt)
//{
//
//}
//
//void Skybox::Draw(Camera* _camera)
//{
//	glUseProgram(m_programID);
//
//	GLint OldCullFaceMode;
//    glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
//    GLint OldDepthFuncMode;
//    glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);
//
//    glCullFace(GL_FRONT);
//    glDepthFunc(GL_LEQUAL);
//
//	unsigned int projectionUniform = glGetUniformLocation(m_programID, "projection");
//
//	glUniformMatrix4fv(projectionUniform, 1, false, glm::value_ptr(_camera->GetProjectionView()));
//	
//	for(unsigned int i = 0; i < 6; i++)
//	{
//		glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture[i]);
//	
//		glBindVertexArray(m_VAO);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(i * 6));
//	}
//	glBindVertexArray(0);
//	glUseProgram(0);
//	glCullFace(OldCullFaceMode); 
//    glDepthFunc(OldDepthFuncMode);
//}
//
//void Skybox::LoadFromObj(const char* _path)
//{
//
//
//	
//
//	std::string mtlPath;
//
//	std::ifstream in(_path, std::ios::in);
//	if (!in) { std::cerr << "Cannot open " << _path << std::endl; exit(1); }
//	
//	std::string line;
//	while (getline(in, line)) 
//	{
//		if (line.substr(0,2) == "v ") 
//		{
//			std::istringstream s(line.substr(2));
//			Vertex v; 
//			s >> v.position.x; 
//			s >> v.position.y; 
//			s >> v.position.z;
//
//			aoVerticies.push_back(v);
//			m_vertexCount++;
//		}  
//		else if (line.substr(0,2) == "f ") 
//		{
//			std::istringstream s(line.substr(2));
//			GLushort a,b,c;
//
//			s >> a;	s >> b;	s >> c;
//			a--; b--; c--;
//			auiIndicies.push_back(a); auiIndicies.push_back(b); auiIndicies.push_back(c);
//
//			m_indexCount+= 3;
//		}
//		else if (line[0] == '#') { /* ignoring this line */ }
//		else { /* ignoring this line */ }
//	}
//
//
//	LoadTexture(mtlPath.c_str());
//}
//
//void Skybox::LoadSkybox(std::string _path[6])
//{
//	glGenBuffers(1, &m_VBO);	
//	glGenBuffers(1, &m_IBO);
//	
//	glGenVertexArrays(1, &m_VAO);
//	
//	glBindVertexArray(m_VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
//
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
//	
//	std::vector<Vertex> aoVerticies;
//	std::vector<unsigned int> auiIndicies;
//
//	for(int i = 0; i < 6; i++)
//	{	
//		unsigned char* imageData = stbi_load(_path[i].c_str(), &m_textureWidth, &m_textureHeight, &m_textureFormat, STBI_default);
//
//		glGenTextures(1, &m_texture[i]);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture[i]);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textureWidth, m_textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//		stbi_image_free(imageData);
//	}
//
//	glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(Vertex), &aoVerticies[0], GL_STATIC_DRAW);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(unsigned int), &auiIndicies[0], GL_STATIC_DRAW);
//}
