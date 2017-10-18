/*
* ShaderManager implementation
*
* Contributors: Lukas Gustafson
* Date: January 26, 2016
*/

#include "ShaderManager.h"

#include <vector>
#include <fstream>

#include "ErrorLog.h"

#include "CheckGLError.h"

/*
* Default Constructor
* does nothing
*/
ShaderManager::ShaderManager(void)
{
	// do nothing.
	return;
}

/*
* Default Destructor
* does nothing
*/
ShaderManager::~ShaderManager(void)
{
	// do nothing.
	return;
}

/*
* StartUp
* Allocates and creates everything that the ShaderManager
* requires to run.
*/
void ShaderManager::StartUp(void)
{
	// These are engine defined shaders, and must always be here.
	SetBaseFilePath("assets/shaders/");

	CreateShaderProgramFromSourceFiles("SimpleShader", "SimpleShader.vertex.glsl", "SimpleShader.fragment.glsl");
	CreateShaderProgramFromSourceFiles("UserInterface", "UserInterface.vertex.glsl", "UserInterface.fragment.glsl");
	CreateShaderProgramFromSourceFiles("FreeType", "FreeType.vertex.glsl", "FreeType.fragment.glsl");

	return;
}

/*
* ShutDown
* Deletes everything that the ShaderManager is in charge of.
* Unlinkgs shaders from opengl, and destroys them as-well.
*/
void ShaderManager::ShutDown(void)
{
	for (std::map< std::string, ShaderProgram >::iterator it = m_map_ShaderPrograms.begin();
		it != m_map_ShaderPrograms.end(); ++it)
	{
		GLuint progId = it->second.id;
		GLuint vertId = it->second.vertexShader.id;
		GLuint fragId = it->second.fragmentShader.id;

		glDetachShader(progId, vertId);
		glDetachShader(progId, fragId);
		glDeleteShader(vertId);
		glDeleteShader(fragId);
		glDeleteProgram(progId);
	}
	return;
}

/*
* SetBaseFilePath
* Sets the base file path for finding shader files
* @param baseFilePath - the new base file path to search
*/
void ShaderManager::SetBaseFilePath(const std::string baseFilePath)
{
	m_BaseFilePath = baseFilePath;

	return;
}

/*
* GetBaseFilePath
* Gets the base file path for finding shader files
* @return - the current base file path to search
*/
std::string	ShaderManager::GetBaseFilePath(void)
{
	return m_BaseFilePath;
}

/*
* UseProgram
* Tells gl to use shader program by the provided id
* @param programID - The id of shader program to use
*/
void ShaderManager::UseProgram(std::string name)
{
	if (m_map_ShaderPrograms.find(name) == m_map_ShaderPrograms.end())
	{
		return;
	}

	ShaderProgram program = m_map_ShaderPrograms[name];

	CheckGLError();
	glUseProgram(program.id);
	CheckGLError();

	m_CurrentShaderId = program.id;

	return;
}

/*
* LinkProgram
* Calls glLinkProgram(programID) to link the program to use
* @param programID - The program id to link
*/
void ShaderManager::LinkProgram(GLuint programID)
{
	glLinkProgram(programID);
	CheckGLError();

	return;
}

/*
* LinkProgram
* Calls glLinkProgram(programID) to link the program to use
* @param programID - The program id to link
*/
void ShaderManager::UnloadProgram(std::string name)
{
	if (m_map_ShaderPrograms.find(name) == m_map_ShaderPrograms.end())
	{
		// this program isn't in our map. oops!
		return;
	}

	ShaderProgram theProgram = m_map_ShaderPrograms[name];
	Shader vertShader = theProgram.vertexShader;
	Shader fragShader = theProgram.fragmentShader;

	glDetachShader(theProgram.id, vertShader.id);
	glDetachShader(theProgram.id, fragShader.id);
	glDeleteShader(vertShader.id);
	glDeleteShader(fragShader.id);
	glDeleteProgram(theProgram.id);
	CheckGLError();

	return;
}

