#include "CFL.h"

int	Bundle::id;

/**
 * The default blank constructor for the Bundle class.
 */
Bundle::Bundle()
{

}

/**
 * Create a Bundle with the specified amount of needed
 * vertices. Also specify the amount of dimensions the
 * vertex will be in, as well as whether to enable textures
 * and color Buffers with the Buffer.
 * 
 * @param vertexAmount The amount of needed vertices.
 * @param vertexSize The amount of dimensions the vertex
 *		will be in.
 * @param textures Whether to enable texture Buffers for this Bundle.
 * @param colors Whether to enable color Buffers for this Bundle.
 */
Bundle::Bundle(int vertexAmount, int vertexSize, bool textures, bool colors)
{
	vertsPosition    = 0;
	texturesPosition = 0;
	colorsPosition   = 0;

	this->vertexAmount = vertexAmount;
	this->vertexSize   = vertexSize;
	
	verticesBuffer    = new Buffer(vertexAmount * vertexSize);
	verticesId        = verticesBuffer->getId();
	
	if (textures)
	{
		texturesBuffer = new Buffer(vertexAmount * 2);
		texturesId     = texturesBuffer->getId();
	}
	
	if (colors)
	{
		colorsBuffer = new Buffer(vertexAmount * 4);
		colorsId     = colorsBuffer->getId();
	
		if (vertexAmount > 0)
		{
			colorsBuffer->beginEditing();
			{
				vector<float> cols(vertexAmount * 4);
				
				for (unsigned int i = 0; i < cols.size(); i++)
				{
					cols[i] = 1;
				}
				
				colorsBuffer->setData(0, &cols[0], (int)cols.size());
			}
			colorsBuffer->endEditing();
		}
	}
}

/**
 * Create a Bundle from the specified Vertices Buffer with the
 * specified vertex size, Textures Buffer, and Colors Buffer.
 * 
 * @param verticesBuffer The Vertices Buffer to create the Bundle
 * 		with.
 * @param texturesBuffer The Textures Buffer to create the Bundle
 * 		with.
 * @param colorsBuffer The Colors Buffer to create the Bundle with.
 * @param vertexSize The size of the vertices in the Vertex Buffer.
 */
Bundle::Bundle(Buffer* verticesBuffer, Buffer* texturesBuffer, Buffer* colorsBuffer, int vertexSize)
{
	vertsPosition    = 0;
	texturesPosition = 0;
	colorsPosition   = 0;

	this->verticesBuffer = verticesBuffer;
	this->verticesId     = verticesBuffer->getId();
	
	if (texturesBuffer != NULL)
	{
		this->texturesBuffer = texturesBuffer;
		this->texturesId     = texturesBuffer->getId();
	}
	
	if (colorsBuffer != NULL)
	{
		this->colorsBuffer = colorsBuffer;
		this->colorsId     = colorsBuffer->getId();
	}
	
	this->vertexSize   = vertexSize;
	this->vertexAmount = verticesBuffer->getSize() / vertexSize;
}

/**
 * Create a Bundle from the specified vertices buffer id, textures
 * buffer id, and colors buffer id. You also need to specify the
 * amount of vertices are in the vertices buffer as well as the size
 * of the vertices in the vertices buffer.
 * 
 * @param verticesId The OpenGL Buffer id for the vertices buffer.
 * @param texturesId The OpenGL Buffer id for the textures buffer.
 * @param colorsId The OpenGL Buffer id for the colors buffer.
 * @param vertexAmount The amount of vertices that are in the
 * 		vertices buffer.
 * @param vertexSize The size of the vertices in the vertices
 * 		buffer.
 */
Bundle::Bundle(int verticesId, int texturesId, int colorsId, int vertexAmount, int vertexSize)
{
	vertsPosition    = 0;
	texturesPosition = 0;
	colorsPosition   = 0;

	this->verticesId   = verticesId;
	this->texturesId   = texturesId;
	this->colorsId     = colorsId;
	
	this->vertexSize   = vertexSize;
	this->vertexAmount = vertexAmount;
}

/**
 * Destruct the Bundle by deleting the containing Buffer instances.
 */
Bundle::~Bundle()
{
	delete verticesBuffer;
	delete texturesBuffer;
	delete colorsBuffer;

	verticesBuffer = NULL;
	texturesBuffer = NULL;
	colorsBuffer   = NULL;
}

