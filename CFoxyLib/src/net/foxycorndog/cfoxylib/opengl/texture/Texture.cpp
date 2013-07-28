#include "../../CFL.h"

int				Texture::currentId;

/**
 * Create a default blank Texture instance.
 */
Texture::Texture()
{
	init();
}

/**
 * Create a Texture from the File at the specified location.
 * 
 * @param location The location of the Image File containing the
 * 		Texture.
 * @throws IOException Thrown if there is an error reading from the
 * 		Image File at the specified location.
 */
Texture::Texture(string location)
{
	init();

	FoxyImage image(location);

	loadTexture(image.getData(), image.getWidth(), image.getHeight());
}

/**
 * Destruct the Texture and all the memory too.
 */
Texture::~Texture()
{
	//delete[] pixels;

	//pixels = NULL;

	quit();

	glDeleteTextures(1, &id);
}

/**
 * Initialize all of the common data between each of the constructors.
 */
void Texture::init()
{
	pixels = nullptr;
}

/**
 * Get the ID number that OpenGL assigned the Texture.
 * 
 * @return The ID number of the Texture.
 */
int Texture::getId()
{
	return id;
}

/**
 * Load the Texture's data and save it to OpenGL.
 * 
 * @param image The BufferedImage to create the Texture from.
 * @param recreate Whether or not to recreate the BufferedImage
 * 		with the needed type of TYPE_4fbyte_ABGR.
 */
void Texture::loadTexture(fbyte* data, int width, int height)
{
	glGenTextures(1, &id);

	this->width  = width;
	this->height = height;

	pixels = data;

	//pixels = new byte[length];

	//for (unsigned int i = 0; i < length; i++)
	//{
	//	pixels[i] = data[i];
	//}

	//pixels.resize(length);

	//pixels.insert(pixels.begin(), data, data + length);

    //bind();
    
    //// Flip the data vertically.
    //for (int y = 0; y < height / 2; y++)
    //{
    //    for (int x = 0; x < width; x++)
    //    {
    //    	int offset  = (x + y * width) * 4;
    //    	int offset2 = (x + (height - y - 1) * width) * 4;
    //    	
    //    	for (int i = 0; i < 4; i++)
    //    	{
    //            byte temp = pixels[offset + i];
    //            pixels[offset + i]  = pixels[offset2 + i];
    //            pixels[offset2 + i] = temp;
    //    	}
    //    }
    //}
    
    //// Put the data in the right order (From ABGR to RGBA (Reverse it)).
    //for (int y = 0; y < height; y++)
    //{
    //	for (int x = 0; x < width; x++)
    //	{
    //    	int offset  = (x + y * width) * 4;
    //    	
    //		for (int i = 0; i < 2; i++)
    //    	{
    //            byte temp = pixels[offset + i];
    //            pixels[offset + i] = pixels[offset + 4 - i - 1];
    //            pixels[offset + 4 - i - 1] = temp;
    //    	}
    //	}
    //}
    
    loadTexture();
}

/**
 * Load the Texture from the existing pixel data from the pixels
 * byte array.
 */
void Texture::loadTexture()
{
	bind();

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}

//	/**
//	 * Get the integer array that holds the values of the colors for
//	 * the colors in the Texture.
//	 * 
//	 * @return The integer array instance.
//	 */
//	byte[] getPixels()
//	{
//		return pixels;
//	}

/**
 * Get the integer representation of the pixel at the specified
 * location of (x, y).
 * 
 * @param x The horizontal location of the pixel (Left = 0).
 * @param y The vertical location of the pixel (Bottom = 0).
 * @return The integer representation of a pixel. eg.:
 * 		Red with alpha = 0xFFFF0000.
 */
int Texture::getPixel(int x, int y)
{
	int pixel = 0;
	
	int r = pixels[(x + y * width) * 4 + 0];
	int g = pixels[(x + y * width) * 4 + 1];
	int b = pixels[(x + y * width) * 4 + 2];
	int a = pixels[(x + y * width) * 4 + 3];
	
	if (r < 0)
	{
		r += 256;
	}
	if (g < 0)
	{
		g += 256;
	}
	if (b < 0)
	{
		b += 256;
	}
	if (a < 0)
	{
		a += 256;
	}
	
	a *= 0x1000000;
	r *= 0x10000;
	g *= 0x100;
	b *= 0x1;
	
	pixel = r + g + b + a;
	
	return pixel;
}

