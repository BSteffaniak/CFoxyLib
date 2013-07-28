#ifndef INTERSECTS_H
#define INTERSECTS_H

#include "../CFL.h"

class Intersects
{
private:
	

public:
	static bool	rectanglesi(int, int, int, int, int, int, int, int);
	static bool	rectanglesl(long, long, long, long, long, long, long, long);
	static bool	rectanglesf(float, float, float, float, float, float, float, float);
	static bool	rectanglesd(double, double, double, double, double, double, double, double);
};

#endif