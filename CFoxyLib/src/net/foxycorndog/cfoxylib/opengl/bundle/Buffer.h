#ifndef BUFFER_H
#define BUFFER_H

#include "CFL.h"

class Buffer
{
private:
	int				size;
	int				position;

	GLuint			id;

	float*			buffer;
	//fbyte*			mapBuffer;

	Buffer();

	static void		bind(int);

	static GLuint	currentId;

public:
	Buffer(int);
	~Buffer();

	void	setPosition(int);
	void	setData(int, float);
	void	setData(int, float*, int length);
	void	beginEditing();
	void	endEditing();
	void	bind();

	bool	isBound();

	int		getId();
	int		getSize();
	int		getPosition();

	float	getData(int index);
};

#endif