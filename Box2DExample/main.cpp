#include <iostream>

#include "PhysicsExampleScene.h"

#include "LManagers.h"

#include <GL/freeglut.h>

PhysicsExampleScene mScene;

const float DEFAULT_DT = 0.016f;
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
}

/**
 * Render
 */
void Render(void) 
{
	// TODO: Calculate delta time.
	dt = DEFAULT_DT;

	mScene.Update(dt);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Call Render
	// TODO: Call render.

	glutSwapBuffers();
}

/**
 * init
 * Startup managers in proper order
 */
bool init()
{
	gMeshManager.StartUp();
	gShaderManager.StartUp();

	return mScene.Initialize();
}

/**
 * shutdown()
 * Shutdown managers in reverse order.
 */
void shutdown()
{
	mScene.Destroy();

	gShaderManager.ShutDown();
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