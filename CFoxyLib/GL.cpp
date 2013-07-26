#include "CFL.h"
#include <math.h>

bool				GL::initialized;
bool				GL::enabled3D;

float				GL::zClose, GL::zFar;
float				GL::fov;
float				GL::textureTolerance, GL::vertexTolerance;

int					GL::textureScaleMinMethod, GL::textureScaleMagMethod, GL::textureWrapSMethod, GL::textureWrapTMethod;

SDL_GLContext		GL::context;

Texture				GL::WHITE;

Color*				GL::color;

Stack<Color>		GL::colorStack, GL::clearColorStack;

Stack<float*>		GL::amountScaled, GL::amountTranslated, GL::amountRotated, GL::currentLocation;

const	int			GL::POINTS = GL_POINTS, GL::LINES = GL_LINES, GL::TRIANGLES = GL_TRIANGLES;

const	int			GL::ALL_ATTRIB_BITS = GL_ALL_ATTRIB_BITS, GL::ENABLE_BIT = GL_ENABLE_BIT, GL::FOG_BIT = GL_FOG_BIT,
					GL::LIGHTING_BIT = GL_LIGHTING_BIT, GL::LINE_BIT = GL_LINE_BIT, GL::POINT_BIT = GL_POINT_BIT,
					GL::POLYGON_BIT = GL_POLYGON_BIT, GL::TEXTURE_BIT = GL_TEXTURE_BIT,
					GL::COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT, GL::CURRENT_BIT = GL_CURRENT_BIT;

const	int 		GL::LINEAR = GL_LINEAR, GL::NEAREST = GL_NEAREST, GL::REPEAT = GL_REPEAT, GL::CLAMP = GL_CLAMP;

const	int			GL::CLEAR = GL_CLEAR, GL::SET = GL_SET, GL::COPY = GL_COPY, GL::COPY_INVERTED = GL_COPY_INVERTED,
					GL::NOOP = GL_NOOP, GL::INVERT = GL_INVERT, GL::AND = GL_AND, GL::NAND = GL_NAND, GL::OR = GL_OR, GL::NOR = GL_NOR,
					GL::XOR = GL_XOR, GL::EQUIV = GL_EQUIV, GL::AND_REVERSE = GL_AND_REVERSE, GL::AND_INVERTED = GL_AND_INVERTED,
					GL::OR_REVERSE = GL_OR_REVERSE, GL::OR_INVERTED = GL_OR_INVERTED;

const	string		GL::VERSION = "0.2";

vector<float*>		GL::floatData;
vector<Color*>		GL::colorData;

void GL::init()
{
	if (initialized)
	{
		return;
	}

	SDL_Window* window = Frame::getWindow();

	if (window != NULL)
	{
		createContext(window);
	}

	glewInit();

	//BufferedImage image = new BufferedImage(1, 1, BufferedImage.BITMASK);
	
	//Graphics g = image.createGraphics();
	//g.setColor(new Color(255, 255, 255, 255));
	//g.fillRect(0, 0, 1, 1);
	//g.dispose();
	
	//floatData = new vector<float*>();
	//colorData = new vector<Color*>();

	byte tex[4] = { 255, 255, 255, 255 };

	WHITE.loadTexture(tex, 1, 1);
	
	set3DEnabled(true);
	
	initGLStates();
	
	Color color(1, 1, 1, 1);

	colorStack.push(color);
	
	Color clearColor(1, 1, 1, 1);

	clearColorStack.push(clearColor);
	
	fov = 55;

	initialized = true;
}

/**
 * Initialize all of the OpenGL states that are required before
 * the use of the functions.
 */
void GL::initGLStates()
{
	glEnable(GL_TEXTURE_2D);
	
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
	
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f); 
	
	glFrontFace(GL_CCW);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	setTextureWrapSMethod(GL::REPEAT);
	setTextureWrapTMethod(GL::REPEAT);
	
	setTextureTolerance(0.0001f);
//		setVertexTolerance(0.001f);
	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//GL_DECAL);
	
	glEnable(GL_BLEND);
//		glBlendFunc(GL_ONE, GL_ONE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//		glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_CONSTANT_COLOR);
//		glDisable(GL_BLEND);
//		glDepthMask(true);
	
	float scaled[] = { 1, 1, 1 };

	amountScaled.push(scaled);
	
	float translated[] = { 0, 0, 0 };

	amountTranslated.push(translated);
	
	float location[] = { 0, 0, 0 };

	currentLocation.push(location);
	
	float rotated[] = { 0, 0, 0 };

	amountRotated.push(rotated);
}

/**
 * Initialize the orthographic view mode. This mode is used
 * for 2 dimensional viewing.
 * 
 * @param width The width of each OpenGL unit per pixel.
 * @param height The height of each OpenGL unit per pixel.
 */
void GL::viewOrtho(int width, int height)
{
	initGLStates();
	
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
	resetMatrix(); // Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	glOrtho(0, width, 0, height, -99999, 99999);
	glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
}

/**
 * Initialize the OpenGL perspective viewing mode.
 * 
 * @param width The width of the Frame of reference.
 * @param height The height of the Frame of reference.
 * @param zClose The closest index to the screen possible for
 * 		the zed axis.
 * @param zFar The farthest index to the screen possible for
 * 		the zed axis.
 */
void GL::viewPerspective(int width, int height, float zClose, float zFar)
{
	initGLStates();
	
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
//		glEnable(GL_TEXTURE_2D);
	
//		glEnable(GL_CULL_FACE);
	
//		glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	glClearDepth(1.0); // Depth Buffer Setup
	
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
	glLoadIdentity(); // Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	//gluPerspective(fov, (float)width / height, zClose, zFar);
//		glOrtho(1, 1, 1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix

	// Really Nice Perspective Calculations
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

/**
 * Get whether 3D rendering is enabled for OpenGL
 * 
 * @return Whether 3D rendering is enabled for OpenGL
 */
bool GL::is3DEnabled()
{
	return enabled3D;
}

/**
 * Set whether 3D rendering is enabled for OpenGL
 * 
 * @param enabled Whether 3D rendering is enabled for OpenGL
 */
void GL::set3DEnabled(bool enabled)
{
	GL::enabled3D = enabled;
}

/**
 * Get the integer variable that represents the method of
 * minification for OpenGL Textures.
 * 
 * @return The integer variable that represents the method of
 * minification for OpenGL Textures.
 */
int GL::getTextureScaleMinMethod()
{
	return textureScaleMinMethod;
}

/**
 * Get the integer variable that represents the method of
 * magnification for OpenGL Textures.
 * 
 * @return The integer variable that represents the method of
 * magnification for OpenGL Textures.
 */
int GL::getTextureScaleMagMethod()
{
	return textureScaleMagMethod;
}

/**
 * Set the Texture minification method when rendering Textures.
 * Possible methods include:<br>
 * NEAREST - Minify the Texture exactly as it is, with loss of pixels.<br>
 * LINEAR - Minify the Texture with estimation.<br>
 * 
 * @param method The method to set the minification to.
 */
void GL::setTextureScaleMinMethod(int method)
{
	GL::textureScaleMinMethod = method;
	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, method);
}

