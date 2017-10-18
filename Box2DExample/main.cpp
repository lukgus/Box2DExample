#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "PhysicsExampleScene.h"

#include "LManagers.h"

#include <GL/freeglut.h>
#include "LOpenGL.h"

PhysicsExampleScene mScene;

const float DEFAULT_DT = 0.016f;
const float Z_NEAR = 1.0f;
const float Z_FAR = 1000.0f;
float dt;
/**
 * Resize
 * Called from GLUT when the window is resized by
 * the user, or full screen mode is toggled. Updates
 * the projection matrix.
 * @param width - the new width of the window
 * @param height - the new height of the window
 */
void Resize(int width, int height)
{
	float ratio = float(width) / float(height);
	gRenderManager.SetProjectionMatrix(glm::perspective(glm::radians(45.0f), ratio, Z_NEAR, Z_FAR));
	glViewport(0, 0, width, height);
}

/**
 * Render
 */
void Render(void) 
{
	// TODO: Calculate delta time.
	dt = DEFAULT_DT;

	mScene.Update(dt);

	gPhysicsManager.Update(dt);

	gRenderManager.SetViewMatrix(
		glm::lookAt(
			glm::vec3(0.0f, 0.0f, 50.0f), 
			glm::vec3(0.0f, 0.0f, 0.0f), 
			glm::vec3(0.0f, 1.0f, 0.0f)
		)
	);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mScene.Render();

	glutSwapBuffers();
}

/**
 * init
 * Startup managers in proper order
 */
bool init()
{
	gMeshManager.StartUp();
	gPhysicsManager.StartUp();
	gShaderManager.StartUp();
	gRenderManager.StartUp();

	return mScene.Initialize();
}

/**
 * shutdown()
 * Shutdown managers in reverse order.
 */
void shutdown()
{
	mScene.Destroy();

	gRenderManager.ShutDown();
	gShaderManager.ShutDown();
	gPhysicsManager.Shutdown();
	gMeshManager.Shutdown();
}

/**
 * Main ¯\_(^v^)_/¯
 */
int main(int argc, char **argv)
{
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Box2D Setup Example");

	GLenum result = glewInit();
	if (result != GLEW_OK)
	{
		return 1;
	}
	// register callbacks
	glutDisplayFunc(Render);
	glutReshapeFunc(Resize);
	glutIdleFunc(Render);

	// TODO - Register keyboard callbacks

	if (!init())
	{
		printf("Failed to initialize the scene.\n");
		return 1;
	}

	// TODO - Make glut loop return on exit.
	glutMainLoop();

	shutdown();

	return 1;
}