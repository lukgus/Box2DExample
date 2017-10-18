#ifndef LOpenGL_HG
#define LOpenGL_HG

#pragma comment(lib, "glew.lib")
#ifdef NDEBUG
#pragma comment(lib, "freeglut.lib")
#else
#pragma comment(lib, "freeglutd.lib")
#endif

//#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/wglew.h>

#include <GL/freeglut.h>

#include "CheckGLError.h"

#endif
