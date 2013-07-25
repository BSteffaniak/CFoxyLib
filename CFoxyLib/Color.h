#ifndef COLOR_H
#define COLOR_H

#include "CFL.h"

class Color
{
private:
	float	r, g, b, a;

	void	checkBounds();

	int		round(float);

public:
	static const Color	white;
	static const Color	WHITE;
	static const Color	lightGray;
	static const Color	LIGHT_GRAY;
	static const Color	gray;
	static const Color	GRAY;
	static const Color	darkGray;
	static const Color	DARK_GRAY;
	static const Color	black;
	static const Color	BLACK;
	static const Color	red;
	static const Color	RED;
	static const Color	pink;
	static const Color	PINK;
	static const Color	orange;
	static const Color	ORANGE;
	static const Color	yellow;
	static const Color	YELLOW;
	static const Color	green;
	static const Color	GREEN;
	static const Color	magenta;
	static const Color	MAGENTA;
	static const Color	cyan;
	static const Color	CYAN;
	static const Color	blue;
	static const Color	BLUE;

	Color();
	Color(int, int, int);
	Color(int, int, int, int);
	Color(float, float, float);
	Color(float, float, float, float);

	void	setData(int r, int g, int b, int a);
	void	setData(float, float, float, float);
	void	brighten(int, int, int, int);
	void	darken(int, int, int, int);

	int		getRed();
	int		getGreen();
	int		getBlue();
	int		getAlpha();

	float	getRedf();
	float	getGreenf();
	float	getBluef();
	float	getAlphaf();
};

#endif