#include "CFL.h"
#include <vector>
#include <stdexcept>

using std::vector;
using std::invalid_argument;

bool		Frame::created;
bool		Frame::vSync;
bool		Frame::initialized;

int			Frame::fps, Frame::targetFPS;
int			Frame::width, Frame::height;

Panel*		Frame::panel;

SDL_Window*	Frame::window;

ArrayList<Component*>		Frame::components;
ArrayList<FrameListener*>	Frame::frameListeners;

void Frame::init()
{
	if (initialized)
	{
		return;
	}

	SDL_Init(SDL_INIT_VIDEO);
	
	panel = new Panel(NULL);
	panel->setLocation(0, 0);
	panel->setSize((float)width, (float)height);
	
	initialized = true;
}

/**
 * Returns whether or not the Frame has been created.
 * 
 * @return Whether or not the Frame has been created.
 */
bool Frame::wasCreated()
{
	return created;
}

/**
 * Method to create a Frame the specified size.
 * 
 * @param width The width of the Frame to create.
 * @param height The height of the Frame to create.
 */
SDL_Window* Frame::create(int width, int height)
{
	if (width <= 0 || height <= 0)
	{
		throw invalid_argument("The width and height of the Frame must both be > 0");
	}

	init();
	
	//ResourceLocator::locateNatives();
	
	window = SDL_CreateWindow
	(
		"",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);

	GL::init();
	
	setVSyncEnabled(false);
	
	//Mouse::addMouseListener(new MouseListener()
	//{
	//	public void mouseUp(MouseEvent event)
	//	{
	//		
	//	}
	//	
	//	public void mouseReleased(MouseEvent event)
	//	{
	//		for (int i = 0; i < components.size(); i++)
	//		{
	//			Component* comp = components.get(i);
	//			
	//			if (comp.isDisposed())
	//			{
	//				continue;
	//			}
	//			
	//			bool intersects = intersectsMouse(comp);
	//			
	//			if (comp instanceof Button)
	//			{
	//				Button button = (Button)comp;
	//				
	//				if (intersects && button.isEnabled())
	//				{
	//					ArrayList<ButtonListener> buttonListeners = button.getButtonListeners();
	//					
	//					for (int n = buttonListeners.size() - 1; n >= 0; n--)
	//					{
	//						ButtonListener listener = buttonListeners.get(n);
	//						
	//						ButtonEvent buttonEvent = new ButtonEvent(button, event.getButton());
	//						
	//						listener.buttonReleased(buttonEvent);
	//					}
	//				}
	//			}
	//		}
	//	}
	//	
	//	public void mousePressed(MouseEvent event)
	//	{
	//		bool focused = false;
	//		
	//		for (int i = 0; i < components.size(); i++)
	//		{
	//			Component comp = components.get(i);
	//			
	//			comp.setFocused(false);
	//			
	//			if (comp.isDisposed())
	//			{
	//				continue;
	//			}

	//			bool intersects = intersectsMouse(comp);
	//			
	//			if (intersects && comp.isEnabled())
	//			{
	//				if (comp instanceof Button)
	//				{
	//					Button button = (Button)comp;
	//					
	//					if (button.isHovered())
	//					{
	//						ArrayList<ButtonListener> buttonListeners = button.getButtonListeners();
	//						
	//						for (int n = buttonListeners.size() - 1; n >= 0; n--)
	//						{
	//							ButtonListener listener = buttonListeners.get(n);
	//							
	//							ButtonEvent buttonEvent = new ButtonEvent(button, event.getButton());
	//							
	//							listener.buttonPressed(buttonEvent);
	//						}
	//					}
	//				}
	//				
	//				focused = true;
	//				
	//				comp.setFocused(true);
	//			}
	//		}
	//	}
	//	
	//	public void mouseMoved(MouseEvent event)
	//	{
	//		for (int i = 0; i < components.size(); i++)
	//		{
	//			Component comp = components.get(i);
	//			
	//			if (comp.isDisposed())
	//			{
	//				continue;
	//			}
	//			
	//			bool intersects = intersectsMouse(comp);
	//			
	//			if (comp instanceof Button)
	//			{
	//				Button button = (Button)comp;
	//				
	//				if (button.isEnabled())
	//				{
	//					ArrayList<ButtonListener> buttonListeners = button.getButtonListeners();
	//					
	//					for (int n = buttonListeners.size() - 1; n >= 0; n--)
	//					{
	//						ButtonListener listener = buttonListeners.get(n);
	//						
	//						ButtonEvent buttonEvent = new ButtonEvent(button, event.getButton());
	//						
	//						if (intersects && !button.isHovered())
	//						{
	//							listener.buttonHovered(buttonEvent);
	//						}
	//						else if (!intersects && button.isHovered())
	//						{
	//							listener.buttonUnHovered(buttonEvent);
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//	
	//	public void mouseDown(MouseEvent event)
	//	{
	//		for (int i = 0; i < components.size(); i++)
	//		{
	//			Component comp = components.get(i);
	//			
	//			if (comp.isDisposed())
	//			{
	//				continue;
	//			}
	//			
	//			bool intersects = intersectsMouse(comp);
	//			
	//			if (comp instanceof Button)
	//			{
	//				Button button = (Button)comp;
	//				
	//				if (button.isEnabled())
	//				{
	//					ArrayList<ButtonListener> buttonListeners = button.getButtonListeners();
	//					
	//					for (int n = buttonListeners.size() - 1; n >= 0; n--)
	//					{
	//						ButtonListener listener = buttonListeners.get(n);
	//						
	//						ButtonEvent buttonEvent = new ButtonEvent(button, event.getButton());
	//						
	//						if (intersects)
	//						{
	//							listener.buttonDown(buttonEvent);
	//						}
	//						else if (!intersects)
	//						{
	//							listener.buttonUp(buttonEvent);
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}

	//	public void mouseEntered(MouseEvent event)
	//	{
	//		
	//	}

	//	public void mouseExited(MouseEvent event)
	//	{
	//		for (int i = 0; i < components.size(); i++)
	//		{
	//			Component comp = components.get(i);
	//			
	//			if (comp.isDisposed())
	//			{
	//				continue;
	//			}
	//			
	//			bool intersects = intersectsMouse(comp);
	//			
	//			if (comp instanceof Button)
	//			{
	//				Button button = (Button)comp;
	//				
	//				if (button.isHovered() && button.isEnabled())
	//				{
	//					ArrayList<ButtonListener> buttonListeners = button.getButtonListeners();
	//					
	//					for (int n = buttonListeners.size() - 1; n >= 0; n--)
	//					{
	//						ButtonListener listener = buttonListeners.get(n);
	//						
	//						ButtonEvent buttonEvent = new ButtonEvent(button, event.getButton());
	//						
	//						listener.buttonUnHovered(buttonEvent);
	//					}
	//				}
	//			}
	//		}
	//	}
	//});
	
	created = true;

	return window;
} 

