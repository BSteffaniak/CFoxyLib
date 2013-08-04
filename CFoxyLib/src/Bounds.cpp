#include "CFL.h"

/**
 * Create a Bounds at the location (0, 0) with the size (0, 0).
 */
Bounds::Bounds()
{
	construct();
}

/**
 * Create a Point at the location (x, y) with the size
 * (width, height).
 * 
 * @param x The horizontal location of the Bounds.
 * @param y The vertical location of the Bounds.
 * @param width The horizontal size of the Bounds.
 * @param height The vertical size of the Bounds.
 */
Bounds::Bounds(int x, int y, int width, int height)
{
	construct();

	this->x      = x;
	this->y      = y;
	this->width  = width;
	this->height = height;
}

void Bounds::construct()
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
int Bounds::getX()
{
	return x;
}

/**
 * Sets the horizontal location of this Bounds.
 * 
 * @param x The horizontal value.
 */
void Bounds::setX(int x)
{
	this->x = x;
}

/**
 * Get the vertical location of this Bounds.
 * 
 * @return The vertical location of this Bounds.
 */
int Bounds::getY()
{
	return y;
}

/**
 * Sets the vertical location of this Bounds.
 * 
 * @param y The vertical value.
 */
void Bounds::setY(int y)
{
	this->y = y;
}

/**
 * Method to set the location of the Bounds at (x, y).
 * 
 * @param x The horizontal location.
 * @param y The vertical location.
 */
void Bounds::setLocation(int x, int y)
{
	this->x = x;
	this->y = y;
}

/**
 * Get the horizontal size of this Bounds.
 * 
 * @return The horizontal size of this Bounds.
 */
int Bounds::getWidth()
{
	return width;
}

/**
 * Sets the horizontal size of this Bounds.
 * 
 * @param width The horizontal size.
 */
void Bounds::setWidth(int width)
{
	this->width = width;
}

/**
 * Get the vertical size of this Bounds.
 * 
 * @return The vertical size of this Bounds.
 */
int Bounds::getHeight()
{
	return height;
}

/**
 * Sets the vertical size of this Bounds.
 * 
 * @param height The vertical size.
 */
void Bounds::setHeight(int height)
{
	this->height = height;
}

/**
 * Method to set the size of the Bounds with (width, height).
 * 
 * @param width The horizontal size.
 * @param height The vertical size.
 */
void Bounds::setSize(int width, int height)
{
	this->width  = width;
	this->height = height;
}