/**
 * Get the integer representation of the pixels within the rectangle
 * (x, y, width, height) on the image. Get the integer representation of
 * the pixels. eg.: An array with values that include integers such as:
 * Red with alpha = 0xFFFF0000.
 * 
 * @param dest The destination int array to put the values in.
 * 		The size of the array must be >= (width * height).
 * @param x The horizontal location of the pixel (Left = 0).
 * @param y The vertical location of the pixel (Bottom = 0).
 * @param width The width of the rectangular selection of pixels
 * 		to get.
 * @param height The height of the rectangular selection of pixels
 * 		to get.
 */
void Texture::getPixels(int* dest, int x, int y, int width, int height)
{
//		byteBuffer.position((x + y * width) * 4);
//			
//		for (int i = 0; i < height; i++)
//		{
//			byteBuffer.get(data, i * width * 4, width * 4);
//		}
	
	for (int y2 = 0; y2 < height; y2++)
	{
		for (int x2 = 0; x2 < width; x2++)
		{
			dest[(x2 + y2 * width)] = getPixel(x2 + x, y2 + y);
		}
	}
}

/**
 * Set the integer representation of the pixel at the specified
 * location of (x, y) on the image.
 * 
 * @param x The horizontal location of the pixel (Left = 0).
 * @param y The vertical location of the pixel (Bottom = 0).
 * @param value The integer representation of a pixel. eg.:
 * 		Red with alpha = 0xFFFF0000.
 */
void Texture::setPixel(int x, int y, int value)
{
	if (!isBound())
	{
//		throw new UnboundTextureException("The Texture must be bound before editing the pixels.");
	}
	
	fbyte values[4];
	
	fbyte r = (fbyte)((value >> 16) & 0xFF);
	fbyte g = (fbyte)((value >>  8) & 0xFF);
	fbyte b = (fbyte)((value >>  0) & 0xFF);
	fbyte a = (fbyte)((value >> 24) & 0xFF);

	values[0] = r;
	values[1] = g;
	values[2] = b;
	values[3] = a;
	
	for (int i = 0; i < 4; i++)
	{
		pixels[(x + y * width) * 4 + i] = values[i];
	}
	
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, values);
}

/**
 * Set the integer representation of the pixels within the rectangle
 * (x, y, width, height) on the image.
 * 
 * @param x The horizontal location of the pixel (Left = 0).
 * @param y The vertical location of the pixel (Bottom = 0).
 * @param width The width of the rectangular selection of pixels
 * 		to set.
 * @param height The height of the rectangular selection of pixels
 * 		to set.
 * @param values The integer representation of the pixels. eg.:
 * 		An array with values that include integers such as: 
 * 		Red with alpha = 0xFFFF0000.<br>
 * 		The array size must equal (width * height).
 */
void Texture::setPixels(int x, int y, int width, int height, int values[])
{
	if (!isBound())
	{
//		throw new UnboundTextureException("The Texture must be bound before editing the pixels.");
	}
	
	vector<fbyte> bytes(width * height * 4);
	
	for (unsigned int i = 0; i < bytes.size(); i += 4)
	{
		fbyte r = (fbyte)((values[i / 4] >> 16) & 0xFF);
		fbyte g = (fbyte)((values[i / 4] >>  8) & 0xFF);
		fbyte b = (fbyte)((values[i / 4] >>  0) & 0xFF);
		fbyte a = (fbyte)((values[i / 4] >> 24) & 0xFF);

		bytes[i + 0] = r;
		bytes[i + 1] = g;
		bytes[i + 2] = b;
		bytes[i + 3] = a;
	}
	
	for (int y2 = 0; y2 < height; y2++)
	{
		for (int x2 = 0; x2 < width; x2++)
		{
			for (int i = 0; i < 4; i++)
			{
				pixels[((x + x2) + (y + y2) * this->width) * 4 + i] = bytes[(x2 + y2 * height) * 4 + i];
			}
		}
	}
	
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &bytes[0]);
}

/**
 * Set the integer representation of the pixels within the rectangle
 * (x, y, width, height) on the image.
 * 
 * @param x The horizontal location of the pixel (Left = 0).
 * @param y The vertical location of the pixel (Bottom = 0).
 * @param width The width of the rectangular selection of pixels
 * 		to set.
 * @param height The height of the rectangular selection of pixels
 * 		to set.
 * @param value The integer representation of the pixels. eg.:
 * 		An integer with the value such as: 
 * 		Red with alpha = 0xFFFF0000.
 */