/**
 * Set the Texture magification method when rendering Textures.
 * Possible methods include:<br>
 * NEAREST - Magnify the Texture exactly as it is, without estimation.<br>
 * LINEAR - Magnify the Texture with estimation.
 * 
 * @param method The method to set the magnification to.
 */
void GL::setTextureScaleMagMethod(int method)
{
	GL::textureScaleMagMethod = method;
	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, method);
}

/**
 * Get the method that is used wrap Textures when they are rendered.
 * This only effects the horizontal view of the Texture.<br>
 * Possible methods include:<br>
 * CLAMP - When the object the Texture is rendered to is too large
 * 		for the Texture, clamp the Texture by continuing the
 * 		colors closest to the edge onward.<br>
 * REPEAT - When the object the Texture is rendered to is too large
 * 		for the Texture, repeat the Texture to fill the empty
 * 		space.
 * 
 * @return The method that is used wrap Textures when they are rendered
 * 		horizontally.
 */
int GL::getTextureWrapSMethod()
{
	return textureWrapSMethod;
}

/**
 * Get the method that is used wrap Textures when they are rendered.
 * This only effects the vertical view of the Texture.<br>
 * Possible methods include:<br>
 * CLAMP - When the object the Texture is rendered to is too large
 * 		for the Texture, clamp the Texture by continuing the
 * 		colors closest to the edge onward.<br>
 * REPEAT - When the object the Texture is rendered to is too large
 * 		for the Texture, repeat the Texture to fill the empty
 * 		space.
 * 
 * @return The method that is used wrap Textures when they are rendered
 * 		vertically.
 */
int GL::getTextureWrapTMethod()
{
	return textureWrapTMethod;
}

/**
 * Set the method to wrap Textures when they are rendered. This
 * only effects the horizontal view of the Texture.<br>
 * Possible methods include:<br>
 * CLAMP - When the object the Texture is rendered to is too large
 * 		for the Texture, clamp the Texture by continuing the
 * 		colors closest to the edge onward.<br>
 * REPEAT - When the object the Texture is rendered to is too large
 * 		for the Texture, repeat the Texture to fill the empty
 * 		space.
 * 
 * @param method The method to set the horizontal Texture wrap
 * 		method.
 */
void GL::setTextureWrapSMethod(int method)
{
	GL::textureWrapSMethod = method;
	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, method);
}

/**
 * Set the method to wrap Textures when they are rendered. This
 * only effects the vertical view of the Texture.<br>
 * Possible methods include:<br>
 * CLAMP - When the object the Texture is rendered to is too large
 * 		for the Texture, clamp the Texture by continuing the
 * 		colors closest to the edge onward.<br>
 * REPEAT - When the object the Texture is rendered to is too large
 * 		for the Texture, repeat the Texture to fill the empty
 * 		space.
 * 
 * @param method The method to set the vertical Texture wrap
 * 		method.
 */
void GL::setTextureWrapTMethod(int method)
{
	GL::textureWrapTMethod = method;
	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, method);
}

/**
 * Enables the ability to invert anything rendered.
 */
void GL::enableInverting()
{
	glEnable(GL_COLOR_LOGIC_OP);
}

/**
 * Begin inverting everything rendered with the specified mode.<br>
 * The modes include:<br>
 *
 * CLEAR - <br>
 * SET - <br>
 * COPY - <br>
 * COPY_INVERTED - <br>
 * NOOP - <br>
 * INVERT - <br>
 * AND - <br>
 * NAND - <br>
 * OR - <br>
 * NOR - <br>
 * XOR - <br>
 * EQUIV - <br>
 * AND_REVERSE - <br>
 * AND_INVERTED - <br>
 * OR_REVERSE - <br>
 * OR_INVERTED  - 
 * 
 * @param mode The mode in which to begin inverting.
 */
void GL::beginInverting(int mode)
{
	enableInverting();
	
	glLogicOp(mode);
}

/**
 * Begin inverting everything rendered according to the opposite
 * of their rgb values.
 */
void GL::beginInvertingNormal()
{
	beginInverting(COPY_INVERTED);
}

/**
 * Begins inverting everything rendered according to whatever is
 * being rendered behind it.
 */
void GL::beginInvertingBackground()
{
	beginInverting(GL_INVERT);
}

/**
 * Begins inverting everything by XORing them.
 */
void GL::beginInvertingXOR()
{
	beginInverting(GL_XOR);
}

/**
 * Ends the ability to invert anything rendered.
 */
void GL::endInverting()
{
	glDisable(GL_COLOR_LOGIC_OP);
}

/**
 * Enable the use of clipping the rendering to the screen.
 */
void GL::enableClipping()
{
	glEnable(GL_SCISSOR_TEST);
}

/**
 * Clip the area that will be rendered inside of to the screen. The
 * difference between this method and
 * beginFrameClipping(float, float, float, float) is that this method
 * takes into account the current scale amount and amount translated.
 * 
 * @param x The horizonal location to make the clip.
 * @param y The vertical location to make to clip.
 * @param width The horizontal size of the area to clip.
 * @param height The vertical size of the area to clip.
 */
void GL::beginClipping(float x, float y, float width, float height)
{
	float scale[3];
	
	getAmountScaled(scale);
	
	x      *= scale[0];
	y      *= scale[1];
	width  *= scale[0];
	height *= scale[1];
	
	float trans[3];
	
	getCurrentLocation(trans);
	
	x      += trans[0];
	y      += trans[1];
	
	beginFrameClipping(x, y, width, height);
}

