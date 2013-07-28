#include "CFL.h"

using lodepng::load_file;
using lodepng::decode;

vector<fbyte*>	FoxyImage::images;

/**
 * Generate an image to read data from at the specified location.
 * 
 * @param location The location of the Image in the relative file
 *		system.
 * @return The SDL_Image created from the image at the location.
 */
FoxyImage::FoxyImage(string location)
{
	//SDL_Surface *image;

	vector<fbyte> buffer;

	load_file(buffer, location);

	unsigned int w, h;
	unsigned int error = decode(data, w, h, buffer);

	if (error)
	{
		cout << "Decoder error for image '" << location << "': " << lodepng_error_text(error) << endl;
	}

	width  = w;
	height = h;
}

/**
 * Destruct the FoxyImage and deallocate the memory.
 */
FoxyImage::~FoxyImage()
{
	//delete[] data;
}

/**
 * Get the width of the image.
 * 
 * @return The horizontal size of the image.
 */
int FoxyImage::getWidth()
{
	return width;
}

/**
 * Get the height of the image.
 * 
 * @return The vertical size of the image.
 */
int FoxyImage::getHeight()
{
	return height;
}

fbyte* FoxyImage::getData()
{
	return &data[0];
}

/**
 * Add an image to the list of images created in order to keep track
 * of its memory location when deallocation occurs.
 * 
 * @param image The SDL_Surface to add to the vector.
 */
void FoxyImage::addImage(fbyte *image)
{
	images.push_back(image);
}