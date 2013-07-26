#include "CFL.h"
#include <iostream>

using std::cout;

bool	Component::initialized;

int		Component::defaultHorizontalAlignment;
int		Component::defaultVerticalAlignment;

vector<Component*>	Component::components;

/**
 * Construct a Component with the specified parent Panel.
 * 
 * @param parent The parent Panel of this Component.
 */
Component::Component(Panel* parent)
{
	init();

	if (parent == NULL)
	{
		parent = Frame::getPanel();
	}

	Component::parent = parent;

	components.push_back(this);
	
	this->enabled  = true;
		
	this->parent   = parent;
		
	this->visible  = true;
		
	this->disposed = false;
		
	if (parent != NULL)
	{
		parent->addChild(this);
	}
		
	scaleX = 1;
	scaleY = 1;
	
	setScale(1);
	setAlignment(defaultHorizontalAlignment, defaultVerticalAlignment);
}

Component::~Component()
{
	delete parent;

	parent = NULL;
}

/**
 * Initialize the Component class stuff.
 */
void Component::init()
{
	if (initialized)
	{
		return;
	}

	setDefaultHorizontalAlignment(LEFT);
	setDefaultVerticalAlignment(BOTTOM);

	initialized = true;
}

/**
 * Get the scale that the Component is currently rendered in. The
 * scale will only affect the (x, y) axiis. Not the z axis.
 * 
 * @return The scale that the Component is currently rendered in.
 */
float Component::getScale()
{
	return scale;
}

/**
 * Get the scale of the Component taking into account the scale of the
 * Parent Components.
 * 
 * @return The full scale of the Component.
 */
float Component::getFullScale()
{
	float scale = this->scale;
	
	Component* parent = this->parent;
	
	while (parent != NULL)
	{
		scale *= parent->scale;
		
		parent = parent->getParent();
	}
	
	return scale;
}

/**
 * Set the scale that the Component will be rendered in.
 * 
 * @param scale The new scale to render the Component in.
 */
void Component::setScale(float scale)
{
	this->scale = scale;
}

/**
 * Get whether the Component is enabled or not.
 * 
 * @return Whether the Component is enabled or not.
 */
bool Component::isEnabled()
{
	return enabled;
}

/**
 * Set whether to enable the Component or disable the Component.
 * 
 * @param enabled Whether to enable or disable the Component.
 */
void Component::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

/**
 * Get whether the Component is focused on or not.
 * 
 * @return Whether the Component is focused on or not.
 */
bool Component::isFocused()
{
	return focused;
}

/**
 * Set whether to focus on the Component or not.
 * 
 * @param focused Whether to focus on the Component or not.
 */
void Component::setFocused(bool focused)
{
	if (focused)
	{
		for (int i = components.size() - 1; i >= 0; i--)
		{
			Component* c = components.at(i);
			
			c->setFocused(false);
		}
	}
	
	this->focused = focused;
}

/**
 * Get whether this Component is visible. Whether or not the Component
 * is being rendered.
 * 
 * @return Whether or not the Component is being rendered.
 */
bool Component::isVisible()
{
	if (!visible)
	{
		return false;
	}
	else
	{
		Panel* parent = this->parent;
		
		while (parent != NULL)
		{
			if (!parent->isVisible())
			{
				return false;
			}
			
			parent = parent->getParent();
		}
	}
	
	return visible;
}

/**
 * Set whether this Component is visible. Whether or not the Component
 * should be rendered.
 * 
 * @param visible Whether or not the Component should be rendered.
 */
void Component::setVisible(bool visible)
{
	this->visible = visible;
}

/**
 * Get the horizontal location of this Component.
 * 
 * @return The horizontal location of this Component.
 */
float Component::getX()
{
	return x + alignX;
}

/**
 * Get the vertical location of this Component.
 * 
 * @return The vertical location of this Component.
 */
float Component::getY()
{
	return y + alignY;
}

/**
 * Get the horizontal scale of this Component during its last update.
 * 
 * @return The horizontal scale of this Component.
 */
float Component::getScaleX()
{
	return scaleX;
}

/**
 * Get the vertical scale of this Component during its last update.
 * 
 * @return The vertical scale of this Component.
 */
float Component::getScaleY()
{
	return scaleY;
}

/**
 * Get the horizontal location that this Component was last
 * displayed on the screen.
 * 
 * @return The horizontal location that this Component was last
 * 		displayed on the screen.
 */
float Component::getDisplayX()
{
	return displayX;//(getX()) * getFullScale() + getTranslatedX();
}

/**
 * Get the vertical location that this Component was last
 * displayed on the screen.
 * 
 * @return The vertical location that this Component was last
 * 		displayed on the screen.
 */
float Component::getDisplayY()
{
	return displayY;//(getY()) * getFullScale() + getTranslatedY();
}

/**
 * Set the location of this Component to the specified location.
 * 
 * @param x The new horizontal location of the Component.
 * @param y The new vertical location of the Component.
 */
void Component::setLocation(float x, float y)
{
	this->x = x;
	this->y = y;
}

/**
 * Get the horizontal size of this Component.
 * 
 * @return The horizontal size of this Component.
 */
float Component::getWidth()
{
	return width;
}

/**
 * Get the vertical size of this Component.
 * 
 * @return The vertical size of this Component.
 */
float Component::getHeight()
{
	return height;
}

/**
 * Get the horizontal size of this Component with consideration
 * of the scale.
 * 
 * @return The scaled horizontal size of this Component.
 */
float Component::getScaledWidth()
{
	return width * scaleX;
}

