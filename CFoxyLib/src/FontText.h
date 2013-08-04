#ifndef FONTTEXT_H
#define FONTTEXT_H

#include "CFL.h"

class FontText
{
private:
	int		vertexBufferId, texturesBufferId, vertexIndicesBufferId;
	int		size;
	int		id;

	long	lastRendered;

	string	text;

public:
	FontText(string, int, int, int, int, int);

	int	getVertexBufferId();
	int	getTexturesBufferId();
	int	getVertexIndicesBufferId();
	int	getSize();
};

#endif