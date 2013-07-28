#ifndef FOXYIMAGE_H
#define FOXYIMAGE_H

#include "CFL.h"

class FoxyImage
{
private:
	int		width, height;

	vector<fbyte>	data;

	static vector<fbyte*>	images;

	static void	addImage(fbyte*);

public:
	FoxyImage(string);
	~FoxyImage();

	int		getWidth();
	int		getHeight();

	fbyte*	getData();
};

#endif