//	/**
//	 * 
//	 * 
//	 * @param amount
//	 */
//	void Bundle::createColorShader(int amount)
//	{
////		String vertexShader =
////				"\nvoid Bundle::main()" +
////				"\n{" +
////				"\n	gl_TexCoord[0] = gl_MultiTexCoord0;" +
////				"\n	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;" +
////				"\n}";
////		
////		String fragmentShader =
////				"\nuniform sampler2D	texture;" +
////				"\nuniform vec4			colors[" + amount / 10 + "];" +
////				"\n" +
////				"\nvoid Bundle::main()" +
////				"\n{" +
////				"\n	gl_FragColor = texture2D(texture, gl_TexCoord[0].st);" +
////				"\n	gl_FragColor = gl_FragColor * colors[0];" +
////				"\n}";
////		
////		colorShader = new Shader();
////		colorShader.loadString(new String[] { vertexShader }, new String[] { fragmentShader });
//	}

/**
 * Get the position that the Vertices Buffer is set at currently.
 * 
 * @return The position that the Vertices Buffer is set at currently.
 */
int Bundle::getVerticesPosition()
{
	return vertsPosition;
}

/**
 * Get the position that the Textures Buffer is set at currently.
 * 
 * @return The position that the Textures Buffer is set at currently.
 */
int Bundle::getTexturesPosition()
{
	return texturesPosition;
}

/**
 * Get the Vertices Buffer instance that this Bundle is using.
 * 
 * @return The Vertices Buffer instance that this Bundle is using.
 */
Buffer* Bundle::getVerticesBuffer()
{
	return verticesBuffer;
}

/**
 * Set the Vertices Buffer instance that this Bundle will use.
 * 
 * @param buffer The Vertices Buffer instance that this Bundle will
 * 		use.
 */
void Bundle::setVerticesBuffer(Buffer* buffer)
{
	this->verticesBuffer = buffer;
}

/**
 * Set the vertices at the specified offset in the Vertices Buffer.
 * 
 * @param offset The offset in the Vertices Buffer.
 * @param verts The new float array to set the data at the offset to.
 */
void Bundle::setVertices(int offset, float* verts, int length)
{
	verticesBuffer->setData(offset, verts, length);
	
//		int id = ++this->id;
	
//		vertexOffsets.put(id, new VertexOffset(shape, offset, vertexSize, verts.length));
	
//		return id;
}

/**
 * Add the specified float array to the end of the Vertices Buffer's
 * current position.
 * 
 * @param verts The float array to append.
 */
void Bundle::addVertices(float* verts, int length)
{
	setVertices(vertsPosition, verts, length);
	
	vertsPosition += length;
	
//		return id;
}

//	void Bundle::translate(int offset, int numVertices, float dx, float dy, float dz)
//	{
//		verticesBuffer.translate(offset * vertexSize, numVertices * vertexSize, dx, dy, dz);
//	}

/**
 * Get the Textures Buffer instance that this Bundle is using.
 * 
 * @return The Textures Buffer instance that this Bundle is using.
 */
Buffer* Bundle::getTexturesBuffer()
{
	return texturesBuffer;
}

/**
 * Set the Textures Buffer instance that this Bundle will use.
 * 
 * @param buffer The Textures Buffer instance that this Bundle will
 * 		use.
 */
void Bundle::setTexturesBuffer(Buffer* buffer)
{
	this->texturesBuffer = buffer;
}

/**
 * Set the textures at the specified offset in the Textures Buffer.
 * 
 * @param offset The offset in the Textures Buffer.
 * @param textures The new float array to set the data at the offset
 * 		to.
 */
void Bundle::setTextures(int offset, float* textures, int length)
{
	texturesBuffer->setData(offset, textures, length);
	
//		int id = ++this->id;

//		textureOffsets.put(id, new TextureOffset(offset, textures.length));
	
//		return id;
}

/**
 * Add the specified float array to the end of the Textures Buffer's
 * current position.
 * 
 * @param verts The float array to append.
 */
void Bundle::addTextures(float* textures, int length)
{
	setTextures(texturesPosition, textures, length);
	
	texturesPosition += length;
	
//		return id;
}

/**
 * Get the Colors Buffer instance that this Bundle is using.
 * 
 * @return The Colors Buffer instance that this Bundle is using.
 */
Buffer* Bundle::getColorsBuffer()
{
	return colorsBuffer;
}

/**
 * Set the Colors Buffer instance that this Bundle will use.
 * 
 * @param buffer The Colors Buffer instance that this Bundle will
 * 		use.
 */
void Bundle::setColorsBuffer(Buffer* buffer)
{
	this->colorsBuffer = buffer;
}

/**
 * Set the colors at the specified offset in the Colors Buffer.
 * 
 * @param offset The offset in the Colors Buffer.
 * @param colors The new float array to set the data at the offset
 * 		to.
 */
