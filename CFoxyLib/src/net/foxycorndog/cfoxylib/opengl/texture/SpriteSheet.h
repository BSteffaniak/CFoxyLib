#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "CFL.h"

class SpriteSheet : public Texture
{
private:
	int				cols, rows;

	vector<float*>	offsets;

	void			addOffsets(float*);
	void			quit();

public:
	SpriteSheet(string, int, int);
	~SpriteSheet();

	void	getImageOffsets(float*, int, int, int, int);

	int		getNumCols();
	int		getNumRows();
	int		getColSize();
	int		getRowSize();

	float*	getImageOffsets(int, int, int, int);
};

#endif