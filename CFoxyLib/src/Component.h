#ifndef COMPONENT_H
#define COMPONENT_H

#include "CFL.h"
#include <vector>

using std::vector;

class Panel;

class Component
{
private:
	bool		disposed;
	bool		visible;
	bool		focused;
	bool		enabled;

	int			horizontalAlignment, verticalAlignment;

	float		x, y;
	float		alignX, alignY;
	float		displayX, displayY;
	float		width, height;
	float		scaleX, scaleY;
	float		scale;

	Panel*		parent;

	static bool	initialized;

	static int	defaultHorizontalAlignment, defaultVerticalAlignment;

	static vector<Component*>	components;

	void	align();

	static void	init();

public:
	Component(Panel*);
	~Component();

	static const int	LEFT = 0, CENTER = 1, RIGHT = 2,
						BOTTOM = 0, TOP = 2;

	void			setScale(float);
	void			setEnabled(bool);
	void			setFocused(bool);
	void			setVisible(bool);
	void			setLocation(float, float);
	void			setSize(float, float);
	void			setAlignment(int, int);
	void			setParent(Panel*);
	void			update();

	bool			isEnabled();
	bool			isFocused();
	bool			isVisible();
	bool			isDisposed();

	float			getScale();
	float			getFullScale();
	float			getX();
	float			getY();
	float			getScaleX();
	float			getScaleY();
	float			getDisplayX();
	float			getDisplayY();
	float			getWidth();
	float			getHeight();
	float			getScaledWidth();
	float			getScaledHeight();

	Panel*			getParent();
	
	/**
	 * Method that must be implemented. Renders the Component to
	 * the screen.
	 */
	virtual void	render();
	virtual bool	dispose();

	static void		setDefaultHorizontalAlignment(int alignment);
	static void		setDefaultVerticalAlignment(int alignment);

	static int		getDefaultHorizontalAlignment();
	static int		getDefaultVerticalAlignment();
};

#endif