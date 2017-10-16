#include <GL/freeglut.h>

/**
 * Resize
 * Called from GLUT when the window is resized by
 * the user, or full screen mode is toggled. Updates
 * the projection matrix.
 * @param width - the new width of the window
 * @param height - the new height of the window
 */
void Resize(int ww, int hh)
{
}

/**
 * Render
 */
void Render(void) 
{
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Call Render

	glutSwapBuffers();
}


int main(int argc, char **argv)
{
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Box2D Setup Example");

	// register callbacks
	glutDisplayFunc(Render);
	glutReshapeFunc(Resize);
	glutIdleFunc(Render);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}