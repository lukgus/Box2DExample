/*
* cShaderManager.h
*
* Header file for the ShaderManager.
* Responsible for handling shader programs.  Linking programs,
* shaders.  Passing information to the graphics card, and handling
* deallocation when needed.
* Contributor: Lukas Gustafson
* January 26, 2016
*/

#ifndef ShaderManager_HG
#define ShaderManager_HG

#include <map>
#include <string>

#include "LOpenGL.h"

/*
* cShader
* information for holding shader information.
*/
class Shader
{
public:
	std::string filename;
	std::string source;
	bool bIsCompiled;
	GLuint id;
};

/*
* cShaderProgram
*
*/
class ShaderProgram
{
public:
	std::string name;
	Shader vertexShader;
	Shader fragmentShader;
	GLuint id;
};

class ShaderManager
{
public:
	ShaderManager(void);
	virtual ~ShaderManager(void);

	void StartUp(void);
	void ShutDown(void);

	void SetBaseFilePath(const std::string baseFilePath);
	std::string	GetBaseFilePath(void);

	void UseProgram(std::string name);
	void LinkProgram(GLuint programID);
	void UnloadProgram(std::string name);

	GLuint GetCurrentShaderID(void);
	GLuint GetShaderIDFromName(const std::string &name);

	GLuint CreateShaderProgramFromSourceFiles(const std::string name, std::string vertexFilename, const std::string fragmentFilename);
private:
	std::string LoadShaderFromFile(std::string filename);
	bool CompileShader(Shader* shader);
	void OutputShaderLog(GLuint shaderId);

	std::string m_BaseFilePath;		// where all of the shader files are located
	GLuint m_CurrentShaderId;		// the current shader id to use when rendering
	std::map<std::string, ShaderProgram> m_map_ShaderPrograms;
};

#endif