/**
 * Stop clipping what is rendered to the screen.
 */
void GL::endClipping()
{
	endFrameClipping();
}

/**
 * Clip the area that will be rendered inside of to the screen. The
 * difference between this method and
 * beginClipping(float, float, float, float) is that this method does
 * not takes into account the current scale amount, and is based on
 * pixels. It also takes the absolute position from the screen.
 * 
 * @param x The horizonal location to make the clip.
 * @param y The vertical location to make to clip.
 * @param width The horizontal size of the area to clip.
 * @param height The vertical size of the area to clip.
 */
void GL::beginFrameClipping(float x, float y, float width, float height)
{
	enableClipping();
	
	glScissor(round(x), round(y), round(width), round(height));
}

/**
 * Stop clipping what is rendered to the screen.
 */
void GL::endFrameClipping()
{
	glDisable(GL_SCISSOR_TEST);
}

/**
 * Get the current version of OpenGL
 * 
 * @return The current version of OpenGL
 */
string GL::getOpenGLVersion()
{
	const GLubyte* f = glGetString(GL_VERSION);

	string version((char*)f);

	return version;
}

/**
 * Get the current version of CFoxyLib
 * 
 * @return The current version of CFoxyLib
 */
string GL::getVersion()
{
	return VERSION;
}

/**
 * Method used to push the specified object onto the stack.
 * 
 * @param bit The bit to push onto the stack.
 */
void GL::pushAttrib(int bit)
{
	glPushAttrib(bit);
}

/**
 * Pop the last added bit off of the stack and return to
 * the second latest mode.
 */
void GL::popAttrib()
{
	glPopAttrib();
}

/**
 * Get the current location that the matrix is at taking into account
 * the scale and the translations with the scale. Put the (x, y, z)
 * values of the current location into the destination array.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (3).
 */
void GL::getCurrentLocation(float* dest)
{
	float* copy = currentLocation.peek();
	
	for (int i = 0; i < 3; i++)
	{
		dest[i] = copy[i];
	}
}

/**
 * Get the current location that the matrix is at taking into account
 * the scale and the translations with the scale.
 * 
 * @return A float array with three values containing the (x, y, z)
 * 		values of the current location at the time of the call.
 */
float* GL::getCurrentLocation()
{
	int length  = 3;
	
	float *dest = genFloatData(length);

	getCurrentLocation(dest);

	return dest;
}

/**
 * Push the current matrix configuration to the stack.
 */
void GL::pushMatrix()
{
	glPushMatrix();
	
	float scaled[3];
	getAmountScaled(scaled);
	
	float trans[3];
	getAmountTranslated(trans);
	
	float rotated[3];
	getAmountRotated(rotated);
	
	float loc[3];
	getCurrentLocation(loc);

	amountScaled.push(scaled);
	amountTranslated.push(trans);
	amountRotated.push(rotated);
	currentLocation.push(loc);
}

/**
 * Pop the last matrix off of the stack. Returns the matrix
 * configuration to the second last configuration available on the
 * stack.
 */
void GL::popMatrix()
{
	glPopMatrix();
	
	amountScaled.pop();
	amountTranslated.pop();
	amountRotated.pop();
	currentLocation.pop();
}

/**
 * Rotates everything that is rendered after this method call
 * the specified x, y, and z amounts.<br>
 * Rotates the current matrix configuration the specified amounts.
 * 
 * @param x How many degrees to rotate around the x axis.
 * @param y How many degrees to rotate around the y axis.
 * @param z How many degrees to rotate around the z axis.
 */
void GL::rotate(float x, float y, float z)
{
	glRotatef(x, 1, 0, 0);
	glRotatef(y, 0, 1, 0);
	glRotatef(z, 0, 0, 1);
	
	float* array = amountRotated.peek();
	
	array[0] += x;
	array[1] += y;
	array[2] += z;
}

/**
 * Set the magnitude of the current rotation back to (0, 0, 0).
 */
void GL::unrotate()
{
	float* array = amountRotated.peek();
	
	rotate(-array[0], -array[1], -array[2]);
}

/**
 * Translate everything that is rendered after this method call
 * the specified x, y, and z amounts.<br>
 * Translates the current matrix configuration the specified amounts.
 * 
 * @param x The amount to translate along the x (horizontal) axis.
 * @param y The amount to translate along the y (vertical) axis.
 * @param z The amount to translate along the z (oblique) axis.
 */
void GL::translate(float x, float y, float z)
{
	glTranslatef(x, y, z);
	
	float* array = amountTranslated.peek();
	
	array[0] += x;
	array[1] += y;
	array[2] += z;
	
	float* scale = amountScaled.peek();
	
	array = currentLocation.peek();

	array[0] += x * scale[0];
	array[1] += y * scale[1];
	array[2] += z * scale[2];
}

/**
 * Set the location of the current translation back to (0, 0, 0).
 */
void GL::untranslate()
{
	float* array = amountTranslated.peek();
	
	translate(-array[0], -array[1], -array[2]);
}

/**
 * Translate everything that is rendered after this method call
 * the specified x, y, and z amounts.<br>
 * Translates the current matrix configuration the specified amounts.<br>
 * <br>
 * The difference between this and the translate() method is that this
 * method translates on a pixel basis, not on a scaled basis. What
 * this means is that no matter what the scale is, this will translate
 * the scene the same amount.<br>
 * <br>
 * This is essentially the same as calling this method:<br>
 * translate(x / scaleX, y / scaleY, z / scaleZ);
 * 
 * @param x The amount to translate along the x (horizontal) axis.
 * @param y The amount to translate along the y (vertical) axis.
 * @param z The amount to translate along the z (oblique) axis.
 */
void GL::translateIgnoreScale(float x, float y, float z)
{
	float scaled[3];
	
	getAmountScaled(scaled);
	
	translate(x / scaled[0], y / scaled[1], z / scaled[2]);
}

/**
 * Scale everything that is rendered after this method call
 * the specified amount int the x, y, and z axis.<br>
 * Scales the current matrix configuration the specified amounts.
 * 
 * @param x The amount to scale horizontally what is rendered.
 * @param y The amount to scale vertically what is rendered.
 * @param z The amount to scale obliquely what is rendered.
 */
