#ifndef BUNDLE_H
#define BUNDLE_H

#include "CFL.h"

class Bundle
{
private:
	int			vertsPosition, texturesPosition, colorsPosition;
	int			vertexAmount, vertexSize;
	GLuint		verticesId, texturesId, colorsId;

	Buffer		*verticesBuffer, *texturesBuffer, *colorsBuffer;

	static int	id;

	Bundle();

	void		beginVerticesDraw();
	void		endVerticesDraw();
	void		beginTexturesDraw();
	void		endTexturesDraw();
	void		beginColorsDraw();
	void		endColorsDraw();

public:
	Bundle(int, int, bool, bool);
	Bundle(Buffer*, Buffer*, Buffer*, int);
	Bundle(int, int, int, int, int);
	~Bundle();

	void	setVerticesBuffer(Buffer*);
	void	setVertices(int, float*, int);
	void	addVertices(float* verts, int length);
	void	setTexturesBuffer(Buffer*);
	void	setTextures(int, float*, int);
	void	addTextures(float* verts, int length);
	void	setColorsBuffer(Buffer*);
	void	setColors(int, float*, int);
	void	addColors(float* verts, int length);
	void	beginEditingVertices();
	void	endEditingVertices();
	void	beginEditingTextures();
	void	endEditingTextures();
	void	beginEditingColors();
	void	endEditingColors();
	void	render(int shape, Texture *texture);
	void	render(int shape, int start, int amount, Texture *texture);

	int		getVerticesPosition();
	int		getTexturesPosition();
	int		getColorsPosition();

	Buffer*	getVerticesBuffer();
	Buffer*	getTexturesBuffer();
	Buffer*	getColorsBuffer();
};

#endif