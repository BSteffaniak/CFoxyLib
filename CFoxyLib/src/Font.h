#ifndef FONT_H
#define FONT_H

#include "CFL.h"
#include <hash_map>

using std::hash_map;

class Font
{
private:
	int			cols, rows;
	int			width, height;
	int			glyphWidth, glyphHeight;
	int			ids;

	float		letterMargin, lineOffset;

	SpriteSheet	characters;

	hash_map<char, int[]>			charMap;
	hash_map<string, FontText>		history;
	hash_map<char, Bounds>*			charBounds;

	static const Font				DEFAULT_FONT;

	static const ArrayList<Font>	fonts;

	Font();

	void		construct(SpriteSheet, char[], int);
	void		addToHistory(string, int, int, int, int);

	Bounds2f	renderVertexBuffer(string, float, float, float, float, int, int, Panel*, bool);
	Bounds2f	renderVertexBuffer(string, float, float, float, float, int, int, Buffer*, Buffer*, Panel*, bool);

	Bounds2f*	getLineHeights(string);

	static void	init();

public:
	static const int	LEFT, CENTER, RIGHT, BOTTOM, TOP;

	Font(string, int, int, char[]);
	Font(SpriteSheet, char[]);
	~Font();

	void		setTrimBounds(bool);
	void		setLineOffset(float);
	void		setLetterMargin(float);

	bool		doesTrimBounds();
	bool		containsChar(char);

	int			getNumLines(string);
	int			getGlyphWidth();
	int			getGlyphHeight();

	float		getLineOffset();
	float		getWidth(string);
	float		getHeight(string);
	float		getLetterMargin();

	Bounds2f	getRenderBounds(string, float, float, float, int, int, Panel*);
	Bounds2f	render(string, float, float, float, Panel*);
	Bounds2f	render(string, float, float, float, Panel*, bool);
	Bounds2f	render(string, float, float, float, float, Panel*);
	Bounds2f	render(string, float, float, float, float, Panel*, bool);
	Bounds2f	render(string, float, float, float, int, int, Panel*);
	Bounds2f	render(string, float, float, float, int, int, Panel*, bool);
	Bounds2f	render(string, float, float, float, float, int, int, Panel*);
	Bounds2f	render(string, float, float, float, float, int, int, Panel*, bool);

	static void	update();

	static Font	getDefaultFont();
};

#endif