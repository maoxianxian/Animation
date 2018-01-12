////////////////////////////////////////
// Core.h
////////////////////////////////////////



// This file just has a bunch of common stuff used by all objects. It mainly just
// includes GL and some other standard headers.

// Set up GLM
//#include "glm/glm.hpp"
//#include "glm/gtx/transform.hpp"
#define GLFW_INCLUDE_GLEXT
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
// Set up GLEW
//#define GLEW_STATIC
//#pragma comment(lib, "glew32s.lib")
//#include "GL/glew.h"

// Set up GLUT
//#include "GL/glut.h"

// Types
typedef unsigned int uint;

// STD library
#include <vector>
#include <ctype.h>
