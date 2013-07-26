#include "CFL.h"

/**
 * Construct a Panel that is used to hold Components with the
 * specified parent Panel.
 * 
 * @param parent The parent Panel of this Panel.
 */
Panel::Panel(Panel* parent) : Component(parent)
{

}

/**
 * Destruct the Panel and free the memory with it.
 */
Panel::~Panel()
{
	delete backgroundColor;

	backgroundColor = NULL;
}

/**
 * Get whether or not the size of the Panel is independent to
 * the scale that the OpenGL matrix has at the rendering time.
 * 
 * @return Whether or not the size of the Panel is independent to
 * 		scale at render time.
 */
bool Panel::isIndependentSize()
{
	return independentSize;
}

/**
 * Set whether or not the size of the Panel should be independent to
 * the scale that the OpenGL matrix has at the rendering time.
 * 
 * @param independentSize Whether or not to set the size of the Panel
 * 		to be independent to scale at render time.
 */
void Panel::setIndependentSize(bool independentSize)
{
	this->independentSize = independentSize;
}

/**
 * Get the Color that is rendered as the background.
 * 
 * @return The Color instance that is rendered as the background.
 */
Color* Panel::getBackgroundColor()
{
	return backgroundColor;
}

/**
 * Set the Color that the background will render in.
 * 
 * @param color The Color to set as the background Color.
 */
void Panel::setBackgroundColor(Color* color)
{
	this->backgroundColor = color;
}

/**
 * Add the specified Component as a child to this Panel. This removes
 * any previous links to parents from the child.
 * 
 * @param child The child Component to add to this Panel.
 */
bool Panel::addChild(Component* child)
{
	child->setParent(this);
	
	//if (children.Contains(child))
	//{
	//	return false;
	//}

	children.push_back(child);
	
	return true;
}

/**
 * Dispose this Panel and all of its children from the Listeners.
 * 
 * @return Whether it was successfully disposed.
 */
bool Panel::dispose()
{
	bool disposed = Component::dispose();
	
	for (unsigned int i = 0; i < children.size(); i++)
	{
		Component* comp = children.at(i);

		comp->dispose();
	}
	
	return disposed;
}

/**
 * Render all of the Components within the Panel to the Display.
 */
void Panel::renderComponents()
{
	for (int i = children.size() - 1; i >= 0; i--)
	{
		Component* child = children.at(i);
		
		if (child->isVisible())
		{
			child->render();
		}
	}
}

/**
 * Renders the Component to the screen.
 */
void Panel::render()
{
	if (isVisible())
	{
		GL::pushMatrix();
		{
			if (independentSize)
			{
				GL::translateIgnoreScale(getX(), getY(), 0);
				
				GL::beginFrameClipping(getDisplayX(), getDisplayY(), getWidth() * getFullScale(), getHeight() * getFullScale());
			}
			else
			{
				GL::translate(getX(), getY(), 0);

//					System.out.println(this + ": " + Math.round(getDisplayX()) + ", " + Math.round(getDisplayY()) + ": " + getScaleX() + ", " + getScaleY() + ": " + getTranslatedX() + ", " + getTranslatedY() + ": " + getScale() + ": " + Math.round(getScaledHeight()));
				GL::beginClipping(0, 0, getWidth() * getFullScale(), getHeight() * getFullScale());
//					GL.beginFrameClipping(Math.round(getDisplayX()), Math.round(getDisplayY()), Math.round(getScaledWidth()), Math.round(getScaledHeight()));
			}
			
			if (backgroundColor != NULL)
			{
//				GL.pushMatrix();
//				{
//					GL.translate(0, 0, backgroundIndex);
//					
//					if (independentSize)
//					{
//						GL.unscale();
//					}
//					
//					GL.scale(getWidth(), getHeight(), 1);
//					
//					Color current = GL.getColor();
//					
//					GL.setColor(backgroundColor);
//					backgroundBundle.render(GL.TRIANGLES, GL.WHITE);
//					
//					GL.setColor(current);
//				}
//				GL.popMatrix();
				
				Color orig(0, 0, 0);
				
				GL::getClearColor(&orig);
				
				GL::setClearColor(backgroundColor);
				
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				
				GL::setClearColor(&orig);
			}
			
			GL::scale(getScale(), getScale(), 1);
			
			update();
			
			renderComponents();
			
			GL::endClipping();
		}
		GL::popMatrix();
	}
}