void GL::scale(float x, float y, float z)
{
	glScalef(x, y, z);
	
	float* array = amountScaled.peek();
	
	array[0] *= x;
	array[1] *= y;
	array[2] *= z;
}

/**
 * Set the scale of the current matrix back to (1, 1, 1).
 */
void GL::unscale()
{
	float scaled[3];
	
	getAmountScaled(scaled);
	
	float x = 1 / scaled[0];
	float y = 1 / scaled[1];
	float z = 1 / scaled[2];
	
	glScalef(x, y, z);
	
	float* array = amountScaled.peek();
	
	array[0] *= x;
	array[1] *= y;
	array[2] *= z;
}

/**
 * Get the amount that the current matrix has been scaled up to
 * this method call. Put the (x, y, z) values of how much
 * the current matrix has been scaled into the destination array.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (3).
 */
void GL::getAmountScaled(float* dest)
{
	float* copy = amountScaled.peek();
	
	for (int i = 0; i < 3; i++)
	{
		dest[i] = copy[i];
	}
}

/**
 * Get the amount that the current matrix has been scaled up to
 * this method call.
 * 
 * @return A float array containing three values that correspond
 * 		to the (x, y, z) amount scaled.
 */
float* GL::getAmountScaled()
{
	int length  = 3;
	
	float *dest = genFloatData(length);

	getAmountScaled(dest);

	return dest;
}

/**
 * Get the amount that the current matrix has been translated by up
 * to this method call. Put the (x, y, z) values of how much
 * the current matrix has been translated into the destination array.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (3).
 */
void GL::getAmountTranslated(float* dest)
{
	float* copy = amountTranslated.peek();
	
	for (int i = 0; i < 3; i++)
	{
		dest[i] = copy[i];
	}
}

/**
 * Get the amount that the current matrix has been translated by up
 * to this method call.
 * 
 * @return A float array containing three values that correspond
 * 		to the (x, y, z) amount translated.
 */
float* GL::getAmountTranslated()
{
	int length  = 3;
	
	float *dest = genFloatData(length);

	getAmountTranslated(dest);

	return dest;
}

/**
 * Get the amount that the current matrix has been rotated by up
 * to this method call. Put the (x, y, z) values of how much
 * the current matrix has been rotated into the destination array.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (3).
 */
void GL::getAmountRotated(float *dest)
{
	float* copy = amountRotated.peek();
	
	for (int i = 0; i < 3; i++)
	{
		dest[i] = copy[i];
	}
}

/**
 * Get the amount that the current matrix has been rotated by up
 * to this method call.
 * 
 * @return A float array containing three values that correspond
 * 		to the (x, y, z) amount rotated.
 */
float* GL::getAmountRotated()
{
	int length  = 3;
	
	float *dest = genFloatData(length);

	getAmountRotated(dest);

	return dest;
}

/**
 * Get the tolerance in which the Textures will  be generated with.
 * This determines how far to keep from overlapping textures on
 * a SpriteSheet or image.
 * 
 * @return The tolerance in which the Textures will be generated
 * 		with.
 */
float GL::getTextureTolerance()
{
	return textureTolerance;
}

/**
 * Set the tolerance in which the Textures will  be generated with.
 * This determines how far to keep from overlapping textures on
 * a SpriteSheet or image.
 * 
 * @param textureTolerance The tolerance in which the Textures
 * 		will be generated with.
 */
void GL::setTextureTolerance(float textureTolerance)
{
	GL::textureTolerance = textureTolerance;
}

/**
 * Set the tolerance in which the Vertices will  be generated with.
 * This determines how much of a buffer to make for the vertices to
 * make sure that no empty space is left in between any adjacent
 * polygons.
 * 
 * @return The tolerance in which the Vertices will  be generated
 * 		with.
 */
float GL::getVertexTolerance()
{
	return vertexTolerance;
}

/**
 * Get the tolerance in which the Vertices will  be generated with.
 * This determines how much of a buffer to make for the vertices to
 * make sure that no empty space is left in between any adjacent
 * polygons.
 * 
 * @return The tolerance in which the Vertices will  be generated
 * 		with.
 */
void GL::setVertexTolerance(float vertexTolerance)
{
	GL::vertexTolerance = vertexTolerance;
}

//	/**
//	 * 
//	 * 
//	 * @param x
//	 * @param y
//	 * @param width
//	 * @param height
//	 */
//	void drawRect(int x, int y, int width, int height)
//	{
//		glBegin(GL_QUADS);
//		{
//			glVertex2f(x, y);
//			glVertex2f(x + width, y);
//			glVertex2f(x + width, y + height);
//			glVertex2f(x, y + height);
//		}
//		glEnd();
//	}

//	/**
//	 * 
//	 * 
//	 * @param x
//	 * @param y
//	 * @param width
//	 * @param height
//	 * @param texture
//	 */
//	void drawRect(int x, int y, int width, int height, Texture texture)
//	{
//		texture.bind();
//		float offsets[] = texture.getImageOffsets();
//		
//		glBegin(GL_QUADS);
//		{
//			glVertex2f(x, y);
//			glTexCoord2f(offsets[0], offsets[1]);
//			glVertex2f(x + width, y);
//			glTexCoord2f(offsets[0], offsets[3]);
//			glVertex2f(x + width, y + height);
//			glTexCoord2f(offsets[2], offsets[3]);
//			glVertex2f(x, y + height);
//			glTexCoord2f(offsets[2], offsets[1]);
//		}
//		glEnd();
//	}

/**
 * Get the current color that is being used by OpenGL.
 * 
 * @param dest The destination Color pointer.
 */
void GL::getColor(Color* dest)
{
	Color copy = colorStack.peek();
	
	dest->setData(copy.getRedf(), copy.getGreenf(), copy.getBluef(), copy.getAlphaf());
}

/**
 * Get the current color that is being used by OpenGL.
 * 
 * @return A Color instance holding the values.
 */
Color* GL::getColor()
{
	Color *dest = genColorData();

	getColor(dest);

	return dest;
}

/**
 * Get the current color that is being used by OpenGL and put
 * the in the specified float array with the values for the
 * (r, g, b, a) color in the current state of OpenGL.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (4).
 */