void Texture::setPixels2(int x, int y, int width, int height, int value)
{
	if (!isBound())
	{
//		throw new UnboundTextureException("The Texture must be bound before editing the pixels.");
	}
	
	fbyte r = (fbyte)((value >> 16) & 0xFF);
	fbyte g = (fbyte)((value >>  8) & 0xFF);
	fbyte b = (fbyte)((value >>  0) & 0xFF);
	fbyte a = (fbyte)((value >> 24) & 0xFF);
	
	vector<fbyte> bytes(width * height * 4);
	
	for (unsigned int i = 0; i < bytes.size(); i += 4)
	{
		bytes[i + 0] = r;
		bytes[i + 1] = g;
		bytes[i + 2] = b;
		bytes[i + 3] = a;
	}
	
	for (int y2 = 0; y2 < height; y2++)
	{
		for (int x2 = 0; x2 < width; x2++)
		{
			for (int i = 0; i < 4; i++)
			{
				pixels[((x + x2) + (y + y2) * this->width) * 4 + i] = bytes[i];
			}
		}
	}
	
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &bytes[0]);
}

/**
 * Get the byte representation of the pixel at the specified
 * location of (x, y) on the image. Get the byte representation
 * of a pixel. eg.: Red with alpha = byte[] { -1, 0, 0, -1 }
 * (-1 == 255 considering Two's Complement).
 * 
 * @param dest The destination unsigned char array to put the
 *		values in. The size of the array must be >= (4).
 * @param x The horizontal location of the pixel (Left = 0).
 * @param y The vertical location of the pixel (Bottom = 0).
 */
void Texture::getPixelBytes(fbyte* dest, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		dest[i] = pixels[(x + y * width) * 4 + i];
	}
}

/**
 * Get the byte representation of the pixels within the rectangle
 * (x, y, width, height) on the image. Get the byte representation
 * of the pixels. eg.: An array with values that include bytes such
 * as: Red with alpha = byte[] { -1, 0, 0, -1 } (-1 == 255
 * considering Two's Complement)
 * 
 * @param dest The destination unsigned char array to put the values
 *		in. The size of the array must be >= (width * height * 4).
 * @param x The horizontal location of the pixel (Left = 0).
 * @param y The vertical location of the pixel (Bottom = 0).
 * @param width The width of the rectangular selection of pixels
 * 		to get.
 * @param height The height of the rectangular selection of pixels
 * 		to get.
 */
void Texture::getPixelsBytes(fbyte* dest, int x, int y, int width, int height)
{
	for (int y2 = 0; y2 < height; y2++)
	{
		for (int x2 = 0; x2 < width; x2++)
		{
			fbyte d[4];
			
			getPixelBytes(d, x2 + x, y2 + y);
			
			for (int i = 0; i < 4; i++)
			{
				dest[(x2 + y2 * width) * 4 + i] = d[i];
			}
		}
	}
}

/**
 * Set the byte representation of the pixel at the specified
 * location of (x, y) on the image.
 * 
 * @param x The horizontal location of the pixel (Left = 0).
 * @param y The vertical location of the pixel (Bottom = 0).
 * @param value The byte representation of a pixel. eg.:
 * 		Red with alpha = byte[] { -1, 0, 0, -1 }
 * 		(-1 == 255 considering Two's Complement).
 */
void Texture::setPixelBytes(int x, int y, fbyte* values)
{
	if (!isBound())
	{
//		throw new UnboundTextureException("The Texture must be bound before editing the pixels.");
	}
	
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, values);
}

/**
 * Set the byte representation of the pixels within the rectangle
 * (x, y, width, height) on the image.
 * 
 * @param x The horizontal location of the pixel (Left = 0).
 * @param y The vertical location of the pixel (Bottom = 0).
 * @param width The width of the rectangular selection of pixels
 * 		to set.
 * @param height The height of the rectangular selection of pixels
 * 		to set.
 * @param values The byte representation of the pixels. eg.:
 * 		An array with values that include bytes such as: 
 * 		Red with alpha = byte[] { -1, 0, 0, -1 }
 * 		(-1 == 255 considering Two's Complement)<br>
 * 		The array size must equal (width * height * 4).
 */