/**
 * Get the vertical size of this Component with consideration
 * of the scale.
 * 
 * @return The scaled vertical size of this Component.
 */
float Component::getScaledHeight()
{
	return height * scaleY;
}

/**
 * Set the size of this Component to the specified size.
 * 
 * @param width The new horizontal size of the Component.
 * @param height The new vertical size of the Component.
 */
void Component::setSize(float width, float height)
{
	this->width  = width;
	this->height = height;
}

/**
 * Get the parent Panel of this Component.
 * 
 * @return The parent Panel of this Component.
 */
Panel* Component::getParent()
{
	return parent;
}

/**
 * Set the parent Panel of this Component.
 * 
 * @param parent The parent Panel of this Component.
 */
void Component::setParent(Panel* parent)
{
	this->parent = parent;
}

/**
 * Returns whether this Component is disposed or not.
 * 
 * @return Whether this Component is disposed or not.
 */
bool Component::isDisposed()
{
	return disposed;
}

/**
 * Dispose this Component from the Listeners.
 * 
 * @return Whether it was successfully disposed.
 */
bool Component::dispose()
{
	bool disposed = Frame::remove(this);
	
	for (unsigned int i = 0; i < components.size(); i++)
	{
		if (components.at(i) == this)
		{
			components.erase(components.begin() + i);

			break;
		}
	}
	
	return disposed;
}

/**
 * Set the alignment to the specified values.
 * 
 * @param horizontal The horizontal alignment.
 * @param vertical The vertical alignment.
 */
void Component::setAlignment(int horizontal, int vertical)
{
	this->horizontalAlignment = horizontal;
	this->verticalAlignment   = vertical;
	
	align();
}

/**
 * Set the alignment variables to their correct values.
 */
void Component::align()
{
	float width    = 0;
	float height   = 0;
	
	float scaleWid = getWidth()  * scale;//  * scaleX / scale;
	float scaleHei = getHeight() * scale;// * scaleY / scale;
	
	if (parent == NULL)
	{
		width  = (float)Frame::getWidth();
		height = (float)Frame::getHeight();
	}
	else
	{
		width  = parent->getWidth();
		height = parent->getHeight();
	}
	
	alignX = 0;
	alignY = 0;
	
	if (horizontalAlignment == CENTER)
	{
		alignX = (width / 2) - (scaleWid / 2);
		
//			alignX -= ((scaleWid * scale) - scaleWid) / 2;
	}
	else if (horizontalAlignment == RIGHT)
	{
		alignX = width - scaleWid;
		
//			alignX -= ((scaleWid * scale) - scaleWid);
	}
	
	// If we want to align it at the top.
	if (verticalAlignment == TOP)
	{
		alignY = height - scaleHei;
	}
	else if (verticalAlignment == CENTER)
	{
		alignY = (height / 2) - (scaleHei / 2);
	}
	
	
//		alignX /= scaleX;
//		alignY /= scaleY;
	
//		alignX /= scale;
//		alignY /= scale;
	
//		alignX = 0;
//		alignY = 0;
}

/**
 * Method to update the Component's information such as
 * the alignment location.
 */
void Component::update()
{
	float scale[3];
	
	GL::getAmountScaled(scale);
	
	scaleX = scale[0];
	scaleY = scale[1];
	
	float loc[3];
	
	GL::getCurrentLocation(loc);
	
	displayX = loc[0];
	displayY = loc[1];
	
	align();
}

void Component::render()
{

}

/**
 * Get the default horizontal alignment of the following made
 * Components.<br>
 * Results include:
 * 	<ul>
 * 		<li>LEFT - The Components are aligned on the left.</li>
 * 		<li>CENTER - The Components are aligned in the center.</li>
 * 		<li>RIGHT - The Components are aligned on the right.</li>
 * 	</ul>
 * 
 * @return The default alignment of the following made Components.
 */
int Component::getDefaultHorizontalAlignment()
{
	return defaultHorizontalAlignment;
}
	
/**
 * Set the default horizontal alignment of the following made
 * Components.<br>
 * Options include:
 * 	<ul>
 * 		<li>LEFT - Align the Components to the left.</li>
 * 		<li>CENTER - Align the Components in the center.</li>
 * 		<li>RIGHT - Align the Components to the right.</li>
 * 	</ul>
 * 
 * @param defaultHorizontalAlignment The default horizontal alignment
 * 		for the following made Components.
 */
void Component::setDefaultHorizontalAlignment(int defaultHorizontalAlignment)
{
	Component::defaultHorizontalAlignment = defaultHorizontalAlignment;
}
	
/**
 * Get the default vertical alignment of the following made
 * Components.<br>
 * Results include:
 * 	<ul>
 * 		<li>TOP - The Components are aligned at the top.</li>
 * 		<li>CENTER - The Components are aligned in the center.</li>
 * 		<li>BOTTOM - The Components are aligned at the bottom.</li>
 * 	</ul>
 * 
 * @return The default alignment of the following made Components.
 */
int Component::getDefaultVerticalAlignment()
{
	return defaultVerticalAlignment;
}
	
/**
 * Set the default vertical alignment of the following made
 * Components.<br>
 * Options include:
 * 	<ul>
 * 		<li>TOP - Align the Components at the top.</li>
 * 		<li>CENTER - Align the Components in the center.</li>
 * 		<li>BOTTOM - Align the Components at the bottom.</li>
 * 	</ul>
 * 
 * @param defaultVerticalAlignment The default vertical alignment for
 * 		the following made Components.
 */
void Component::setDefaultVerticalAlignment(int defaultVerticalAlignment)
{
	Component::defaultVerticalAlignment = defaultVerticalAlignment;
}