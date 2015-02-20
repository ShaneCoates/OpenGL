#ifndef SHADER_H
#define	SHADER_H

#include <string>
#include <map>
#include <glm/glm.hpp>

class Shader
{
public:
	static unsigned int LoadShader(std::string _strShaderName, const char* _szVertexShader, const char* _szPixelShader, const char* _szGeometryShader = nullptr, const char* _szTessellationControlShader = nullptr, const char* a_szTessellationEvaluationShader = nullptr);
	static unsigned int LoadShader(const char* _strName, unsigned int _uiType);
	static unsigned int CreateProgram(unsigned int vs, unsigned int tcs, unsigned int tes, unsigned int gs, unsigned int fs);
	static unsigned char* FileToBuffer(const char* _strName);

protected:
private:
};

#endif