/*
* CreateShaderProgramFromSourceFiles
* Creates a shader program from the provided shader files
* @param vertexFilename - the filename of the vertex shader to load
* @param fragmentFilename - the filename of the fragment shader to load
* @return bool - TRUE if successfully loaded, FALSE otherwise
*/
bool ShaderManager::CreateShaderProgramFromSourceFiles(const std::string name, std::string vertexFilename, const std::string fragmentFilename)
{
	ShaderProgram program;
	Shader vertShader;
	Shader fragShader;

	program.id = glCreateProgram();
	program.name = name;

	vertShader.id = glCreateShader(GL_VERTEX_SHADER);
	fragShader.id = glCreateShader(GL_FRAGMENT_SHADER);

	vertShader.filename = vertexFilename;
	fragShader.filename = fragmentFilename;

	vertShader.source = LoadShaderFromFile(vertShader.filename);
	fragShader.source = LoadShaderFromFile(fragShader.filename);

	if (vertShader.source.empty() || fragShader.source.empty())
	{
		return false;
	}

	const GLchar* tmp;
	tmp = static_cast<const GLchar*>(vertShader.source.c_str());
	glShaderSource(vertShader.id, 1, (const GLchar**)&tmp, NULL);
	CheckGLError();

	tmp = static_cast<const GLchar*>(fragShader.source.c_str());
	glShaderSource(fragShader.id, 1, (const GLchar**)&tmp, NULL);
	CheckGLError();

	if (!CompileShader(&vertShader) || !CompileShader(&fragShader))
	{
		return false;
	}

	glAttachShader(program.id, vertShader.id);
	glAttachShader(program.id, fragShader.id);
	CheckGLError();

	glLinkProgram(program.id);
	CheckGLError();

	// Add our new shader to our map
	program.vertexShader = vertShader;
	program.fragmentShader = fragShader;
	m_map_ShaderPrograms[name] = program;

	return true;
}

/*
* LoadShaderFromFile
* Loads a shader from file into the provided shader pointer.
* @param filename - the filename of the shader to load
* @return - the source from the file
*/
std::string ShaderManager::LoadShaderFromFile(std::string filename)
{
	std::ifstream shaderFile(m_BaseFilePath + filename.c_str());

	if (!shaderFile.good())
	{
		ErrorLog::GetInstance()->WriteErrorMessageToLogFile("[ShaderManager] Error: Could not load shader " + filename);
		return std::string();
	}

	std::string stringBuffer(std::istreambuf_iterator<char>(shaderFile), (std::istreambuf_iterator<char>()));
	return stringBuffer;
}

/*
* CompileShader
* Compiles a shaders source code. Returns success or fail.
* @param shader - The shader to find source code to attempt to compile
* @return whether the compilation was successful or not
*/
bool ShaderManager::CompileShader(Shader* shader)
{
	glCompileShader(shader->id);
	CheckGLError();

	GLint result = 0xDEADBEEF;
	glGetShaderiv(shader->id, GL_COMPILE_STATUS, &result);
	CheckGLError();

	if (!result)
	{
		ErrorLog::GetInstance()->WriteErrorMessageToLogFile("[ShaderManager] " + shader->filename + " failed to compile: ");
		OutputShaderLog(shader->id);
		return false;
	}

	return true;
}

/*
* OutputShaderLog
* Displays the error from the shader.  Should send to the error log.
* @param shaderId - The shader id to fetch error information from and output
*/
void ShaderManager::OutputShaderLog(GLuint shaderId)
{
	std::vector<char> infoLog;
	GLint infoLogLength;

	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
	CheckGLError();

	infoLog.resize(infoLogLength);

	glGetShaderInfoLog(shaderId, infoLogLength, &infoLogLength, &infoLog[0]);
	CheckGLError();

	ErrorLog::GetInstance()->WriteErrorMessageToLogFile(std::string(infoLog.begin(), infoLog.end()));

	return;
}

/*
* GetCurrentShaderID
* Returns the last shader id that was called with UseProgram
* @return the current shader id
*/
GLuint ShaderManager::GetCurrentShaderID(void)
{
	return m_CurrentShaderId;
}

/*
* GetShaderIDFromName
* Returns the id of the shader by provided name
* @param name - the name of the shader to find
* @return - the id
*/
GLuint ShaderManager::GetShaderIDFromName(const std::string &name)
{
	if (m_map_ShaderPrograms.find(name) == m_map_ShaderPrograms.end())
	{
		return 0;
	}

	ShaderProgram program = m_map_ShaderPrograms[name];

	return program.id;
}
