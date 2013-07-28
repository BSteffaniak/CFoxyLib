#include "../CFL.h"

/**
 * Check whether two rectangles with the specified dimensions
 * intersect.
 * 
 * @param x1 The horizontal location of the first rectangle.
 * @param y1 The vertical location of the first rectangle.
 * @param width1 The width of the first rectangle.
 * @param height1 The height of the first rectangle.
 * @param x2 The horizontal location of the second rectangle.
 * @param y2 The vertical location of the second rectangle.
 * @param width2 The width of the second rectangle.
 * @param height2 The height of the second rectangle.
 * @return Whether or not the two rectangles intersect.
 */
bool Intersects::rectanglesi(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2)
{
	if (width2 <= 0 || height2 <= 0 || width1 <= 0 || height1 <= 0)
	{
		return false;
	}
		
	width2  += x2;
	height2 += y2;
	width1  += x1;
	height1 += y1;
		
	return ((width2  < x2 || width2  > x1) &&
			(height2 < y2 || height2 > y1) &&
			(width1  < x1 || width1  > x2) &&
			(height1 < y1 || height1 > y2));
}

/**
 * Check whether two rectangles with the specified dimensions
 * intersect.
 * 
 * @param x1 The horizontal location of the first rectangle.
 * @param y1 The vertical location of the first rectangle.
 * @param width1 The width of the first rectangle.
 * @param height1 The height of the first rectangle.
 * @param x2 The horizontal location of the second rectangle.
 * @param y2 The vertical location of the second rectangle.
 * @param width2 The width of the second rectangle.
 * @param height2 The height of the second rectangle.
 * @return Whether or not the two rectangles intersect.
 */
bool Intersects::rectanglesl(long x1, long y1, long width1, long height1, long x2, long y2, long width2, long height2)
{
	if (width2 <= 0 || height2 <= 0 || width1 <= 0 || height1 <= 0)
	{
		return false;
	}
		
	width2  += x2;
	height2 += y2;
	width1  += x1;
	height1 += y1;
		
	return ((width2  < x2 || width2  > x1) &&
			(height2 < y2 || height2 > y1) &&
			(width1  < x1 || width1  > x2) &&
			(height1 < y1 || height1 > y2));
}

/**
 * Check whether two rectangles with the specified dimensions
 * intersect.
 * 
 * @param x1 The horizontal location of the first rectangle.
 * @param y1 The vertical location of the first rectangle.
 * @param width1 The width of the first rectangle.
 * @param height1 The height of the first rectangle.
 * @param x2 The horizontal location of the second rectangle.
 * @param y2 The vertical location of the second rectangle.
 * @param width2 The width of the second rectangle.
 * @param height2 The height of the second rectangle.
 * @return Whether or not the two rectangles intersect.
 */
bool Intersects::rectanglesf(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2)
{
	if (width2 <= 0 || height2 <= 0 || width1 <= 0 || height1 <= 0)
	{
		return false;
	}
		
	width2  += x2;
	height2 += y2;
	width1  += x1;
	height1 += y1;
		
	return ((width2  < x2 || width2  > x1) &&
			(height2 < y2 || height2 > y1) &&
			(width1  < x1 || width1  > x2) &&
			(height1 < y1 || height1 > y2));
}

/**
 * Check whether two rectangles with the specified dimensions
 * intersect.
 * 
 * @param x1 The horizontal location of the first rectangle.
 * @param y1 The vertical location of the first rectangle.
 * @param width1 The width of the first rectangle.
 * @param height1 The height of the first rectangle.
 * @param x2 The horizontal location of the second rectangle.
 * @param y2 The vertical location of the second rectangle.
 * @param width2 The width of the second rectangle.
 * @param height2 The height of the second rectangle.
 * @return Whether or not the two rectangles intersect.
 */
bool Intersects::rectanglesd(double x1, double y1, double width1, double height1, double x2, double y2, double width2, double height2)
{
	if (width2 <= 0 || height2 <= 0 || width1 <= 0 || height1 <= 0)
	{
		return false;
	}
		
	width2  += x2;
	height2 += y2;
	width1  += x1;
	height1 += y1;
		
	return ((width2  < x2 || width2  > x1) &&
			(height2 < y2 || height2 > y1) &&
			(width1  < x1 || width1  > x2) &&
			(height1 < y1 || height1 > y2));
}