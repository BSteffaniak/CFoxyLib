#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "CFL.h"

class MouseEvent : public Event
{
private:
	int	x, y;
	int	button;

public:
	MouseEvent(int, int, int);

	int	getX();
	int	getY();
	int	getButton();
};

#endif