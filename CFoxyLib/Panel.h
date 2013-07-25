#ifndef PANEL_H
#define PANEL_H

#include "CFL.h"
#include <vector>

using std::vector;

class Color;

class Panel : public Component
{
private:
	bool	independentSize;

	Color*	backgroundColor;

	vector<Component*> children;

	Panel();

public:
	Panel(Panel*);

	void	setIndependentSize(bool);
	void	setBackgroundColor(Color*);
	void	renderComponents();
	void	render();

	bool	addChild(Component*);
	bool	isIndependentSize();
	bool	dispose();

	Color*	getBackgroundColor();
};

#endif