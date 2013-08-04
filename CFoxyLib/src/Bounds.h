#ifndef BOUNDS_H
#define BOUNDS_H

#include "CFL.h"

class Bounds
{
private:
	int		x, y;
	int		width, height;

	void	construct();

public:
	Bounds();
	Bounds(int, int, int, int);

	void	setX(int);
	void	setY(int);
	void	setLocation(int, int);
	void	setWidth(int);
	void	setHeight(int);
	void	setSize(int, int);

	int		getX();
	int		getY();
	int		getWidth();
	int		getHeight();
};

#endif