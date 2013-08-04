#include "CFL.h"

/**
 * Create an instance of FontText to keep track of a String of
 * text that was recently added to the history.
 * 
 * @param text The String of text to add to the history.
 * @param vId The vertex buffer's id.
 * @param tId The texture buffer's id.
 * @param viId The vertex indices buffer's id.
 * @param size the size of the buffer that is being added to the
 * 		history.
 */
FontText::FontText(string text, int vId, int tId, int viId, int size, int id)
{
	this->id                    = id;
	
	this->text                  = text;
	
	this->vertexBufferId        = vId;
	this->texturesBufferId      = tId;
	this->vertexIndicesBufferId = viId;
	
	this->size                  = size;
}

/**
 * Get the vertex Buffer id.
 * 
 * @return The vertex Buffer id.
 */
int FontText::getVertexBufferId()
{
	return vertexBufferId;
}

/**
 * Get the vertex  Buffer id.
 * 
 * @return The vertex Buffer id.
 */
int FontText::getVertexIndicesBufferId()
{
	return vertexIndicesBufferId;
}

/**
 * Get the textures Buffer id.
 * 
 * @return The textures Buffer id.
 */
int FontText::getTexturesBufferId()
{
	return texturesBufferId;
}

/**
 * Get the size of the buffers.
 * 
 * @return The size of the buffers.
 */
int FontText::getSize()
{
	return size;
}