void GL::getColorArray(float* dest)
{
	Color copy = colorStack.peek();
	
	dest[0] = copy.getRedf();
	dest[1] = copy.getGreenf();
	dest[2] = copy.getBluef();
	dest[3] = copy.getAlphaf();
	
//		FloatBuffer buffer = BufferUtils.createFloatBuffer(4 * 4);
//		
//		glGetFloat(GL_CURRENT_COLOR, buffer);
//		
//		color[0] = buffer.get(0);
//		color[1] = buffer.get(1);
//		color[2] = buffer.get(2);
//		color[3] = buffer.get(3);
}

/**
 * Get the current color that is being used by OpenGL.
 * 
 * @return A float array describing the float values for the
 * 		(r, g, b, a) color in the current state.
 */
float* GL::getColorArray()
{
	int length  = 4;

	float *dest = genFloatData(length);

	getColorArray(dest);

	return dest;
}

/**
 * Set the color that everything rendered will be affected by.
 * Accepts values (0 - 1).
 * 
 * @param r The red component (0.0 - 1.0).
 * @param g The green component (0.0 - 1.0).
 * @param b The blue component (0.0 - 1.0).
 * @param a The alpha component (0.0 - 1.0).
 */
void GL::setColor(float r, float g, float b, float a)
{
	glColor4f(r, g, b, a);
	
	Color color = colorStack.peek();
	
	color.setData(r, g, b, a);
}

/**
 * Set the color that everything rendered will be affected by.
 * Accepts values (0 - 1).
 * 
 * @param color A Color instance that describes a rgba Color.
 */
void GL::setColor(Color* color)
{
	setColor(color->getRedf(), color->getGreenf(), color->getBluef(), color->getAlphaf());
}

/**
 * Set the color that everything rendered will be affected by.
 * Accepts values (0 - 1).
 * 
 * @param color A 4 float large array that contains the (r, g, b, a)
 * 		values in order.
 */
void GL::setColor(float color[])
{
	setColor(color[0], color[1], color[2], color[3]);
}

/**
 * Get the current color that is being used by OpenGL to clear the
 * Display each frame.
 * 
 * @param dest The destination Color pointer. Size must be >= (4).
 */
void GL::getClearColor(Color* dest)
{
	Color copy = clearColorStack.peek();
	
	dest->setData(copy.getRedf(), copy.getGreenf(), copy.getBluef(), copy.getAlphaf());
}

/**
 * Get the current color that is being used by OpenGL to clear the
 * Display each frame.
 * 
 * @return A Color instance holding the values.
 */
Color* GL::getClearColor()
{
	Color *dest = genColorData();

	getClearColor(dest);

	return dest;
}

/**
 * Set the color that the Frame will clear the scene with.
 * 
 * @param r The red component (0.0 - 1.0).
 * @param g The green component (0.0 - 1.0).
 * @param b The blue component (0.0 - 1.0).
 * @param a The alpha component (0.0 - 1.0).
 */
void GL::setClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	
	Color color = clearColorStack.peek();
	
	color.setData(r, g, b, a);
}

/**
 * Set the color that everything rendered will be cleared by.
 * Accepts values (0 - 1).
 * 
 * @param color A Color instance that describes a rgba Color.
 */
void GL::setClearColor(Color* color)
{
	setClearColor(color->getRedf(), color->getGreenf(), color->getBluef(), color->getAlphaf());
}

/**
 * Reset the matrix of all translations and scales.
 */
void GL::resetMatrix()
{
	glLoadIdentity();
}

/**
 * Get the float value of the Field of View.
 * 
 * @return The float value of the Field of View.
 */
float GL::getFOV()
{
	return fov;
}

/**
 * Set the float value of the Field of View.
 * 
 * @param FOV The float value of the Field of View.
 */
void GL::setFOV(float FOV)
{
	GL::fov = FOV;
}

/**
 * Populate a float array with values that describe a
 * 2 dimensional rectangle's vertices.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (3 * 2 * 2).
 * @param x The horizontal location of the rectangle.
 * @param y The vertical location of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 */
void GL::genRectVerts(float* dest, float x, float y, float width, float height)
{
	int index = 0;
	
	x      -= vertexTolerance;
	width  += vertexTolerance * 2;
	y      -= vertexTolerance;
	height += vertexTolerance * 2;
	
//		New TRIANGLE method.
	dest[index++] = x;
	dest[index++] = y;

	dest[index++] = x + width;
	dest[index++] = y + height;

	dest[index++] = x;
	dest[index++] = y + height;
	
	
	dest[index++] = x;
	dest[index++] = y;

	dest[index++] = x + width;
	dest[index++] = y;

	dest[index++] = x + width;
	dest[index++] = y + height;
}

/**
 * Populate a float array with values that describe a
 * 2 dimensional rectangle's vertices.
 * 
 * @param x The horizontal location of the rectangle.
 * @param y The vertical location of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 */
float* GL::genRectVerts(float x, float y, float width, float height)
{
	int length  = 3 * 2 * 2;

	float *dest = genFloatData(length);

	genRectVerts(dest, x, y, width, height);

	return dest;
}

/**
 * Populate a float array with values that describe a
 * 2 dimensional rectangle's vertices with depth.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (3 * 2 * 2).
 * @param x The horizontal location of the rectangle.
 * @param y The vertical location of the rectangle.
 * @param z The oblique location of the rectangle (depth).
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 */
void GL::genRectVerts(float* dest, float x, float y, float z, float width, float height)
{
	int index = 0;
	
	// Front
	dest[index++] = x;
	dest[index++] = y;
	dest[index++] = z;
	
	dest[index++] = x + width;
	dest[index++] = y;
	dest[index++] = z;
	
	dest[index++] = x + width;
	dest[index++] = y + height;
	dest[index++] = z;
	
	dest[index++] = x;
	dest[index++] = y + height;
	dest[index++] = z;
}

/**
 * Generate a float array containing values that describe a
 * 2 dimensional rectangle's vertices with depth.
 * 
 * @param x The horizontal location of the rectangle.
 * @param y The vertical location of the rectangle.
 * @param z The oblique location of the rectangle (depth).
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @return The generated float array containing the values.
 */
float* GL::genRectVerts(float x, float y, float z, float width, float height)
{
	int length  = 3 * 2 * 2;

	float *dest = genFloatData(length);

	genRectVerts(dest, x, y, z, width, height);

	return dest;
}

