#ifndef CFL_H
#define CFL_H

#define byte unsigned char

//#define GL_GLEXT_PROTOTYPES

#include <iostream>

using std::cout;
using std::endl;

#if defined(__APPLE__)
	#include <SDL2/SDL.h>
	#include <GLUT/GLUT.h>
#elif defined(_WIN32) || defined(_WIN64)
	#include "SDL.h"
	#include "GL/glew.h"
#endif

#include "Texture.h"
#include "Buffer.h"
#include "Bundle.h"
#include "ArrayList.h"
#include "Stack.h"
#include "Component.h"
#include "Frame.h"
#include "Panel.h"
#include "GL.h"
#include "Color.h"
#include "Event.h"
#include "FrameEvent.h"
#include "MouseEvent.h"
#include "FrameListener.h"
#include "MouseListener.h"
#include "Mouse.h"
#include "Time.h"
#include "ResourceLocator.h"
#include "Intersects.h"

#endif