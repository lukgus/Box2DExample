/*
* RenderManager.cpp
*
* Implementation for the RenderManager.
* Responsible for handling rendering everything to the screen.
* Contributor: Lukas Gustafson
* January 26, 2016
*/

#include "RenderManager.h"

#include <sstream>

#include "ErrorLog.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "LManagers.h"


/*
* Default Constructor for cRenderManager
* Do nothing here.
*/
RenderManager::RenderManager(void)
{
	// do nothing.
}

/*
* Default Destructor for cRenderManager
* Do nothing here.
*/
RenderManager::~RenderManager(void)
{
	// do nothing.
}

/*
* StartUp
* StartUp for cRenderManager
* Initialize all variables here
*/
void RenderManager::StartUp(void)
{
	this->GetUniformLocations();
}

/*
* ShutDown
* ShutDown for cRenderManager
* Deallocate all memory, and handle garbage collection properly
*/
void RenderManager::ShutDown(void)
{
}

/*
* RenderScene
* Called to get all of the uniform locations from the shader manager
*/
void RenderManager::GetUniformLocations(void)
{
	GLuint id;

	// Simple Shader Uniform Locations
	gShaderManager.UseProgram("SimpleShader");
	id = gShaderManager.GetCurrentShaderID();
	CheckGLError();

	// Matrix information
	this->mModelMatrixUL = glGetUniformLocation(id, "ModelMatrix");
	this->mProjectionMatrixUL = glGetUniformLocation(id, "ProjectionMatrix");
	this->mViewMatrixUL = glGetUniformLocation(id, "ViewMatrix");

	// Colour
	this->mColourUL = glGetUniformLocation(id, "colour");

	// Eye position
	this->mEyeUL = glGetUniformLocation(id, "eye");
	CheckGLError();


	TempSetUp();

	gShaderManager.UseProgram("SimpleShader");
}

/* Update
*
*
*
*/
void RenderManager::Update(float dt)
{

}

void RenderManager::SetProjectionMatrix(const glm::mat4 &projection) {
	this->mProjectionMatrix = projection;
}


void RenderManager::SetViewMatrix(const glm::mat4 &view)
{
	this->mViewMatrix = view;
}

void RenderManager::RenderScene(void)
{

}

/*
* RenderGameObjects
* Called to prepare the Manager for rendering all of the objects
* Clear buffers, clear screen, set values.
*/
void RenderManager::RenderGameObjects(const std::vector<GameObject*> &gameObjects)
{
	gShaderManager.UseProgram("SimpleShader");
	TempSetUp();

	glUniformMatrix4fv(this->mViewMatrixUL, 1, GL_FALSE, glm::value_ptr(mViewMatrix));
	glUniformMatrix4fv(this->mProjectionMatrixUL, 1, GL_FALSE, glm::value_ptr(mProjectionMatrix));
	CheckGLError();

	glUniform3f(this->mEyeUL, mViewMatrix[3].x, mViewMatrix[3].y, mViewMatrix[3].z);
	CheckGLError();

	glm::mat4 WorldMatrix(1.0f);

	// Iterate through all of the objects to render them.
	for (unsigned int EntityIndex = 0; EntityIndex < gameObjects.size(); EntityIndex++)
	{
		this->RenderGameObject(gameObjects[EntityIndex], WorldMatrix, WorldMatrix);
	}
}

/*
* RenderObject
* Called to render a specific object using it's materials, textures, and mesh.
* @param gameObject - the game object to get the mesh, materials, and textures
* @param modelMatrixParent - the matrix to start calculations with for the translation matrix
* @param rotMatrixParent - the rotational matrix to start rotational calculation transformations
*/
void RenderManager::RenderGameObject(GameObject* pGameObject, const glm::mat4 &parentModelMatrix, const glm::mat4 &parentRotMatrix)
{
	glm::mat4 TranslationMatrix = glm::translate(parentModelMatrix, pGameObject->position);
	glm::mat4 RotationMatrix = glm::mat4_cast(pGameObject->orientation);
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(1.0f), pGameObject->scale);

	glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;

	// Check if there is a mesh to render
	if (pGameObject->MeshId != -1)
	{
		GLuint vbo;
		unsigned int numTriangles;

		gMeshManager.GetMeshDataById(pGameObject->MeshId, numTriangles, vbo);

		glUniform3f(this->mColourUL, pGameObject->colour.x, pGameObject->colour.y, pGameObject->colour.z);

		CheckGLError();
		glUniformMatrix4fv(this->mModelMatrixUL, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
		CheckGLError();

		glBindVertexArray(vbo);
		CheckGLError();

		glDrawElements(GL_TRIANGLES, numTriangles * 3, GL_UNSIGNED_INT, (GLvoid*)0);
		CheckGLError();
	}
}

void RenderManager::TempSetUp(void)
{
	// Set up a light
	glUniform3f(this->mColourUL, 1.0f, 1.0f, 1.0f);
	CheckGLError();

	return;
}
