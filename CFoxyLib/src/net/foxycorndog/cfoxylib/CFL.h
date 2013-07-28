#ifndef CFL_H
#define CFL_H

#define fbyte unsigned char

#include <string>
#include <vector>
#include <iostream>

using std::string;

using std::vector;

using std::cout;
using std::endl;

/*
 Operating System Definition names.
 
 _WIN32
 _WIN64
 __unix
 __unix__
 __APPLE__
 __MACH__
 __linux__
 __FreeBSD__
 */

#if defined(__APPLE__)
	#define MACOSX
	#include <SDL2/SDL.h>
	#include <GLUT/GLUT.h>
#elif defined(_WIN32) || defined(_WIN64)
	#define WINDOWS
	#include "SDL.h"
	#include "GL/glew.h"
#endif

#include "util/lodepng.h"
#include "util/FoxyImage.h"
#include "opengl/texture/Texture.h"
#include "opengl/texture/SpriteSheet.h"
#include "opengl/bundle/Buffer.h"
#include "opengl/bundle/Bundle.h"
#include "ArrayList.h"
#include "Stack.h"
#include "components/Component.h"
#include "Frame.h"
#include "components/Panel.h"
#include "opengl/GL.h"
#include "Color.h"
#include "events/Event.h"
#include "events/FrameEvent.h"
#include "events/MouseEvent.h"
#include "events/FrameListener.h"
#include "events/MouseListener.h"
#include "input/Mouse.h"
#include "util/FoxyTime.h"
#include "util/ResourceLocator.h"
#include "util/Intersects.h"

#endif