#include "CFL.h"

/**
 * Create a Bounds at the location (0, 0) with the size (0, 0).
 */
Bounds2f::Bounds2f()
{
	construct();
}

/**
 * Create a Pofloat at the location (x, y) with the size
 * (width, height).
 * 
 * @param x The horizontal location of the Bounds.
 * @param y The vertical location of the Bounds.
 * @param width The horizontal size of the Bounds.
 * @param height The vertical size of the Bounds.
 */
Bounds2f::Bounds2f(float x, float y, float width, float height)
{
	construct();

	this->x      = x;
	this->y      = y;
	this->width  = width;
	this->height = height;
}

void Bounds2f::construct()
{
	x      = 0;
	y      = 0;
	width  = 0;
	height = 0;
}

/**
 * Get the horizontal location of this Bounds.
 * 
 * @return The horizontal location of this Bounds.
 */
float Bounds2f::getX()
{
	return x;
}

/**
 * Sets the horizontal location of this Bounds.
 * 
 * @param x The horizontal value.
 */
void Bounds2f::setX(float x)
{
	this->x = x;
}

/**
 * Get the vertical location of this Bounds.
 * 
 * @return The vertical location of this Bounds.
 */
float Bounds2f::getY()
{
	return y;
}

/**
 * Sets the vertical location of this Bounds.
 * 
 * @param y The vertical value.
 */
void Bounds2f::setY(float y)
{
	this->y = y;
}

/**
 * Method to set the location of the Bounds at (x, y).
 * 
 * @param x The horizontal location.
 * @param y The vertical location.
 */
void Bounds2f::setLocation(float x, float y)
{
	this->x = x;
	this->y = y;
}

/**
 * Get the horizontal size of this Bounds.
 * 
 * @return The horizontal size of this Bounds.
 */
float Bounds2f::getWidth()
{
	return width;
}

/**
 * Sets the horizontal size of this Bounds.
 * 
 * @param width The horizontal size.
 */
void Bounds2f::setWidth(float width)
{
	this->width = width;
}

/**
 * Get the vertical size of this Bounds.
 * 
 * @return The vertical size of this Bounds.
 */
float Bounds2f::getHeight()
{
	return height;
}

/**
 * Sets the vertical size of this Bounds.
 * 
 * @param height The vertical size.
 */
void Bounds2f::setHeight(float height)
{
	this->height = height;
}

/**
 * Method to set the size of the Bounds with (width, height).
 * 
 * @param width The horizontal size.
 * @param height The vertical size.
 */
void Bounds2f::setSize(float width, float height)
{
	this->width  = width;
	this->height = height;
}