/**
 * Populate a float array with values that describe a
 * 2 dimensional rectangle's texture coordinates to map on
 * vertices.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (3 * 2 * 2).
 * @param texture The texture to generate the values for.
 */
void GL::genRectTextures(float *dest, Texture *texture)
{
	float offsets[4];
	texture->getImageOffsets(offsets);

	genRectTextures(dest, offsets);
}

/**
 * Generate a float array containing values that describe a
 * 2 dimensional rectangle's texture coordinates to map on
 * vertices.
 * 
 * @param texture The texture to generate the values for.
 * @return The generated float array containing the values.
 */
float* GL::genRectTextures(Texture *texture)
{
	int length  = 3 * 2 * 2;

	float *dest = genFloatData(length);

	genRectTextures(dest, texture);

	return dest;
}

/**
 * Populate a float array with values that describe a
 * 2 dimensional rectangle's texture coordinates to map on
 * vertices. The texture will be repeated the specified amount on
 * each of the axiis.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (3 * 2 * 2).
 * @param texture The texture to generate the values for.
 * @param rx The amount of times to repeat the Texture horizontally.
 * @param ry The amount of times to repeat the Texture vertically.
 */
void GL::genRectTextures(float *dest, Texture *texture, int rx, int ry)
{
	float offsets[4];
	texture->getImageOffsets(offsets);

	genRectTextures(dest, offsets, rx, ry);
}

/**
 * Generate a float array containing values that describe a
 * 2 dimensional rectangle's texture coordinates to map on
 * vertices. The texture will be repeated the specified amount on
 * each of the axiis.
 * 
 * @param texture The texture to generate the values for.
 * @param rx The amount of times to repeat the Texture horizontally.
 * @param ry The amount of times to repeat the Texture vertically.
 * @return The generated float array containing the values.
 */
float* GL::genRectTextures(Texture *texture, int rx, int ry)
{
	int length  = 3 * 2 * 2;

	float *dest = genFloatData(length);

	genRectTextures(dest, texture, rx, ry);

	return dest;
}

/**
 * Popluate a float array with values that describe a
 * 2 dimensional rectangle's texture coordinates to map on
 * vertices. The texture can be mirrored horizontally and/or
 * vertically depending on the values passed to the parameters.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (3 * 2 * 2).
 * @param texture The texture to generate the values for.
 * @param mirrorHorizontal Whether or not to mirror the Texture
 * 		horizontally.
 * @param mirrorVertical Whether or not to mirror the Texture
 * 		vertically.
 */
void GL::genRectTextures(float *dest, Texture *texture, bool mirrorHorizontal, bool mirrorVertical)
{
	float offsets[4];
	texture->getImageOffsets(offsets);

	genRectTextures(dest, offsets, mirrorHorizontal, mirrorVertical);
}

/**
 * Generate a float array containing values that describe a
 * 2 dimensional rectangle's texture coordinates to map on
 * vertices. The texture can be mirrored horizontally and/or
 * vertically depending on the values passed to the parameters.
 * 
 * @param texture The texture to generate the values for.
 * @param mirrorHorizontal Whether or not to mirror the Texture
 * 		horizontally.
 * @param mirrorVertical Whether or not to mirror the Texture
 * 		vertically.
 * @return The generated float array containing the values.
 */
float* GL::genRectTextures(Texture *texture, bool mirrorHorizontal, bool mirrorVertical)
{
	int length  = 3 * 2 * 2;

	float *dest = genFloatData(length);

	genRectTextures(dest, texture, mirrorHorizontal, mirrorVertical);

	return dest;
}

/**
 * Populate a float array with values that describe a
 * 2 dimensional rectangle's texture coordinates to map on
 * vertices.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (3 * 2 * 2).
 * @param offsets The offsets of the Texture that will be used to
 * 		generate the float array.
 */
void GL::genRectTextures(float *dest, float *offsets)
{
	genRectTextures(dest, offsets, 1, 1, false, false);
}

/**
 * Generate a float array containing values that describe a
 * 2 dimensional rectangle's texture coordinates to map on
 * vertices.
 * 
 * @param offsets The offsets of the Texture that will be used to
 * 		generate the float array.
 * @return The generated float array containing the values.
 */
float* GL::genRectTextures(float *offsets)
{
	int length  = 3 * 2 * 2;

	float *dest = genFloatData(length);

	genRectTextures(dest, offsets);

	return dest;
}

/**
 * Populate a float array with values that describe a
 * 2 dimensional rectangle's texture coordinates to map on
 * vertices.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (3 * 2 * 2).
 * @param offsets The offsets of the Texture that will be used to
 * 		generate the float array.
 * @param rx The amount of times to repeat the Texture horizontally.
 * @param ry The amount of times to repeat the Texture vertically.
 */
void GL::genRectTextures(float *dest, float *offsets, int rx, int ry)
{
	genRectTextures(dest, offsets, rx, ry, false, false);
}

/**
 * Generate a float array containing values that describe a
 * 2 dimensional rectangle's texture coordinates to map on
 * vertices.
 * 
 * @param offsets The offsets of the Texture that will be used to
 * 		generate the float array.
 * @param rx The amount of times to repeat the Texture horizontally.
 * @param ry The amount of times to repeat the Texture vertically.
 * @return The generated float array containing the values.
 */
float* GL::genRectTextures(float *offsets, int rx, int ry)
{
	int length  = 3 * 2 * 2;

	float *dest = genFloatData(length);

	genRectTextures(dest, offsets, rx, ry);

	return dest;
}

/**
 * Populate a float array with values that describe a
 * 2 dimensional rectangle's texture coordinates to map on
 * vertices.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (3 * 2 * 2).
 * @param offsets The offsets of the Texture that will be used to
 * 		generate the float array.
 * @param mirrorHorizontal Whether or not to mirror the Texture
 * 		horizontally.
 * @param mirrorVertical Whether or not to mirror the Texture
 * 		vertically.
 */
void GL::genRectTextures(float *dest, float *offsets, bool mirrorHorizontal, bool mirrorVertical)
{
	genRectTextures(dest, offsets, 1, 1, mirrorHorizontal, mirrorVertical);
}

/**
 * Generate a float array containing values that describe a
 * 2 dimensional rectangle's texture coordinates to map on
 * vertices.
 * 
 * @param offsets The offsets of the Texture that will be used to
 * 		generate the float array.
 * @param mirrorHorizontal Whether or not to mirror the Texture
 * 		horizontally.
 * @param mirrorVertical Whether or not to mirror the Texture
 * 		vertically.
 * @return The generated float array containing the values.
 */
