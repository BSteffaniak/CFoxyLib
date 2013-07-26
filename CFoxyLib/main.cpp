#include "CFL.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char* argv[])
{
	
	//SDL_Init(SDL_INIT_VIDEO);
	// Now you can set up your SDL_Window* with SDL_CreateWindow().
	// and change the display mode with SDL_SetWindowDisplayMode().
	SDL_Window* window = Frame::create(800, 600);
	
	Frame::setTitle("test");
	
	cout << Frame::getTitle() << endl;
	
	//	SDL_CreateWindow
	//(
	//	"SDL2 Window",
	//	SDL_WINDOWPOS_UNDEFINED,
	//	SDL_WINDOWPOS_UNDEFINED,
	//	closest.w,
	//	closest.h,
	//	SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	//);
	
	//if(SDL_SetWindowDisplayMode(window, &closest))
	//{
	//	// ... handle error, clean up and exit
	//}
	
	// Create an OpenGL context associated with the window.
	//SDL_GLContext context = SDL_GL_CreateContext(Frame::getWindow());
	
	// Now, regular OpenGL functions ...
	glMatrixMode(GL_PROJECTION | GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-320, 320, 240, -240, 0, 1);
	
	float x = 50;
	float y = -20;
	
	int dfps = 0;
	int fps  = 0;
	
	Frame::setVSyncEnabled(true);
	
	SDL_Event e;
	
	Bundle bundle(3 * 2, 2, true, false);
	
	float* verts = GL::genRectVerts(-50, -50, 100, 100);
	bundle.addVertices(verts, 3 * 2 * 2);
	
	Texture t = GL::WHITE;// Texture();
	
	float *textures = GL::genRectTextures(&t);
	//float textures[3 * 2 * 2];
	bundle.addTextures(textures, 3 * 2 * 2);
	
	long start = Time::currentTimeMillis();
	
	// Wait for a keypress, then exit the program
	do
	{
		SDL_PollEvent(&e);
		
		glClearColor(0, 0, 0, 1); // Draw with OpenGL.
		
		glClear(GL_COLOR_BUFFER_BIT);
		//glRotatef(10.0, 0.0, 0.0, 1.0);
		
		glColor4b(255, 255, 255, 255);
		
		//GL::viewOrtho(800, 600);
		
		
		// Note that the glBegin() ... glEnd() OpenGL style used below is actually
		// obsolete, but it will do for example purposes. For more information, see
		// SDL_GL_GetProcAddress() or find an OpenGL extension loading library.
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0); glVertex2f(x,        y + 90.0);
		glColor3f(0.0, 1.0, 0.0); glVertex2f(x + 90.0, y - 90.0);
		glColor3f(0.0, 0.0, 1.0); glVertex2f(x - 90.0, y - 90.0);
		glEnd();
		
		bundle.render(GL::TRIANGLES, &t);
		
		SDL_GL_SwapWindow(window); // Swap the window/buffer to display the result.
		//SDL_Delay(10); // Pause briefly before moving on to the next cycle.
		
		long current = Time::currentTimeMillis();
		
		dfps++;
		
		if (current >= start + 1000)
		{
			fps   = dfps;
			
			dfps  = 0;
			
			start = current;
			
			cout << fps << endl;
		}
	}
	while (e.type != SDL_KEYDOWN && e.type != SDL_QUIT);
	
	GL::quit();
	
	//cin.get();
	
	return 0;
}

