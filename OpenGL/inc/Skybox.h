//#ifndef SKYBOX_H
//#define SKYBOX_H
//
//#include <gl_core_4_4.h>
//#include <GLFW/glfw3.h>
//
//#include <string>
//class Skybox
//{
//public: 
//	Skybox(const std::string& Directory,
//    const std::string& PosXFilename,
//    const std::string& NegXFilename,
//    const std::string& PosYFilename,
//    const std::string& NegYFilename,
//    const std::string& PosZFilename,
//    const std::string& NegZFilename);
//
//    ~Skybox();
//
//    bool Load();
//
//    void Bind(GLenum TextureUnit);
//
//	void Render();
//
//private:
//
//    std::string m_fileNames[6];
//
//	int m_textureWidth;
//	int m_textureHeight;
//	int m_textureFormat;
//
//	unsigned int m_texture;
//
//	unsigned int m_VAO;
//	unsigned int m_VBO;
//	unsigned int m_IBO;
//	unsigned int m_vertexCount;
//	unsigned int m_indexCount;
//	unsigned int m_programID;
//
//	
//};
//
//#endif