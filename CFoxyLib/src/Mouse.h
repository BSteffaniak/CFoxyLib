#ifndef MOUSE_H
#define MOUSE_H

#include "CFL.h"

class Mouse
{
private:
	

public:
	static void	addMouseListener(MouseListener*);
	static void	removeMouseListener(MouseListener*);

	static bool	isInFrame();

	static int	getX();
	static int	getY();
};

#endif