float* GL::genRectTextures(float *offsets, bool mirrorHorizontal, bool mirrorVertical)
{
	int length  = 3 * 2 * 2;

	float *dest = genFloatData(length);

	genRectTextures(dest, offsets, mirrorHorizontal, mirrorVertical);

	return dest;
}

/**
 * Populate a float array with values that describe a
 * 2 dimensional rectangle's texture coordinates to map on
 * vertices.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (3 * 2 * 2).
 * @param offsets The offsets of the Texture that will be used to
 * 		generate the float array.
 * @param rx The amount of times to repeat the Texture horizontally.
 * @param ry The amount of times to repeat the Texture vertically.
 * @param mirrorHorizontal Whether or not to mirror the Texture
 * 		horizontally.
 * @param mirrorVertical Whether or not to mirror the Texture
 * 		vertically.
 */
void GL::genRectTextures(float *dest, float *offsets, int rx, int ry, bool mirrorHorizontal, bool mirrorVertical)
{
	int index = 0;
	
	if (mirrorHorizontal)
	{
		index = 0;
		
		dest[index] = rx * offsets[2] - textureTolerance;// * 2;
		index += 2;
		
		dest[index] = rx * offsets[0] + textureTolerance;
		index += 2;
		
		dest[index] = rx * offsets[2] - textureTolerance;// * 2;
		index += 2;
		
		
		dest[index] = rx * offsets[2] - textureTolerance;// * 2;
		index += 2;
		
		dest[index] = rx * offsets[0] + textureTolerance;
		index += 2;
		
		dest[index] = rx * offsets[0] + textureTolerance;
		index += 2;
	}
	else
	{
		dest[index] = rx * offsets[0] + textureTolerance;
		index += 2;
		
		dest[index] = rx * offsets[2] - textureTolerance;// * 2;
		index += 2;
		
		dest[index] = rx * offsets[0] + textureTolerance;
		index += 2;
		

		dest[index] = rx * offsets[0] + textureTolerance;
		index += 2;
		
		dest[index] = rx * offsets[2] - textureTolerance;// * 2;
		index += 2;
		
		dest[index] = rx * offsets[2] - textureTolerance;// * 2;
		index += 2;
	}
	
	if (mirrorVertical)
	{
		index = 1;
		
		dest[index] = ry * offsets[3] - textureTolerance;// * 2;
		index += 2;
		
		dest[index] = ry * offsets[1] + textureTolerance;
		index += 2;

		dest[index] = ry * offsets[1] + textureTolerance;
		index += 2;
		
		
		dest[index] = ry * offsets[3] - textureTolerance;// * 2;
		index += 2;
		
		dest[index] = ry * offsets[3] - textureTolerance;// * 2;
		index += 2;
		
		dest[index] = ry * offsets[1] + textureTolerance;
		index += 2;
	}
	else
	{
		index = 1;
		
		dest[index] = ry * offsets[1] + textureTolerance;
		index += 2;

		dest[index] = ry * offsets[3] - textureTolerance;// * 2;
		index += 2;
		
		dest[index] = ry * offsets[3] - textureTolerance;// * 2;
		index += 2;
		
		
		dest[index] = ry * offsets[1] + textureTolerance;
		index += 2;
		
		dest[index] = ry * offsets[1] + textureTolerance;
		index += 2;
		
		dest[index] = ry * offsets[3] - textureTolerance;// * 2;
		index += 2;
	}
}

/**
 * Generate a float array containing values that describe a
 * 2 dimensional rectangle's texture coordinates to map on
 * vertices.
 * 
 * @param offsets The offsets of the Texture that will be used to
 * 		generate the float array.
 * @param rx The amount of times to repeat the Texture horizontally.
 * @param ry The amount of times to repeat the Texture vertically.
 * @param mirrorHorizontal Whether or not to mirror the Texture
 * 		horizontally.
 * @param mirrorVertical Whether or not to mirror the Texture
 * 		vertically.
 * @return The generated float array containing the values.
 */
float* GL::genRectTextures(float *offsets, int rx, int ry, bool mirrorHorizontal, bool mirrorVertical)
{
	int length  = 3 * 2 * 2;

	float *dest = genFloatData(length);

	genRectTextures(dest, offsets, rx, ry, mirrorHorizontal, mirrorVertical);

	return dest;
}

/**
 * Populate a float array with values that describe a
 * 3 dimensional cube's vertices.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (3 * 2 * 6 * 3).
 * @param x The horizontal location of the cube.
 * @param y The vertical location of the cube.
 * @param z The oblique location of the cube.
 * @param width The width of the cube.
 * @param height The height of the cube.
 * @param depth The depth of the cube.
 */
