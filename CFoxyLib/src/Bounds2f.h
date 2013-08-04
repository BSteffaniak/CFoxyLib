#ifndef BOUNDS2F_H
#define BOUNDS2F_H

#include "CFL.h"

class Bounds2f
{
private:
	float	x, y;
	float	width, height;

	void	construct();

public:
	Bounds2f();
	Bounds2f(float, float, float, float);

	void	setX(float);
	void	setY(float);
	void	setLocation(float, float);
	void	setWidth(float);
	void	setHeight(float);
	void	setSize(float, float);

	float	getX();
	float	getY();
	float	getWidth();
	float	getHeight();
};

#endif