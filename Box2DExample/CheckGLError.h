/* CheckGLError
*
* This function is used to see if there has been an error
* with an opengl call that was called between the last
* call to this function, and the current call.  It is
* suggested to call this function after any major OpenGL
* call
*
* Seperation exist so you are able to move declaration
* into a seperate file from the implementation easily.
*
* Author: Lukas Gustafson
* Date: January 27, 2016
*/
#ifndef CHECK_GL_ERROR_HG
#define CHECK_GL_ERROR_HG

void _CheckGLError(const char* file, int line);

#define CheckGLError() _CheckGLError(__FILE__, __LINE__)

#endif