void GL::genCubeVerts(float* dest, float x, float y, float z, float width, float height, float depth)
{
	depth *= -1;
	
	int index = 0;

	x -= vertexTolerance;
	width += vertexTolerance * 2;
	y -= vertexTolerance;
	height += vertexTolerance * 2;
	z += vertexTolerance;
	depth -= vertexTolerance * 2;
	
	// Front.
	dest[index++] = x;
	dest[index++] = y;
	dest[index++] = z;
	
	dest[index++] = x + width;
	dest[index++] = y + height;
	dest[index++] = z;

	dest[index++] = x;
	dest[index++] = y + height;
	dest[index++] = z;
	
	
	dest[index++] = x;
	dest[index++] = y;
	dest[index++] = z;

	dest[index++] = x + width;
	dest[index++] = y;
	dest[index++] = z;

	dest[index++] = x + width;
	dest[index++] = y + height;
	dest[index++] = z;
	
	// Back.
	dest[index++] = x + width;
	dest[index++] = y;
	dest[index++] = z + depth;

	dest[index++] = x;
	dest[index++] = y + height;
	dest[index++] = z + depth;
	
	dest[index++] = x + width;
	dest[index++] = y + height;
	dest[index++] = z + depth;
	

	dest[index++] = x + width;
	dest[index++] = y;
	dest[index++] = z + depth;

	dest[index++] = x;
	dest[index++] = y;
	dest[index++] = z + depth;

	dest[index++] = x;
	dest[index++] = y + height;
	dest[index++] = z + depth;

	
	// Left.
	dest[index++] = x;
	dest[index++] = y;
	dest[index++] = z + depth;

	dest[index++] = x;
	dest[index++] = y + height;
	dest[index++] = z;

	dest[index++] = x;
	dest[index++] = y + height;
	dest[index++] = z + depth;
	
	
	dest[index++] = x;
	dest[index++] = y;
	dest[index++] = z + depth;

	dest[index++] = x;
	dest[index++] = y;
	dest[index++] = z;

	dest[index++] = x;
	dest[index++] = y + height;
	dest[index++] = z;
	

	// Right.
	dest[index++] = x + width;
	dest[index++] = y;
	dest[index++] = z;

	dest[index++] = x + width;
	dest[index++] = y + height;
	dest[index++] = z + depth;

	dest[index++] = x + width;
	dest[index++] = y + height;
	dest[index++] = z;
	
	
	dest[index++] = x + width;
	dest[index++] = y;
	dest[index++] = z;

	dest[index++] = x + width;
	dest[index++] = y;
	dest[index++] = z + depth;

	dest[index++] = x + width;
	dest[index++] = y + height;
	dest[index++] = z + depth;
	

	// Top.
	dest[index++] = x;
	dest[index++] = y + height;
	dest[index++] = z;

	dest[index++] = x + width;
	dest[index++] = y + height;
	dest[index++] = z + depth;

	dest[index++] = x;
	dest[index++] = y + height;
	dest[index++] = z + depth;
	
	
	dest[index++] = x;
	dest[index++] = y + height;
	dest[index++] = z;

	dest[index++] = x + width;
	dest[index++] = y + height;
	dest[index++] = z;

	dest[index++] = x + width;
	dest[index++] = y + height;
	dest[index++] = z + depth;


	// Bottom.
	dest[index++] = x;
	dest[index++] = y;
	dest[index++] = z + depth;

	dest[index++] = x + width;
	dest[index++] = y;
	dest[index++] = z;

	dest[index++] = x;
	dest[index++] = y;
	dest[index++] = z;
	
	
	dest[index++] = x;
	dest[index++] = y;
	dest[index++] = z + depth;

	dest[index++] = x + width;
	dest[index++] = y;
	dest[index++] = z + depth;

	dest[index++] = x + width;
	dest[index++] = y;
	dest[index++] = z;
}

/**
 * Generate a float array containing values that describe a
 * 3 dimensional cube's vertices.
 * 
 * @param x The horizontal location of the cube.
 * @param y The vertical location of the cube.
 * @param z The oblique location of the cube.
 * @param width The width of the cube.
 * @param height The height of the cube.
 * @param depth The depth of the cube.
 * @return The generated float array containing the values.
 */
float* GL::genCubeVerts(float x, float y, float z, float width, float height, float depth)
{
	int length  = 3 * 2 * 6 * 3;

	float *dest = genFloatData(length);

	genCubeVerts(dest, x, y, z, width, height, depth);

	return dest;
}

/**
 * Populate a float array with values that describe an
 * (r, g, b, a) color's values that are used for Color Buffers.
 * 
 * @param dest The destination float array to put the values in.
 * 		The size of the array must be >= (4 * 4).
 * @param r The red component of the Color (0.0 - 1.0).
 * @param g The green component of the Color (0.0 - 1.0).
 * @param b The blue component of the Color (0.0 - 1.0).
 * @param a The alpha component of the Color (0.0 - 1.0).
 */
void GL::genRectColors(float *dest, float r, float g, float b, float a)
{
	int index = 0;
	
	dest[index++] = r;
	dest[index++] = g;
	dest[index++] = b;
	dest[index++] = a;
	
	dest[index++] = r;
	dest[index++] = g;
	dest[index++] = b;
	dest[index++] = a;
	
	dest[index++] = r;
	dest[index++] = g;
	dest[index++] = b;
	dest[index++] = a;
	
	dest[index++] = r;
	dest[index++] = g;
	dest[index++] = b;
	dest[index++] = a;
}

/**
 * Generate a float array containing values that describe an
 * (r, g, b, a) color's values that are used for Color Buffers.
 * 
 * @param r The red component of the Color (0.0 - 1.0).
 * @param g The green component of the Color (0.0 - 1.0).
 * @param b The blue component of the Color (0.0 - 1.0).
 * @param a The alpha component of the Color (0.0 - 1.0).
 * @return The generated float array containing the values.
 */
float* GL::genRectColors(float r, float g, float b, float a)
{
	int length  = 4 * 4;

	float *dest = genFloatData(length);

	genRectColors(dest, r, g, b, a);

	return dest;
}

/**
 * Add the specified data to the list of generated float data so that
 * it can be deleted at shut-down time.
 * 
 * @param data The data to add to the list.
 */
float* GL::genFloatData(int length)
{
	//floatData->insert(floatData->end(), &data, &data + length);

	float *data = new float[length];

	floatData.push_back(data);

	return data;//floatData[floatData->size() - length];
}

/**
 * Add the specified data to the list of generated float data so that
 * it can be deleted at shut-down time.
 * 
 * @param data The data to add to the list.
 */
Color* GL::genColorData()
{
	Color *data = new Color();

	colorData.push_back(data);

	return data;
}

/**
 * Round the float value to the rounded integer value.
 * 
 * @param value The float value to round.
 * @return The rounded integer value.
 */
int GL::round(float value)
{
	return (int)floor(value + 0.5);
}

/**
 * Get the current GLContext that is being used.
 * 
 * @return The SDL_GLContext instance that is being used.
 */
SDL_GLContext GL::getContext()
{
	return context;
}

/**
 * Create the OpenGL Context if it has not been created yet.
 */
bool GL::createContext(SDL_Window* window)
{
	if (context == NULL)
	{
		context = SDL_GL_CreateContext(window);

		return true;
	}

	return false;
}

/**
 * Quit the GL functionality.
 */
void GL::quit()
{
	delete color;

	for (int i = floatData.size() - 1; i >= 0; i--)
	{
		delete[] floatData[i];
	}

	for (int i = colorData.size() - 1; i >= 0; i--)
	{
		delete colorData[i];
	}

	color = NULL;

	SDL_GL_DeleteContext(context);

	Frame::quit();

	SDL_Quit();
}