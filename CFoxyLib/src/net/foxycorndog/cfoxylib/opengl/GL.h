#ifndef GL_H
#define GL_H

#include "CFL.h"

class GL
{
private:
	static bool				initialized;
	static bool				enabled3D;

	static float			zClose, zFar;
	static float			fov;
	static float			textureTolerance, vertexTolerance;

	static int				textureScaleMinMethod, textureScaleMagMethod, textureWrapSMethod, textureWrapTMethod;

	static SDL_GLContext	context;

	static Color*			color;

	static vector<float*>	floatData;
	static vector<Color*>	colorData;

	static Stack<Color>		colorStack, clearColorStack;
	static Stack<float*>	amountScaled, amountTranslated, amountRotated, currentLocation;

	static void		initGLStates();
	static void		enableClipping();
	static void		deleteMatrixStacks();

	static int		round(float);

	static float*	genFloatData(int);
	static Color*	genColorData();

public:
	static Texture			WHITE;

	static const int		POINTS, LINES, TRIANGLES;
	static const int		ALL_ATTRIB_BITS, ENABLE_BIT, FOG_BIT, LIGHTING_BIT, LINE_BIT, POINT_BIT, POLYGON_BIT,
							TEXTURE_BIT, COLOR_BUFFER_BIT, CURRENT_BIT;
	static const int		LINEAR, NEAREST, REPEAT, CLAMP;
	static const int		CLEAR, SET, COPY, COPY_INVERTED, NOOP, INVERT, AND, NAND, OR, NOR, XOR, EQUIV,
							AND_REVERSE, AND_INVERTED, OR_REVERSE, OR_INVERTED;

	static const string		VERSION;

	static void				init();
	static void				viewOrtho(int, int);
	static void				viewPerspective(int, int, float, float);
	static void				set3DEnabled(bool);
	static void				setTextureScaleMinMethod(int);
	static void				setTextureScaleMagMethod(int);
	static void				setTextureWrapTMethod(int);
	static void				setTextureWrapSMethod(int);
	static void				enableInverting();
	static void				beginInverting(int);
	static void				beginInvertingNormal();
	static void				beginInvertingBackground();
	static void				beginInvertingXOR();
	static void				endInverting();
	static void				beginClipping(float, float, float, float);
	static void				endClipping();
	static void				beginFrameClipping(float, float, float, float);
	static void				endFrameClipping();
	static void				pushAttrib(int);
	static void				popAttrib();
	static void				pushMatrix();
	static void				popMatrix();
	static void				rotate(float, float, float);
	static void				unrotate();
	static void				translate(float, float, float);
	static void				untranslate();
	static void				translateIgnoreScale(float, float, float);
	static void				scale(float, float, float);
	static void				unscale();
	static void				setTextureTolerance(float);
	static void				setVertexTolerance(float);
	static void				getColor(Color*);
	static void				setColor(float, float, float, float);
	static void				setColor(Color*);
	static void				setColor(float*);
	static void				getClearColor(Color*);
	static void				setClearColor(float, float, float, float);
	static void				setClearColor(Color*);
	static void				resetMatrix();
	static void				setFOV(float);
	static void				getCurrentLocation(float*);
	static void				getAmountScaled(float*);
	static void				getAmountTranslated(float*);
	static void				getAmountRotated(float*);
	static void				getColorArray(float*);
	static void				genRectVerts(float*, float, float, float, float);
	static void				genRectVerts(float*, float, float, float, float, float);
	static void				genRectTextures(float*, Texture*);
	static void				genRectTextures(float*, Texture*, int, int);
	static void				genRectTextures(float*, Texture*, bool, bool);
	static void				genRectTextures(float*, float*);
	static void				genRectTextures(float*, float*, int, int);
	static void				genRectTextures(float*, float*, bool, bool);
	static void				genRectTextures(float*, float*, int, int, bool, bool);
	static void				genCubeVerts(float*, float, float, float, float, float, float);
	static void				genRectColors(float*, float, float, float, float);
	static void				quit();

	static bool				is3DEnabled();
	static bool				createContext(SDL_Window*);

	static int				getTextureScaleMinMethod();
	static int				getTextureScaleMagMethod();
	static int				getTextureWrapTMethod();
	static int				getTextureWrapSMethod();

	static float			getTextureTolerance();
	static float			getVertexTolerance();
	static float			getFOV();
	
	static string			getOpenGLVersion();
	static string			getVersion();

	static SDL_GLContext	getContext();

	static float*			getCurrentLocation();
	static float*			getAmountScaled();
	static float*			getAmountTranslated();
	static float*			getAmountRotated();
	static float*			getColorArray();
	static float*			genRectVerts(float, float, float, float);
	static float*			genRectVerts(float, float, float, float, float);
	static float*			genRectTextures(Texture*);
	static float*			genRectTextures(Texture*, int, int);
	static float*			genRectTextures(Texture*, bool, bool);
	static float*			genRectTextures(float*);
	static float*			genRectTextures(float*, int, int);
	static float*			genRectTextures(float*, bool, bool);
	static float*			genRectTextures(float*, int, int, bool, bool);
	static float*			genCubeVerts(float, float, float, float, float, float);
	static float*			genRectColors(float, float, float, float);

	static Color*			getColor();
	static Color*			getClearColor();
};

#endif