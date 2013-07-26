#ifndef FRAME_H
#define FRAME_H

#include "CFL.h"
#include <vector>
#include <string>

using std::string;

class FrameListener;

/**
 * Class that is used to control the Frame used in the game.
 * 
 * @author	Braden Steffaniak
 * @since	Mar 9, 2013 at 3:18:44 AM
 * @since	v0.1
 * @version Mar 9, 2013 at 3:18:44 AM
 * @version	v0.2
 */
class Frame
{
private:
	static bool			created;
	static bool			vSync;
	static bool			initialized;

	static int			fps, targetFPS;
	static int			width, height;

	static Panel*		panel;

	static SDL_Window*	window;

	static ArrayList<Component*>		components;
	static ArrayList<FrameListener*>	frameListeners;

	static bool	intersectsMouse(Component*);

public:
	static void			init();
	static void			update();
	static void			setResizable(bool);
	static void			setVSyncEnabled(bool);
	static void			setFPS(int);
	static void			setTargetFPS(int);
	static void			setTitle(string);
	static void			setLocation(int, int);
	static void			quit();

	static bool			wasCreated();
	static bool			add(Component*);
	static bool			remove(Component*);
	static bool			isVSyncEnabled();
	static bool			addFrameListener(FrameListener*);
	static bool			removeFrameListener(FrameListener*);

	static int			getFPS();
	static int			getTargetFPS();
	static int			getX();
	static int			getY();
	static int			getWidth();
	static int			getHeight();

	static Panel*		getPanel();

	static string		getTitle();

	static SDL_Window*	create(int, int);
	static SDL_Window*	getWindow();
};

#endif