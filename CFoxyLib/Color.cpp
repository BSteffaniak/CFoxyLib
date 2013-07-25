#include "CFL.h"
#include <math.h>

const Color Color::white = Color(255, 255, 255);
const Color Color::WHITE = white;
const Color Color::lightGray = Color(192, 192, 192);
const Color Color::LIGHT_GRAY = lightGray;
const Color Color::gray = Color(128, 128, 128);
const Color Color::GRAY = gray;
const Color Color::darkGray = Color(64, 64, 64);
const Color Color::DARK_GRAY = darkGray;
const Color Color::black = Color(0, 0, 0);
const Color Color::BLACK = black;
const Color Color::red = Color(255, 0, 0);
const Color Color::RED = red;
const Color Color::pink = Color(255, 175, 175);
const Color Color::PINK = pink;
const Color Color::orange = Color(255, 200, 0);
const Color Color::ORANGE = orange;
const Color Color::yellow = Color(255, 255, 0);
const Color Color::YELLOW = yellow;
const Color Color::green = Color(0, 255, 0);
const Color Color::GREEN = green;
const Color Color::magenta = Color(255, 0, 255);
const Color Color::MAGENTA = magenta;
const Color Color::cyan = Color(0, 255, 255);
const Color Color::CYAN = cyan;
const Color Color::blue = Color(0, 0, 255);
const Color Color::BLUE = blue;

/**
 * Create a color with the values (0, 0, 0, 255).
 */
Color::Color()
{
	Color::Color(0, 0, 0);
}

/**
 * Create a color with the specified red, green, and blue values.
 * 
 * @param r The red component for the Color.
 * @param g The green component for the Color.
 * @param b The blue component for the Color.
 */
Color::Color(int r, int g, int b)
{
	Color::Color(r, g, b, 255);
}

/**
 * Create a color with the specified red, green, and blue values.
 * (0 - 255)
 * 
 * @param r The red component for the Color.
 * @param g The green component for the Color.
 * @param b The blue component for the Color.
 * @param a The alpha component for the Color.
 */
Color::Color(int r, int g, int b, int a)
{
	Color::Color(r / (float)255, g / (float)255, b / (float)255, a / (float)255);
}

/**
 * Create a color with the specified red, green, and blue values.
 * 
 * @param r The red component for the Color.
 * @param g The green component for the Color.
 * @param b The blue component for the Color.
 */
Color::Color(float r, float g, float b)
{
	Color::Color(r, g, b, (float)1);
}

/**
 * Create a color with the specified red, green, and blue values.
 * (0 - 1)
 * 
 * @param r The red component for the Color.
 * @param g The green component for the Color.
 * @param b The blue component for the Color.
 * @param a The alpha component for the Color.
 */
Color::Color(float r, float g, float b, float a)
{
	setData(r, g, b, a);
}

/**
 * Get the red component of the Color.
 * 
 * @return The red component of the Color.
 */
int Color::getRed()
{
	return round(r * 255);
}

/**
 * Get the green component of the Color.
 * 
 * @return The green component of the Color.
 */
int Color::getGreen()
{
	return round(g * 255);
}

/**
 * Get the blue component of the Color.
 * 
 * @return The blue component of the Color.
 */
int Color::getBlue()
{
	return round(b * 255);
}

/**
 * Get the alpha component of the Color.
 * 
 * @return The alpha component of the Color.
 */
int Color::getAlpha()
{
	return round(a * 255);
}

/**
 * Get the red component of the Color as a float value.
 * ranging from 0-1 (0 == 0 & 1 == 255)
 * 
 * @return The red component of the Color in float form.
 */
float Color::getRedf()
{
	return r;
}

/**
 * Get the green component of the Color as a float value.
 * ranging from 0-1 (0 == 0 & 1 == 255)
 * 
 * @return The green component of the Color in float form.
 */
float Color::getGreenf()
{
	return g;
}

/**
 * Get the blue component of the Color as a float value.
 * ranging from 0-1 (0 == 0 & 1 == 255)
 * 
 * @return The blue component of the Color in float form.
 */
float Color::getBluef()
{
	return b;
}

/**
 * Get the alpha component of the Color as a float value.
 * ranging from 0-1 (0 == 0 & 1 == 255)
 * 
 * @return The alpha component of the Color in float form.
 */
float Color::getAlphaf()
{
	return a;
}

/**
 * Set the Color's red, green, and blue components to the specified
 * values.
 * 
 * @param r The new red component.
 * @param g The new green component.
 * @param b The new blue component.
 * @param a The new alpha component.
 */
void Color::setData(int r, int g, int b, int a)
{
	this->r = r / (float)255;
	this->g = g / (float)255;
	this->b = b / (float)255;
	this->a = a / (float)255;
	
	checkBounds();
}

/**
 * Set the Color's red, green, and blue components to the specified
 * values.
 * 
 * @param r The new red component.
 * @param g The new green component.
 * @param b The new blue component.
 * @param a The new alpha component.
 */
void Color::setData(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	
	checkBounds();
}

/**
 * Brighten the Color the specified amount. Each of the Color
 * components will be increased the specified amount.
 * 
 * eg. A Color with the values (40, 10, 200, 0) that has a call
 * of brighten(30, 10, 0, 0) will have the resulting values of
 * (70, 20, 200, 0)
 * 
 * @param r The amount of red to add.
 * @param g The amount of green to add.
 * @param b The amount of blue to add.
 * @param a The amount of alpha to add.
 */
void Color::brighten(int r, int g, int b, int a)
{
	this->r += r;
	this->g += g;
	this->b += b;
	this->a += a;
	
	checkBounds();
}

/**
 * Darken the Color the specified amount. Each of the Color
 * components will be decreased the specified amount.
 * 
 * eg. A Color with the values (40, 10, 200, 0) that has a call
 * of darken(30, 10, 0, 0) will have the resulting values of
 * (10, 0, 200, 0)
 * 
 * @param r The amount of red to subtract.
 * @param g The amount of green to subtract.
 * @param b The amount of blue to subtract.
 * @param a The amount of alpha to subtract.
 */
void Color::darken(int r, int g, int b, int a)
{
	brighten(-r, -g, -b, -a);
}

/**
 * Check to make sure that the Color component values are within
 * the range of 0-255. If not, then put them back in bounds.
 */
void Color::checkBounds()
{
	if (r < 0)
	{
		r = 0;
	}
	if (g < 0)
	{
		g = 0;
	}
	if (b < 0)
	{
		b = 0;
	}
	if (a < 0)
	{
		a = 0;
	}
	
	if (r > 1)
	{
		r = 1;
	}
	if (g > 1)
	{
		g = 1;
	}
	if (b > 1)
	{
		b = 1;
	}
	if (a > 1)
	{
		a = 1;
	}
}

/**
 * Round the float value to the rounded integer value.
 * 
 * @param value The float value to round.
 * @return The rounded integer value.
 */
int Color::round(float value)
{
	return (int)floor(value + 0.5);
}