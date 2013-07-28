#ifndef TEXTURE_H
#define TEXTURE_H

#include "CFL.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class Texture
{
private:
	int				width, height;

	GLuint			id;

	fbyte*			pixels;

	vector<float*>	offsets;

	static int		currentId;

	void			init();
	void			genTexDimensions();
	void			addOffsets(float*);
	void			quit();

	static void		bind(int);

public:
	Texture();
	Texture(string);
	~Texture();
	
	void			loadTexture(fbyte*, int, int);
	void			loadTexture();
	void			getPixels(int*, int, int, int, int);
	void			setPixel(int, int, int);
	void			setPixels(int, int, int, int, int*);
	void			setPixels2(int, int, int, int, int);
	void			setPixelBytes(int, int, unsigned char*);
	void			getPixelBytes(fbyte*, int, int);
	void			getPixelsBytes(fbyte*, int, int, int, int);
	void			setPixelsBytes(int, int, int, int, fbyte*);
	void			setPixelsBytes2(int, int, int, int, fbyte*);
	void			getImageOffsets(float*);
	void			bind();

	bool			isBound();

	int				getId();
	int				getPixel(int, int);
	int				getWidth();
	int				getHeight();

	float*			getImageOffsets();

	static void		unbind();
};

#endif