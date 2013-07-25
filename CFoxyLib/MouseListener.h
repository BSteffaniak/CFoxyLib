#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H

#include "CFL.h"

class MouseListener
{
private:
	

public:
	virtual void mousePressed(MouseEvent);
	virtual void mouseReleased(MouseEvent);
	virtual void mouseDown(MouseEvent);
	virtual void mouseUp(MouseEvent);
	virtual void mouseMoved(MouseEvent);
	virtual void mouseEntered(MouseEvent);
	virtual void mouseExited(MouseEvent);
};

#endif