/**
 * Check whether the specified Component is located under the Mouse
 * cursor.
 * 
 * @param comp The Component to check if it is under the Mouse or not.
 * @return Whether the Component is under the Mouse cursor or not.
 */
bool Frame::intersectsMouse(Component* comp)
{
	float trans[3];
	
	GL::getAmountTranslated(trans);
	
	return comp->isVisible() && Mouse::isInFrame() &&
			Intersects::rectanglesf(comp->getDisplayX(), comp->getDisplayY(),
					comp->getWidth() * comp->getFullScale(), comp->getHeight() * comp->getFullScale(),
					(float)Mouse::getX(), (float)Mouse::getY(), 1, 1);
}

/**
 * Updates the Frame and its Components. Called every frame.
 */
void Frame::update()
{
	int w;
	int h;

	SDL_GetWindowSize(window, &w, &h);

	if (width != w || height != h)
	{
		width  = w;
		height = h;
		
		for (int i = frameListeners.size() - 1; i >= 0; i--)
		{
			FrameListener* listener = frameListeners.get(i);
			
			FrameEvent* event = &FrameEvent();
			
			listener->frameResized(event);
		}
		
		panel->setSize((float)width, (float)height);
	}
}

/**
 * Get the main Frame Panel that holds all of the Components in the
 * Frame.
 * 
 * @return The main Frame Panel instance.
 */
Panel* Frame::getPanel()
{
	return panel;
}

/**
 * Add a Component to the Frame. Lets the listeners be active.
 * 
 * @param component The Component to add.
 * @return Whether it was added successfully or not.
 */
bool Frame::add(Component* component)
{
	components.add(component);

	return true;
}

/**
 * Remove a Component from the Frame.
 * 
 * @param component The Component to remove.
 * @return Whether it was removed successfully or not.
 */
bool Frame::remove(Component* component)
{
	components.removeElement(component);

	return true;
}

/**
 * Set whether the Frame should be resizable.
 * 
 * @param resizable Whether the Frame should be resizable.
 */
void Frame::setResizable(bool resizable)
{
	//bool r = &SDL_getwindowre

	//if (resizable != r)
	//{
	//	SDL_setwindow
	//}
}