//#include "SDL.h"
//#include "SDL_opengl.h"
//#include <cstdio>
//
//int main(int argc, char* argv[])
//{
//	SDL_Init(SDL_INIT_VIDEO);
//
//	// Declare structures to be filled in.
//	SDL_DisplayMode target, closest;
//
//	// Set the target properties.
//	target.w = 600; // weird request, but ok
//	target.h = 500;
//	target.format = 0; // don't care
//	target.refresh_rate = 0; // don't care
//	target.driverdata = 0; // initialize to 0
//
//	printf("Requesting: \t%dx%dpx @ %dhz \n", target.w, target.h, target.refresh_rate);
//
//	// Pass the display mode structures by reference to SDL_GetClosestDisplay
//	// and check that the result is not a null pointer.
//	if(SDL_GetClosestDisplayMode(0, &target, &closest)==NULL)
//	{
//		// If the returned pointer is null ...
//		printf("\nNo match was found!\n\n");
//		SDL_Quit();
//
//		return 1;
//	}
//	// Otherwise, a display mode close to the target is available.
//	// Access the SDL_DisplayMode structure to see what was received.
//	printf(" Received: \t%dx%dpx @ %dhz \n", closest.w, closest.h, closest.refresh_rate);
//
//	// Now you can set up your SDL_Window* with SDL_CreateWindow()
//	// and change the display mode with SDL_SetWindowDisplayMode().
//	SDL_Window* window = SDL_CreateWindow
//	(
//		"SDL2 Window",
//		SDL_WINDOWPOS_UNDEFINED,
//		SDL_WINDOWPOS_UNDEFINED,
//		closest.w,
//		closest.h,
//		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
//	);
//
//	if(SDL_SetWindowDisplayMode(window, &closest))
//	{
//		// ... handle error, clean up and exit
//	}
//
//	// Create an OpenGL context associated with the window.
//	SDL_GLContext glcontext = SDL_GL_CreateContext(window);
//
//	// Now, regular OpenGL functions ...
//	glMatrixMode(GL_PROJECTION|GL_MODELVIEW);
//	glLoadIdentity();
//	glOrtho(-320, 320, 240, -240, 0, 1);
//
//	// ... can be used alongside SDL2.
//	SDL_Event e;
//
//	SDL_PollEvent(&e);
//
//	float x = 0.0, y = 30.0;
//
//	while(e.type !=SDL_KEYDOWN && e.type != SDL_QUIT)
//	{
//		// Enter main loop.
//		SDL_PollEvent(&e); // Check for events.
//
//		glClearColor(0, 0, 0, 1); // Draw with OpenGL.
//		glClear(GL_COLOR_BUFFER_BIT);
//		glRotatef(10.0, 0.0, 0.0, 1.0);
//		// Note that the glBegin() ... glEnd() OpenGL style used below is actually
//		// obsolete, but it will do for example purposes. For more information, see
//		// SDL_GL_GetProcAddress() or find an OpenGL extension loading library.
//		glBegin(GL_TRIANGLES);
//			glColor3f(1.0, 0.0, 0.0); glVertex2f(x,        y + 90.0);
//			glColor3f(0.0, 1.0, 0.0); glVertex2f(x + 90.0, y - 90.0);
//			glColor3f(0.0, 0.0, 1.0); glVertex2f(x - 90.0, y - 90.0);
//		glEnd();
//
//		SDL_GL_SwapWindow(window); // Swap the window/buffer to display the result.
//		SDL_Delay(10); // Pause briefly before moving on to the next cycle.
//	}
//
//	// Once finished with OpenGL functions, the SDL_GLContext can be deleted.
//	SDL_GL_DeleteContext(glcontext);
//
//	SDL_DestroyWindow(window);
//	SDL_Quit();
//
//	return 0;
//}


//#include <iostream>
//
//int main(int argc, char* argv[])
//{
//	SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2
//
//	SDL_Window *window; // Declare a pointer to an SDL_Window
//
//	// Create an application window with the following settings:
//	window = SDL_CreateWindow
//	(
//		"An SDL2 window", // const char* title
//		SDL_WINDOWPOS_UNDEFINED, // int x: initial x position
//		SDL_WINDOWPOS_UNDEFINED, // int y: initial y position
//		640, // int w: width, in pixels
//		480, // int h: height, in pixels
//		SDL_WINDOW_SHOWN // Uint32 flags: window options, see docs
//	);
//
//	// Check that the window was successfully made
//	if(window==NULL)
//	{
//		// In the event that the window could not be made...
//		std::cout << "Could not create window: " << SDL_GetError() << '\n';
//		SDL_Quit();
//		return 1;
//	}
//
//	// The window is open: enter program loop (see SDL_PollEvent)
//	//SDL_Delay(3000); // Wait for 3000 milliseconds, for example
//
//	std::cin.get();
//
//	// Close and destroy the window
//	SDL_DestroyWindow(window);
//
//	// Clean up SDL2 and exit the program
//	SDL_Quit();
//	return 0;
//}

//#include "SDL.h"
//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//
//int main(int argc, char** argvs)
//{
//	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
//	{
//		std::cout << "It worked!";
//	}
//	else
//	{
//		std::cout << "Didn't work...";
//	}
//
//	std::cout << std::endl;
//
//    /* Information about the current video settings. */
//    const SDL_VideoInfo* info = NULL;
//
//    /* Let's get some video information. */
//    info = SDL_GetVideoInfo();
//
//	int width = 0;
//	int height = 0;
//	int bpp = 0;
//	int flags = 0;
//
//    /*
//     * Set our width/height to 640/480 (you would
//     * of course let the user decide this in a normal
//     * app). We get the bpp we will request from
//     * the display. On X11, VidMode can't change
//     * resolution, so this is probably being overly
//     * safe. Under Win32, ChangeDisplaySettings
//     * can change the bpp.
//     */
//    width = 640;
//    height = 480;
//    bpp = info->vfmt->BitsPerPixel;
//
//    /*
//     * Now, we want to setup our requested
//     * window attributes for our OpenGL window.
//     * We want *at least* 5 bits of red, green
//     * and blue. We also want at least a 16-bit
//     * depth buffer.
//     *
//     * The last thing we do is request a double
//     * buffered window. '1' turns on double
//     * buffering, '0' turns it off.
//     *
//     * Note that we do not use SDL_DOUBLEBUF in
//     * the flags to SDL_SetVideoMode. That does
//     * not affect the GL attribute state, only
//     * the standard 2D blitting setup.
//     */
//    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
//    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
//    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
//    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
//    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
//
//    /*
//     * We want to request that SDL provide us
//     * with an OpenGL window, in a fullscreen
//     * video mode.
//     *
//     * EXERCISE:
//     * Make starting windowed an option, and
//     * handle the resize events properly with
//     * glViewport.
//     */
//    flags = SDL_OPENGL | SDL_FULLSCREEN;
//
//	if (SDL_SetVideoMode(width, height, bpp, flags) == 0)
//	{
//
//	}
//
//	SDL_Quit();
//
//	std::cin.get();
//	
//	return 0;
//}