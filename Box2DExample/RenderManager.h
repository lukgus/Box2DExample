/*
* RenderManager.h
*
* Header file for the cRenderManager.
* Responsible for handling rendering everything to the screen.
* Contributor: Lukas Gustafson
* January 26, 2016
*/

#ifndef RENDER_MANAGER_HG
#define RENDER_MANAGER_HG

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "LOpenGL.h"

#include "CheckGLError.h"

class GameObject;

class RenderManager
{
public:
	RenderManager(void);
	virtual ~RenderManager(void);
	void StartUp(void);
	void ShutDown(void);
	void TempSetUp(void);

	void Update(float dt);

	void SetProjectionMatrix(const glm::mat4 &projection);
	void SetViewMatrix(const glm::mat4 &view);

	void RenderScene(void);
	void RenderGameObjects(const std::vector<GameObject*> &objects);
private:
	void GetUniformLocations(void);

	void RenderGameObject(GameObject*, const glm::mat4 &parentModelMatrix, const glm::mat4 &parentRotMatrix);

	glm::mat4 mViewMatrix;
	glm::mat4 mProjectionMatrix;

	// Matrices	
	GLuint mModelMatrixUL;
	GLuint mProjectionMatrixUL;
	GLuint mViewMatrixUL;

	// Plain Colour or Debug
	GLuint mColourUL;

	// Eye
	GLuint mEyeUL;
};

#endif