/**
 * Returns whether the Frame has Vertical Synchronization enabled or
 * not.
 * 
 * @return Whether the Frame has Vertical Synchronization enabled or
 * 		not.
 */
bool Frame::isVSyncEnabled()
{
	return SDL_GL_GetSwapInterval() == 1;
}

/**
 * Limit the frame rate to the monitors capable speed to reduce
 * the tearing of the frames. Map slow down the performance, but
 * in most cases looks better.
 * 
 * @param vSync Whether or not to enable or disable vertical
 * 		synchronization.
 */
void Frame::setVSyncEnabled(bool vSync)
{
	if (vSync)
	{
		SDL_GL_SetSwapInterval(1);
	}
	else
	{
		SDL_GL_SetSwapInterval(0);
	}
}

/**
 * Get the amount of frames that the Frame gets per second. Each
 * frame includes the clearing of the screen, calls to the loop and
 * render methods, and other methods too.
 * 
 * @return The most recent amount of frames per second.
 */
int Frame::getFPS()
{
	return fps;
}

/**
 * Set the value that is used to display the frames per second.
 * 
 * @param fps The value to set it to.
 */
void Frame::setFPS(int fps)
{
	Frame::fps = fps;
}

/**
 * Get the value that is set for the target FPS. The target FPS
 * is used to create a goal for the Frame to try to reach whenever
 * looping through the main loop. The program tries to accomplish
 * the specified amount of frames per second each second.
 * 
 * @return The target frames per second each second.
 */
int Frame::getTargetFPS()
{
	return targetFPS;
}

/**
 * Set the value that is set for the target FPS. The target FPS
 * is used to create a goal for the Frame to try to reach whenever
 * looping through the main loop. The program tries to accomplish
 * the specified amount of frames per second each second.
 * 
 * @param targetFPS The target frames per second each second.
 */
void Frame::setTargetFPS(int targetFPS)
{
	Frame::targetFPS = targetFPS;
}

/**
 * Get the title that is displayed in the Title Bar of the Frame.
 * 
 * @return The title that is displayed in the Title Bar.
 */
string Frame::getTitle()
{
	const char* title = SDL_GetWindowTitle(window);

	string s(title);

	return s;
}

/**
 * Set the title that is displayed in the Title Bar of the Frame.
 * 
 * @param title The title that is to be displayed in the Title Bar.
 */
void Frame::setTitle(string title)
{
	SDL_SetWindowTitle(window, title.c_str());
}

/**
 * Get the horizontal location of the Frame in the Display.
 * 
 * @return The horizontal location of the Frame in the Display.
 */
int Frame::getX()
{
	int x, y;

	SDL_GetWindowPosition(window, &x, &y);

	return x;
}

/**
 * Get the vertical location of the Frame in the Display.
 * 
 * @return The vertical location of the Frame in the Display.
 */
int Frame::getY()
{
	int x, y;

	SDL_GetWindowPosition(window, &x, &y);

	return y;
}

/**
 * Set the location of the Frame.
 * 
 * @param x The horizontal location to put the Frame at.
 * @param y The vertical location to put the Frame at.
 */
void Frame::setLocation(int x, int y)
{
	SDL_SetWindowPosition(window, x, y);
}

/**
 * Get the horizontal size of the Frame in the Display.
 * 
 * @return The horizontal size of the Frame in the Display.
 */
int Frame::getWidth()
{
	return width;
}

/**
 * Get the vertical size of the Frame in the Display.
 * 
 * @return The vertical size of the Frame in the Display.
 */
int Frame::getHeight()
{
	return height;
}

/**
 * Add the specified FrameListener to this Frame.
 * 
 * @param listener The FrameListener to add to this Frame.
 * @return Whether the FrameListener was added successfully or not.
 */
bool Frame::addFrameListener(FrameListener* listener)
{
	frameListeners.add(listener);

	return true;
}

/**
 * Remove the specified FrameListener from this Frame.
 * 
 * @param listener The FrameListener to remove from this Frame.
 * @return Whether the remove was successful or not.
 */
bool Frame::removeFrameListener(FrameListener* listener)
{
	frameListeners.removeElement(listener);

	return true;
}

/**
 * Get the SDL_Window instance of the Frame.
 * 
 * @return The SDL_Window instance of the Frame.
 */
SDL_Window* Frame::getWindow()
{
	return window;
}

/**
 * Quit the Frame and free the memory with it.
 */
void Frame::quit()
{
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	delete panel;

	panel  = NULL;

	for (int i = components.size() - 1; i >= 0; i--)
	{
		delete components.get(i);
	}

	for (int i = frameListeners.size() - 1; i >= 0; i--)
	{
		delete frameListeners.get(i);
	}
}