void Bundle::setColors(int offset, float* colors, int length)
{
	colorsBuffer->setData(offset, colors, length);
	
//		int id = ++this->id;

//		textureOffsets.put(id, new TextureOffset(offset, textures.length));
	
//		return id;
}

/**
 * Add the specified float array to the end of the Colors Buffer's
 * current position.
 * 
 * @param verts The float array to append.
 */
void Bundle::addColors(float* colors, int length)
{
	setColors(colorsPosition, colors, length);
	
	colorsPosition += length;
	
//		return id;
}

/**
 * Bind the VerticesBuffer and allow it to be modified.
 */
void Bundle::beginEditingVertices()
{
	verticesBuffer->beginEditing();
}

/**
 * Unbind the VerticesBuffer and restrict it from being modified.
 */
void Bundle::endEditingVertices()
{
	verticesBuffer->endEditing();
}

/**
 * Bind the TexturesBuffer and allow it to be modified.
 */
void Bundle::beginEditingTextures()
{
	texturesBuffer->beginEditing();
}

/**
 * Unbind the TexturesBuffer and restrict it from being modified.
 */
void Bundle::endEditingTextures()
{
	texturesBuffer->endEditing();
}

/**
 * Bind the ColorsBuffer and allow it to be modified.
 */
void Bundle::beginEditingColors()
{
	colorsBuffer->beginEditing();
}

/**
 * Unbind the ColorsBuffer and restrict it from being modified.
 */
void Bundle::endEditingColors()
{
	colorsBuffer->endEditing();
}

/**
 * Render all of the contents in the Bundle to the specified shape
 * and Texture.
 * 
 * @param shape The shape of the polygons that the Bundle contains.
 * @param texture The Texture instance that is wrapped on the
 * 		polygons.
 */
void Bundle::render(int shape, Texture* texture)
{
	render(shape, 0, vertexAmount, texture);
}

/**
 * Render a portion of the contents from the Bundle to the specified
 * shape and Texture.
 * 
 * @param shape The shape of the polygons that the portion of the
 * 		Bundle contains.
 * @param start The start index of the first vertex of the polygons
 * 		to render.
 * @param amount The amount of vertices to render starting at the
 * 		start index.
 * @param texture The Texture to wrap all of the polygons within
 * 		the portion of the Bundle with.
 */
void Bundle::render(int shape, int start, int amount, Texture* texture)
{
	if (texture != NULL)
	{
		texture->bind();
	}
	
	beginVerticesDraw();//start * vertexSize);
	beginTexturesDraw();//start * 2);
	beginColorsDraw();

	glDrawArrays(shape, start, amount);
	
	endColorsDraw();
	endTexturesDraw();
	endVerticesDraw();
	
//		Texture.unbind();
}

/**
 * Bind the VertexBuffer and set it up for drawing.
 */
void Bundle::beginVerticesDraw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER, verticesId);

	glVertexPointer(vertexSize, GL_FLOAT, 0, 0);
	
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndicesId);
}

/**
 * Unbind the VertexBuffer and restrict the drawing with it.
 */
void Bundle::endVerticesDraw()
{
	glDisableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glDisableClientState(GL_VERTEX_ARRAY);
}

/**
 * Bind the TexturesBuffer and set it up for drawing.
 */
void Bundle::beginTexturesDraw()
{
	GL::setTextureWrapSMethod(GL::getTextureWrapSMethod());
	GL::setTextureWrapTMethod(GL::getTextureWrapTMethod());
	
	GL::setTextureScaleMinMethod(GL::getTextureScaleMinMethod());
	GL::setTextureScaleMagMethod(GL::getTextureScaleMagMethod());
	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER, texturesId);

	glTexCoordPointer(2, GL_FLOAT, 0, 0);
}

/**
 * Unbind the TexturesBuffer and restrict the drawing with it.
 */
void Bundle::endTexturesDraw()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	GL::setTextureScaleMinMethod(GL::getTextureScaleMinMethod());
	GL::setTextureScaleMagMethod(GL::getTextureScaleMagMethod());
	
	GL::setTextureWrapSMethod(GL::getTextureWrapSMethod());
	GL::setTextureWrapTMethod(GL::getTextureWrapTMethod());
}

/**
 * Bind the ColorsBuffer and set it up for drawing.
 */
void Bundle::beginColorsDraw()
{
	if (colorsId == 0)
	{
		return;
	}
	
	glEnableClientState(GL_COLOR_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER, colorsId);
	
	glColorPointer(4, GL_FLOAT, 0, 0);
}

/**
 * Unbind the ColorsBuffer and restrict the drawing with it.
 */
void Bundle::endColorsDraw()
{
	if (colorsId == 0)
	{
		return;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glDisableClientState(GL_COLOR_ARRAY);
}