void Texture::setPixelsBytes(int x, int y, int width, int height, fbyte* values)
{
	if (!isBound())
	{
//		throw new UnboundTextureException("The Texture must be bound before editing the pixels.");
	}
	
	for (int y2 = 0; y2 < height; y2++)
	{
		for (int x2 = 0; x2 < width; x2++)
		{
			for (int i = 0; i < 4; i++)
			{
				pixels[((x + x2) + (y + y2) * this->width) * 4 + i] = values[(x2 + y2 * height) * 4 + i];
			}
		}
	}
	
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, values);
}

/**
 * Set the byte representation of the pixels within the rectangle
 * (x, y, width, height) on the image.
 * 
 * @param x The horizontal location of the pixel (Left = 0).
 * @param y The vertical location of the pixel (Bottom = 0).
 * @param width The width of the rectangular selection of pixels
 * 		to set.
 * @param height The height of the rectangular selection of pixels
 * 		to set.
 * @param value The byte representation of the pixels. eg.:
 * 		An array with values that include bytes such as: 
 * 		Red with alpha = byte[] { -1, 0, 0, -1 }
 * 		(-1 == 255 considering Two's Complement)
 */
void Texture::setPixelsBytes2(int x, int y, int width, int height, fbyte* value)
{
	if (!isBound())
	{
//		throw new UnboundTextureException("The Texture must be bound before editing the pixels.");
	}
	
	vector<fbyte> bytes(width * height * 4);
	
	for (unsigned int i = 0; i < bytes.size(); i += 4)
	{
		bytes[i + 0] = value[0];
		bytes[i + 1] = value[1];
		bytes[i + 2] = value[2];
		bytes[i + 3] = value[3];
	}
	
	for (int y2 = 0; y2 < height; y2++)
	{
		for (int x2 = 0; x2 < width; x2++)
		{
			for (int i = 0; i < 4; i++)
			{
				pixels[((x + x2) + (y + y2) * this->width) * 4 + i] = value[i];
			}
		}
	}
	
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &bytes[0]);
}

/**
 * Get the closest greatest power of 2 for the width and height so
 * that the OpenGL texture wrapping can go over nicely.
 */
void Texture::genTexDimensions()
{
	//int pow = 2;
	//
	//while (pow < width)
	//{
	//	pow *= 2;
	//}
	//
	//texWid = (float)width / pow;
	//
	//pow = 2;
	//
	//while (pow < height)
	//{
	//	pow *= 2;
	//}
	//
	//texHei = (float)height / pow;
}

/**
 * Get the offsets needed for OpenGL to wrap the Texture to a
 * polygon.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (4).
 */
void Texture::getImageOffsets(float* dest)
{
	float w = 1;//texWid;
	float h = 1;//texHei;

	dest[0] = 0;
	dest[1] = 0;
	dest[2] = w;
	dest[3] = h;
}

/**
 * Get the offsets needed for OpenGL to wrap the Texture to a
 * polygon.
 * 
 * @return A float array containing the values for the offsets of
 * 		the Texture.
 */
float* Texture::getImageOffsets()
{
	float *dest = new float[4];

	getImageOffsets(dest);

	addOffsets(dest);

	return dest;
}

/**
 * Get whether or not the Texture is currently bound and ready to
 * be used.
 * 
 * @return Whether the Texture is bound or not.
 */
bool Texture::isBound()
{
	return currentId == id;
}

/**
 * Bind the Texture as the current Texture to be used.
 */
void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
	
	bind(id);
}

/**
 * Get the width of the Texture's source image file.
 * 
 * @return The width (in pixels) of the Texture.
 */
int Texture::getWidth()
{
	return width;
}

/**
 * Get the height of the Texture's source image file.
 * 
 * @return The height (in pixels) of the Texture.
 */
int Texture::getHeight()
{
	return height;
}

/**
 * Unbind the OpenGL Texture instance.
 */
void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);

	bind(0);
}

/**
 * Method to keep track of which Texture is currently bound.
 * 
 * @param id The id of the Texture that is being bound.
 */
void Texture::bind(int id)
{
	Texture::currentId = id;
}

/**
 * Add the pointer array that contains the offsets generated by a call
 * to genImageOffsets() to a vector of pointers to be deleted at the end
 * of the program.
 */
void Texture::addOffsets(float *offsets)
{
	this->offsets.push_back(offsets);
}

/**
 * Deallocate the memory created with the Texture class.
 */
void Texture::quit()
{
	for (int i = (int)offsets.size() - 1; i >= 0; i--)
	{
		delete[] offsets[i];

		offsets[i] = NULL;
	}
}