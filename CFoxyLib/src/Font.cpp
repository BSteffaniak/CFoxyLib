#define COMPILE_FONT
#if !defined(COMPILE_FONT)

#include "CFL.h"

#include <hash_map>

using std::hash_map;
using std::_Hash;

const Font				Font::DEFAULT_FONT;

const ArrayList<Font>	Font::fonts;

const int				LEFT = 0, CENTER = 1, RIGHT = 2, BOTTOM = 0, TOP = 2;

void Font::init()
{
	SpriteSheet sprites(ResourceLocator::getProjectDirectory() + "res/images/fonts/font.png", 26, 4);

	char chars[] =
	{
		'A', 'B', 'C', 'D', 'E', 'F',  'G', 'H', 'I', 'J', 'K', 'L',  'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f',  'g', 'h', 'i', 'j', 'k', 'l',  'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'0', '1', '2', '3', '4', '5',  '6', '7', '8', '9', '_', '-',  '+', '=', '~', '`', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
		'?', '>', '<', ';', ':', '\'', '"', '{', '}', '[', ']', '\\', '|', ',', '.', '/', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
	};
	
	Font DEFAULT_FONT(sprites, chars);
		
	DEFAULT_FONT.setLetterMargin(1);
	DEFAULT_FONT.setTrimBounds(true);
}

/**
 * Private default constructor for class Font. Do nothing.
 */
Font::Font()
{

}

/**
 * Create a Font from the image at the specified location. The Font
 * image will be split up into the specified amount of columns and
 * rows. Each of the characters will correspond with the given
 * charSequence char array.
 * 
 * @param location The location of the Font image.
 * @param cols The number of columns in the Font image.
 * @param rows The number of rows in the Font image.
 * @param charSequence The character array that corresponds with each
 * 		Character in the Font image.
 * @throws IOException Thrown if the Font image file was not found.
 */
Font::Font(string location, int cols, int rows, char charSequence[])
{
	construct(SpriteSheet(location, cols, rows), charSequence);
}

/**
 * Create a Font from the specified SpriteSheet. Each of the
 * characters will correspond with the given charSequence char
 * array.
 * 
 * @param sprites The SpriteSheet that holds all of the characters.
 * 		It must be split into the correct divisions for each letter
 * 		to work properly.
 * @param charSequence The character array that corresponds with each
 * 		Character in the Font image.
 * @throws IOException Thrown if the Font image file was not found.
 */
Font::Font(SpriteSheet sprites, char charSequence[])
{
	construct(sprites, charSequence);
}

/**
 * Free any of the dangling memory created by the Font class
 * instance.
 */
Font::~Font()
{
	delete charBounds;

	charBounds = NULL;
}

void Font::construct(SpriteSheet sprites, char charSequence[], int length)
{
	characters        = sprites;
	
	this->cols         = characters.getNumCols();
	this->rows         = characters.getNumRows();
	
	this->width        = characters.getWidth();
	this->height       = characters.getHeight();
	
	this->glyphWidth   = width / cols;
	this->glyphHeight  = height / rows;
	
	hash_map<char, int[]> charMap();
	hash_map<string, FontText> history();
	
	for (int y = 0; y < rows; y ++)
	{
		for (int x = 0; x < cols; x ++)
		{
			if (x + y * cols >= length)
			{
				break;
			}
			
			char c = charSequence[x + y * cols];
			
			if (charMap[c] == NULL)
			{
				int ar[] = { x, y };

				charMap[c] = ar;
			}
		}
	}
	
	lineOffset = 1;
	
	fonts.add(this);
}

/**
 * Get whether or not the Bounds for the Font's Glyphs have been
 * trimmed and prepared to fit together like a PBJ sandwich baby.
 * 
 * @return Whether or not the Bounds have been trimmed neatly.
 */
bool Font::doesTrimBounds()
{
	return charBounds != NULL;
}

/**
 * Whether or not to trim the Glyphs Bounds so that they fit perfectly
 * together in beautiful harmony. Yes, do it.
 * 
 * @param trim Whether or not to trim the Bounds.
 */
void Font::setTrimBounds(bool trim)
{
	if (trim)
	{
		charBounds = new hash_map<char, Bounds>();
		_Hash<char> chars = charMap.key_comp;
		
		Set<Character> chars = charSequence.keySet();
		
		Iterator<Character> i = chars.iterator();
		
		while (i.hasNext())
		{
			Character c      = i.next();
			
			Bounds  bounds   = new Bounds();
			
			if (c == ' ')
			{
				bounds.setWidth(glyphWidth);
//					bounds.setHeight(glyphHeight);
				bounds.setY(glyphHeight);
				
				charBounds.put(c, bounds);
				
				continue;
			}
			
			int     x        = charSequence.get(c)[0];
			int     y        = characters.getNumRows() - charSequence.get(c)[1] - 1;
			
			x               *= glyphWidth;
			y               *= glyphHeight;
			
			byte    pixels[] = characters.getPixelsBytes(x, y, glyphWidth, glyphHeight);
			
			bool begin    = true;
			
			int     left     = 0;
			int     right    = 0;
			int     top      = 0;
			int     bottom   = 0;
			
			for (int x2 = 0; x2 < glyphWidth; x2++)
			{
				int num = 0;
				
				for (int y2 = 0; y2 < glyphHeight; y2++)
				{
					if (pixels[(x2 + y2 * glyphWidth) * 4 + 3] != 0)
					{
						begin = false;
						
						break;
					}
					
					num++;
				}
				
				if (num >= glyphHeight)
				{
					if (begin)
					{
						left++;
					}
					else
					{
						break;
					}
				}
			}
			
			begin = true;
			
			for (int x2 = glyphWidth - 1; x2 > left; x2--)
			{
				int num = 0;
				
				for (int y2 = 0; y2 < glyphHeight; y2++)
				{
					if (pixels[(x2 + y2 * glyphWidth) * 4 + 3] != 0)
					{
						begin = false;
						
						break;
					}
					
					num++;
				}
				
				if (num >= glyphHeight)
				{
					if (begin)
					{
						right++;
					}
					else
					{
						break;
					}
				}
			}
			
			begin = true;
			
			for (int y2 = 0; y2 < glyphHeight; y2++)
			{
				int num = 0;

				for (int x2 = 0; x2 < glyphWidth; x2++)
				{
					if (pixels[(x2 + y2 * glyphWidth) * 4 + 3] != 0)
					{
						begin = false;
						
						break;
					}
					
					num++;
				}
				
				if (num >= glyphWidth)
				{
					if (begin)
					{
						bottom++;
					}
					else
					{
						break;
					}
				}
			}
			
			begin = true;
			
			for (int y2 = glyphHeight - 1; y2 > bottom; y2--)
			{
				int num = 0;
				
				for (int x2 = 0; x2 < glyphWidth; x2++)
				{
					if (pixels[(x2 + y2 * glyphWidth) * 4 + 3] != 0)
					{
						begin = false;
						
						break;
					}
					
					num++;
				}
				
				if (num >= glyphWidth)
				{
					if (begin)
					{
						top++;
					}
					else
					{
						break;
					}
				}
			}
			
			bounds.setX(left);
			bounds.setY(bottom);
			bounds.setWidth(glyphWidth - left - right);
			bounds.setHeight(glyphHeight - bottom - top);
			
			charBounds[c] = bounds;
		}
	}
	else
	{
		delete charBounds;

		charBounds = NULL;
	}
}

/**
 * Get the Bounds that the Font render will take up with the specified
 * text, location, scale, alignment, and panel given to it.
 * 
 * @param text The text to get the Bounds with.
 * @param x The horizontal location that the text would be rendered
 * 		to.
 * @param y The vertical location that the text would be rendered
 * 		to.
 * @param scale The scale that the Font would be rendered by.
 * @param horizontalAlignment The horizontal alignment that the text
 * 		will be aligned by.
 * @param verticalAlignment The vertical alignment that the text will
 * 		be aligned by.
 * @param panel The Panel that the Font will be rendered inside of.
 * 		Passing a NULL value here will result in the Panel being
 * 		treated of as the Frame.
 * @return The Bounds that the text will take up after rendered.
 */
Bounds2f Font::getRenderBounds(string text, float x, float y, float scale, int horizontalAlignment, int verticalAlignment, Panel *panel)
{
	Bounds2f bounds;
	
	float glScale[3];
	GL::getAmountScaled(glScale);
	
	float scaleX    = glScale[0];
	float scaleY    = glScale[1];
	
	float width     = getWidth(text);
	float height    = getHeight(text);
	
	int   numLines  = getNumLines(text);
	
	if (horizontalAlignment == CENTER)
	{
		if (panel != NULL)
		{
			x += (Frame::getWidth() / scaleX) / 2;
		}
		else
		{
			x += (Frame::getWidth() / scaleX) / 2;
		}
		
		x -= (width * (scale / 2));
	}
	else if (horizontalAlignment == RIGHT)
	{
		if (panel != NULL)
		{
			x += panel->getScaledWidth() / scaleX;
		}
		else
		{
			x += Frame::getWidth() / scaleX;
		}
		
		x -= width * scale;
	}
	if (verticalAlignment == CENTER)
	{
		if (panel != NULL)
		{
			y += (panel->getScaledHeight() / scaleY) / 2;
		}
		else
		{
			y += (Frame::getHeight() / scaleY) / 2;
		}
		
		y -= (glyphHeight * numLines) * (scale / 2);
	}
	else if (verticalAlignment == TOP)
	{
		if (panel != NULL)
		{
			y += panel->getScaledHeight() / scaleY;
		}
		else
		{
			y += Frame::getHeight() / scaleY;
		}
		
		y -= glyphHeight * scale;
	}
	
	bounds.setX(x * scaleX);
	bounds.setY(y * scaleY);
	bounds.setWidth(width * scaleX);
	bounds.setHeight(height * scaleY);
	
	return bounds;
}

/**
 * Render the text at the specified location to the specified Panel.
 * 
 * @param text The text to render to the Panel.
 * @param x The horizontal location to render the text.
 * @param y The vertical location to render the text.
 * @param z The oblique location to render the text.
 * @param panel The Panel to render the text inside of. Passing a
 * 		NULL value here will result in the Panel being
 * 		treated of as the Frame.
 * @return The Bounds that the text was rendered inside of.
 */
Bounds2f Font::render(string text, float x, float y, float z, Panel *panel)
{
	return render(text, x, y, z, panel, true);
}

/**
 * Render the text at the specified location to the specified Panel.
 * 
 * @param text The text to render to the Panel.
 * @param x The horizontal location to render the text.
 * @param y The vertical location to render the text.
 * @param z The oblique location to render the text.
 * @param panel The Panel to render the text inside of. Passing a
 * 		NULL value here will result in the Panel being
 * 		treated of as the Frame.
 * @param saveHistory Whether or not to save the specified text to the
 * 		history buffer.
 * @return The Bounds that the text was rendered inside of.
 */
Bounds2f Font::render(string text, float x, float y, float z, Panel *panel, bool saveHistory)
{
	return render(text, x, y, z, 1, panel, saveHistory);
}

/**
 * Render the text at the specified location to the specified Panel.
 * 
 * @param text The text to render to the Panel.
 * @param x The horizontal location to render the text.
 * @param y The vertical location to render the text.
 * @param z The oblique location to render the text.
 * @param scale The scale to render the text by.
 * @param panel The Panel to render the text inside of. Passing a
 * 		NULL value here will result in the Panel being
 * 		treated of as the Frame.
 * @return The Bounds that the text was rendered inside of.
 */
Bounds2f Font::render(string text, float x, float y, float z, float scale, Panel *panel)
{
	return render(text, x, y, z, scale, panel, true);
}

/**
 * Render the text at the specified location to the specified Panel.
 * 
 * @param text The text to render to the Panel.
 * @param x The horizontal location to render the text.
 * @param y The vertical location to render the text.
 * @param z The oblique location to render the text.
 * @param scale The scale to render the text by.
 * @param panel The Panel to render the text inside of. Passing a
 * 		NULL value here will result in the Panel being
 * 		treated of as the Frame.
 * @param saveHistory Whether or not to save the specified text to the
 * 		history buffer.
 * @return The Bounds that the text was rendered inside of.
 */
Bounds2f Font::render(string text, float x, float y, float z, float scale, Panel *panel, bool saveHistory)
{
	return render(text, x, y, z, scale, LEFT, BOTTOM, panel, saveHistory);
}

/**
 * Render the text at the specified location to the specified Panel.
 * 
 * @param text The text to render to the Panel.
 * @param x The horizontal location to render the text.
 * @param y The vertical location to render the text.
 * @param z The oblique location to render the text.
 * @param horizontalAlignment The horizontal alignment that the text
 * 		will be aligned by.
 * @param verticalAlignment The vertical alignment that the text will
 * 		be aligned by.
 * @param panel The Panel to render the text inside of. Passing a
 * 		NULL value here will result in the Panel being
 * 		treated of as the Frame.
 * @return The Bounds that the text was rendered inside of.
 */
Bounds2f Font::render(string text, float x, float y, float z, int horizontalAlignment, int verticalAlignment, Panel *panel)
{
	return render(text, x, y, z, horizontalAlignment, verticalAlignment, panel, true);
}

/**
 * Render the text at the specified location to the specified Panel.
 * 
 * @param text The text to render to the Panel.
 * @param x The horizontal location to render the text.
 * @param y The vertical location to render the text.
 * @param z The oblique location to render the text.
 * @param horizontalAlignment The horizontal alignment that the text
 * 		will be aligned by.
 * @param verticalAlignment The vertical alignment that the text will
 * 		be aligned by.
 * @param panel The Panel to render the text inside of. Passing a
 * 		NULL value here will result in the Panel being
 * 		treated of as the Frame.
 * @param saveHistory Whether or not to save the specified text to the
 * 		history buffer.
 * @return The Bounds that the text was rendered inside of.
 */
Bounds2f Font::render(string text, float x, float y, float z, int horizontalAlignment, int verticalAlignment, Panel *panel, bool saveHistory)
{
	return render(text, x, y, z, 1, horizontalAlignment, verticalAlignment, panel, saveHistory);
}

/**
 * Render the text at the specified location to the specified Panel.
 * 
 * @param text The text to render to the Panel.
 * @param x The horizontal location to render the text.
 * @param y The vertical location to render the text.
 * @param z The oblique location to render the text.
 * @param scale The scale to render the text by.
 * @param horizontalAlignment The horizontal alignment that the text
 * 		will be aligned by.
 * @param verticalAlignment The vertical alignment that the text will
 * 		be aligned by.
 * @param panel The Panel to render the text inside of. Passing a
 * 		NULL value here will result in the Panel being
 * 		treated of as the Frame.
 * @return The Bounds that the text was rendered inside of.
 */
Bounds2f Font::render(string text, float x, float y, float z, float scale, int horizontalAlignment, int verticalAlignment, Panel *panel)
{
	return render(text, x, y, z, scale, horizontalAlignment, verticalAlignment, panel, true);
}

/**
 * Render the text at the specified location to the specified Panel.
 * 
 * @param text The text to render to the Panel.
 * @param x The horizontal location to render the text.
 * @param y The vertical location to render the text.
 * @param z The oblique location to render the text.
 * @param scale The scale to render the text by.
 * @param horizontalAlignment The horizontal alignment that the text
 * 		will be aligned by.
 * @param verticalAlignment The vertical alignment that the text will
 * 		be aligned by.
 * @param panel The Panel to render the text inside of. Passing a
 * 		NULL value here will result in the Panel being
 * 		treated of as the Frame.
 * @param saveHistory Whether or not to save the specified text to the
 * 		history buffer.
 * @return The Bounds that the text was rendered inside of.
 */
Bounds2f Font::render(string text, float x, float y, float z, float scale, int horizontalAlignment, int verticalAlignment, Panel *panel, bool saveHistory)
{
	return renderVertexBuffer(text, x, y, z, scale, horizontalAlignment, verticalAlignment, panel, saveHistory);
}

///**
// * Render the text at the specified location to the specified Panel.
// * 
// * @param text The text to render to the Panel.
// * @param x The horizontal location to render the text.
// * @param y The vertical location to render the text.
// * @param z The oblique location to render the text.
// * @param scale The scale to render the text by.
// * @param horizontalAlignment The horizontal alignment that the text
// * 		will be aligned by.
// * @param verticalAlignment The vertical alignment that the text will
// * 		be aligned by.
// * @param panel The Panel to render the text inside of. Passing a
// * 		NULL value here will result in the Panel being
// * 		treated of as the Frame.
// * @return The Bounds that the text was rendered inside of.
// */
//Bounds2f Font::renderVertexBuffer(string text, float x, float y, float z, float scale, int horizontalAlignment, int verticalAlignment, Panel *panel)
//{
//	return renderVertexBuffer(text, x, y, z, scale, horizontalAlignment, verticalAlignment, panel, true);
//}

/**
 * Render the text at the specified location to the specified Panel.
 * 
 * @param text The text to render to the Panel.
 * @param x The horizontal location to render the text.
 * @param y The vertical location to render the text.
 * @param z The oblique location to render the text.
 * @param scale The scale to render the text by.
 * @param horizontalAlignment The horizontal alignment that the text
 * 		will be aligned by.
 * @param verticalAlignment The vertical alignment that the text will
 * 		be aligned by.
 * @param panel The Panel to render the text inside of. Passing a
 * 		NULL value here will result in the Panel being
 * 		treated of as the Frame.
 * @param saveHistory Whether or not to save the specified text to the
 * 		history buffer.
 * @return The Bounds that the text was rendered inside of.
 */
Bounds2f Font::renderVertexBuffer(string text, float x, float y, float z, float scale, int horizontalAlignment, int verticalAlignment, Panel *panel, bool saveHistory)
{
	return renderVertexBuffer(text, x, y, z, scale, horizontalAlignment, verticalAlignment, NULL, NULL, panel, saveHistory);
}

///**
// * Render the text at the specified location to the specified Panel
// * using vertex buffers.
// * 
// * @param text The text to render to the Panel.
// * @param x The horizontal location to render the text.
// * @param y The vertical location to render the text.
// * @param z The oblique location to render the text.
// * @param scale The scale to render the text by.
// * @param horizontalAlignment The horizontal alignment that the text
// * 		will be aligned by.
// * @param verticalAlignment The vertical alignment that the text will
// * 		be aligned by.
// * @param vertices The Buffer that holds the vertices used for
// * 		rendering the Font.
// * @param textures The Buffer that holds the Textures used for
// * 		each of the letters in the text.
// * @param panel The Panel to render the text inside of. Passing a
// * 		NULL value here will result in the Panel being
// * 		treated of as the Frame.
// * @return The Bounds that the text was rendered inside of.
// */
//Bounds2f Font::renderVertexBuffer(string text, float x, float y, float z, float scale, int horizontalAlignment, int verticalAlignment, Buffer vertices, Buffer textures, Panel panel)
//{
//	return renderVertexBuffer(text, x, y, z, scale, horizontalAlignment, verticalAlignment, vertices, textures, panel, true);
//}

/**
 * Render the text at the specified location to the specified Panel
 * using vertex buffers.
 * 
 * @param text The text to render to the Panel.
 * @param x The horizontal location to render the text.
 * @param y The vertical location to render the text.
 * @param z The oblique location to render the text.
 * @param scale The scale to render the text by.
 * @param horizontalAlignment The horizontal alignment that the text
 * 		will be aligned by.
 * @param verticalAlignment The vertical alignment that the text will
 * 		be aligned by.
 * @param vertices The Buffer that holds the vertices used for
 * 		rendering the Font.
 * @param textures The Buffer that holds the Textures used for
 * 		each of the letters in the text.
 * @param panel The Panel to render the text inside of. Passing a
 * 		NULL value here will result in the Panel being
 * 		treated of as the Frame.
 * @param saveHistory Whether or not to save the specified text to the
 * 		history buffer.
 * @return The Bounds that the text was rendered inside of.
 */
Bounds2f Font::renderVertexBuffer(string text, float x, float y, float z, float scale, int horizontalAlignment, int verticalAlignment, Buffer *vertices, Buffer *textures, Panel *panel, bool saveHistory)
{
	if (text.length() <= 0)
	{
		return Bounds2f(0, 0, 0, 0);
	}
	
	int      vId       = 0;
	int      tId       = 0;
	int      viId      = 0;
	int      size      = 0;
	
	float    glScale[3];
	GL::getAmountScaled(glScale);
	
	float    scaleX   = glScale[0];
	float    scaleY   = glScale[1];
	
	const char *chars = text.c_str();
	
	Bounds2f bounds   = getRenderBounds(text, x, y, scale, horizontalAlignment, verticalAlignment, panel);
	
//		x = Math.round(bounds.getX() / scaleX);
//		y = Math.round(bounds.getY() / scaleY);
	
	x = bounds.getX() / scaleX;
	y = bounds.getY() / scaleY;
	
//		x /= scaleX;
//		y /= scaleY;
	
	if (history.find(text) != history.end())
	{
		vId  = history[text].getVertexBufferId();
		tId  = history[text].getTexturesBufferId();
		viId = history[text].getVertexIndicesBufferId();
		size = history[text].getSize();
	}
	else
	{
		if (vertices == NULL && textures == NULL)
		{
			vertices = new Buffer(text.length() * 3 * 2 * 2);
			textures = new Buffer(text.length() * 3 * 2 * 2);
		}
		else if (vertices != NULL || textures != NULL)
		{
			//throw new IllegalArgumentException("Vertices and textures must either both be NULL or both have a value.");
		}
		
		size = vertices->getSize();
		
//			for (int i = 0; i < chars.length; i ++)
//			{
//				if (chars[i] == '\n')
//				{
//					renderVertexBuffer(text.substring(0, i), x, y /*+ ((glyphHeight + 1) / 2) * scale*/ , z, scale, horizontalAlignment, verticalAlignment, vertices, textures, panel);
//					renderVertexBuffer(text.substring(i + 1), x, y - (glyphHeight + 1)/*((glyphHeight + 1) / 2) * scale*/, z, scale, horizontalAlignment, verticalAlignment, vertices, textures, panel);
//					
//					addToHistory(text, vId, tId, viId, size, vertices, textures, NULL);
//					
//					return;
//				}
//			}
		
		int      line      = 0;
		int      lines     = getNumLines(text);
		
		vector<Bounds2f> heights(lines);
		
		float    yOffset   = 0;
		float    xOffset   = 0;
		
		if (lines > 1)
		{
			if (verticalAlignment == BOTTOM)
			{
				string lastLines = text.substr(text.find_first_of('\n') + 1);
				
				yOffset = getHeight(lastLines);
			}
			else if (verticalAlignment == TOP)
			{
				yOffset -= lineOffset;
			}
		}
		
		if (charBounds != NULL)
		{
			heights = getLineHeights(text);
			
			if (verticalAlignment == BOTTOM)
			{
				yOffset -= glyphHeight - heights[line].getHeight();
			}
			
			if (lines > 1)
			{
				yOffset += lineOffset;
			}
		}
		
		for (int i = 0; i < text.length(); i ++)
		{
			if (chars[i] == '\n')
			{
				line++;
				
				yOffset -= glyphHeight + lineOffset;
				xOffset  = 0;

				if (charBounds != NULL)
				{
					yOffset += glyphHeight - (heights[line].getHeight() + heights[line].getY());
					yOffset += heights[line - 1].getY();
				}
			}
			else
			{
				int   charX     = 0;
				int   charY     = 0;
				
				float offsets[] = NULL;
				
				try
				{
					if (!charSequence.containsKey(chars[i]))	
					{
						continue;
					}
					
					charX   = charSequence.get(chars[i])[0];
					charY   = charSequence.get(chars[i])[1];
					
					offsets = characters.getImageOffsets(charX, charY, 1, 1);
				}
				catch (NullPointerException e)
				{
//						if (chars[i] == ' ')
//						{
//							
//						}
//						else
//						{
//							addToHistory(text, vId, tId, viId, size);
//							
//							return NULL;
//						}
					
					chars[i] = ' ';
					
					charX    = charSequence.get(chars[i])[0];
					charY    = charSequence.get(chars[i])[1];
					
					offsets  = characters.getImageOffsets(charX, charY, 1, 1);
				}
				
				int cleft  = 0;
				int cwidth = 0;
				
				if (charBounds != NULL)
				{
					cleft    = charBounds.get(chars[i]).getX();
					cwidth   = charBounds.get(chars[i]).getWidth();
					
					xOffset -= charBounds.get(chars[i]).getX();
				}
				
				vertices.beginEditing();
				{
					vertices.setData(i * 3 * 2 * 2, GL.genRectVerts(xOffset, yOffset, glyphWidth, glyphHeight));
				}
				vertices.endEditing();
				
				textures.beginEditing();
				{
					textures.setData(i * 3 * 2 * 2, GL.genRectTextures(offsets));
				}
				textures.endEditing();
				
				if (charBounds != NULL)
				{
					xOffset += cwidth + cleft;
				}
				else
				{
					xOffset += glyphWidth;
				}
				
				xOffset += letterMargin;
			}
		}
		
//			vertices.genIndices(GL.QUADS, NULL);
		
		vId  = vertices.getId();
		tId  = textures.getId();
//			viId = vertices.getIndicesId(0);
		
		if (saveHistory)
		{
			addToHistory(text, vId, tId, viId, size);
		}
	}
	
	bundle = new Bundle(vId, tId, 0, size / 2, 2);
	
	GL.pushMatrix();
	{
		GL.translate(x, y, z);
		GL.scale(scale, scale, 1);
		
		bundle.render(GL.TRIANGLES, characters);
	}
	GL.popMatrix();
	
	if (history.containsKey(text))
	{
		history.get(text).lastRendered = System.currentTimeMillis();
	}
	
	return bounds;
}

/**
 * Get whether the specified char is a valid character contained in
 * the character set given to the Font during construction.
 * 
 * @param c The character to check if it is a valid character or not.
 * @return Whether the character is valid or not.
 */
bool Font::containsChar(char c)
{
	return charSequence.containsKey(c);
}

/**
 * Get the amount of pixels that there will be between a new-line in
 * a string of text rendered.
 * 
 * @return The amount of pixels that there will be between a new-line
 * 		in a string of text rendered.
 */
float Font::getLineOffset()
{
	return lineOffset;
}

/**
 * Set the amount of pixels that there will be between a new-line in
 * a string of text rendered.
 * 
 * @param lineOffset The amount of pixels that there will be between
 * 		a new-line in a string of text rendered.
 */
void Font::setLineOffset(float lineOffset)
{
	this->lineOffset = lineOffset;
}

/**
 * Get the number of lines that the specified string of text takes
 * up on the Display.
 * 
 * @param text The string of text to get the number of lines from.
 * @return The number of lines in the string of text.
 */
int Font::getNumLines(string text)
{
	if (text.length() <= 0)
	{
		return 0;
	}
	
	int   numLines  = 1;
	
	for (int i = 0; i < text.length(); i++)
	{
		if (text.charAt(i) == '\n')
		{
			numLines++;
		}
	}
	
	return numLines;
}

/**
 * Add the string of text that was previously rendered to the history
 * of rendered strings. This is used in order to save time if a string
 * has already been previously rendered. Instead of creating the
 * vertex buffer all over again, just reuse the old one.
 * 
 * @param text The string of text to add to the history.
 * @param vId The vertex buffer's id.
 * @param tId The texture buffer's id.
 * @param viId The vertex indices buffer's id.
 * @param size the size of the buffer that is being added to the
 * 		history.
 */
void Font::addToHistory(string text, int vId, int tId, int viId, int size)
{
	ids = ids + 1;// < 100 ? ids + 1 : 0;
	
	history.put(text, new FontText(text, vId, tId, viId, size));
}

/**
 * Get the amount of pixels that the specified string would take up
 * horizontally.
 * 
 * @param text The string of text to get the width of.
 * @return The amount of pixels that the specified string would take
 * 		up horizontally.
 */
float Font::getWidth(string text)
{
	float width  = 0;
	
	float max    = 0;
	
	int   cwidth = 0;
	
	for (int i = 0; i < text.length(); i ++)
	{
		char c = text.charAt(i);
		
		if (c == '\n')
		{
			if (i > 0 && max == width)
			{
				max -= letterMargin;
			}
			
			width = 0;
		}
		else
		{
			if (charBounds != NULL)
			{
				cwidth = charBounds.get(c).getWidth();
				
				width += cwidth;
			}
			else
			{
				width += glyphWidth;
			}
			
			width += letterMargin;
		
			if (width > max)
			{
				max = width;
			}
		}
	}
	
	if (max > 0 && max == width)
	{
		max -= letterMargin;
	}
	
	return max;
}

/**
 * Get the amount of pixels that the specified string would take up
 * vertically.
 * 
 * @param text The string of text to get the height of.
 * @return The amount of pixels that the specified string would take
 * 		up vertically.
 */
float Font::getHeight(string text)
{
	float height = 0;
	
	if (charBounds == NULL)
	{
		int numLines = getNumLines(text);
		
		if (numLines > 0)
		{
			height = (glyphHeight + lineOffset) * numLines - lineOffset;
		}
	}
	else
	{
		Bounds2f Font::heights[] = getLineHeights(text);
		
		for (int i = 0; i < heights.length; i++)
		{
			height += heights[i].getHeight() + lineOffset;
		}
		
		if (heights.length > 0)
		{
			height -= lineOffset;
		}
	}
	
	return height;
}

/**
 * Get the height of each line in order of an array.
 * 
 * @param text The text to get the height of each line from.
 * @return An array containing float values that represent the
 * 		height of each line of the text.
 */
Bounds2f* Font::getLineHeights(string text)
{
	Bounds2f Font::heights[] = new Bounds2f[getNumLines(text)];
	
	int line = 0;
	int min  = glyphHeight;
	int max  = 0;
	
	for (int i = 0; i < text.length(); i++)
	{
		char c = text.charAt(i);
		
		if (c == '\n')
		{
			heights[line] = new Bounds2f();
			
			heights[line].setY(min);
			heights[line].setHeight(max - min);
			
			max = 0;
			min = glyphHeight;
			
			line++;
		}
		else
		{
			int y = charBounds.get(c).getY();
			int h = charBounds.get(c).getHeight();
			
			if (y < min)
			{
				min = y;
			}
			if (y + h > max)
			{
				max = y + h;
			}
		}
	}
	
	if (min < glyphHeight || max > 0)
	{
		heights[line] = new Bounds2f();
		
		heights[line].setY(min);
		heights[line].setHeight(max - min);
	}
	
	return heights;
}

/**
 * Get the width that each of the Font's Glyphs take up.
 * 
 * @return The width that each of the Font's Glyphs take up.
 */
int Font::getGlyphWidth()
{
	return glyphWidth;
}

/**
 * Get the height that each of the Font's Glyphs take up.
 * 
 * @return The height that each of the Font's Glyphs take up.
 */
int Font::getGlyphHeight()
{
	return glyphHeight;
}

/**
 * Get the amount of pixels that the letters will be spaced by when
 * rendered.
 * 
 * @return The amount of pixels that the letters will be spaced by when
 * 		rendered.
 */
float Font::getLetterMargin()
{
	return letterMargin;
}

/**
 * Set the amount of pixels that the letters will be spaced by when
 * rendered.
 * 
 * @param letterMargin The amount of pixels that the letters will be
 * 		spaced by when rendered.
 */
void Font::setLetterMargin(float letterMargin)
{
	this->letterMargin = letterMargin;
}

/**
 * Get the default Font that is used in this library.
 * 
 * @return The default Font that is used in this library.
 */
Font Font::getDefaultFont()
{
	return DEFAULT_FONT;
}

/**
 * Updates the Font class. Removes any old strings in the history
 * that need to be removed.
 */
void Font::update()
{
	long current = Time::currentTimeMillis();
	
	for (unsigned int i = 0; i < fonts.size(); i++)
	{
		Font font = fonts.get(i);
		
		Collection<FontText> values = font.history.values();
		
		Queue<string>	remove = new Queue<string>();
		
		Iterator<FontText> it = values.iterator();
		
		while (it.hasNext())
		{
			FontText ft = it.next();
			
			if (current - ft.lastRendered >= 10000)
			{
				remove.enqueue(ft.text);
			}
		}
		
		while (!remove.isEmpty())
		{
			string text = remove.dequeue();
			
			font.history.remove(text);
		}
	}
}

#endif