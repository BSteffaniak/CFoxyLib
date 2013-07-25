#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Texture
{
private:
	int				id;
	int				width, height;

	vector<byte>	pixels;

	float*			offsets;

	static int		currentId;

	void		genTexDimensions();

	static void	bind(int);

public:
	Texture();
	Texture(string);

	void		loadTexture(byte*, int, int);
	void		loadTexture();
	void			getPixels(int*, int, int, int, int);
	void			setPixel(int, int, int);
	void			setPixels(int, int, int, int, int*);
	void			setPixels2(int, int, int, int, int);
	void			setPixelBytes(int, int, unsigned char*);
	void			getPixelBytes(byte*, int, int);
	void			getPixelsBytes(byte*, int, int, int, int);
	void			setPixelsBytes(int, int, int, int, byte*);
	void			setPixelsBytes2(int, int, int, int, byte*);
	void			getImageOffsets(float*);
	void			bind();

	bool			isBound();

	int				getId();
	int				getPixel(int, int);
	int				getWidth();
	int				getHeight();

	static void		unbind();
};

#endif