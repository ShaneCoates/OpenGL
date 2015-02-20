//#include "Skybox.h"
//
//#include <stb_image.h>
//bool Skybox::Load()
//{
//    glGenTextures(1, &m_texture);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
//
//	unsigned char* imageData = stbi_load("data/something.png", &m_textureWidth, &m_textureHeight, &m_textureFormat, STBI_default);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textureWidth, m_textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
//
//
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//	stbi_image_free(imageData);
//
//
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
//	glEnableVertexAttribArray(1);
//	glEnableVertexAttribArray(2);
//
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4)));
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4) + (sizeof(glm::vec3))));
//
//
//
//    return true;
//}
//
//void Skybox::Bind(GLenum TextureUnit)
//{
//    glActiveTexture(TextureUnit);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
//}
//
//void Skybox::Render()
//{
//
//}