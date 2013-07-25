#include "CFL.h"

GLuint	Buffer::currentId;

/**
 * The default blank constructor for the Bundle class.
 */
Buffer::Buffer()
{

}

/**
 * Create a Buffer suitable for storing a specific amount
 * of floats.
 * 
 * @param size The specific amount of floats to use.
 */
Buffer::Buffer(int size)
{
	this->size = size;
	
	buffer = new float[size];

	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size * 4, buffer, GL_DYNAMIC_DRAW);
}

/**
 * Destruct the Buffer by deleting the arrays that hold the data.
 */
Buffer::~Buffer()
{
	delete[] buffer;
	delete[] mapBuffer;

	buffer    = NULL;
	mapBuffer = NULL;
}

/**
 * @return The OpenGL GL_ARRAY_BUFFER id.
 */
int Buffer::getId()
{
	return id;
}

/**
 * Get the capacity of the Buffer. The max amount of
 * data that can be stored in this Buffer.
 * 
 * @return The capacity of the Buffer. The max amount of
 *		data that can be stored in this Buffer.
 */
int Buffer::getSize()
{
	return size;
}

/**
 * Get the current position of the Buffer. This is the
 * index that you will next insert values into.
 * 
 * @return The current position of the Buffer. This is the
 *		index that you will next insert values into.
 */
int Buffer::getPosition()
{
	return position;
}

/**
 * Set the place in which the Buffer will next insert data
 * into.
 * 
 * @param position The position to set for the Buffer.
 */
void Buffer::setPosition(int position)
{
	this->position = position;
}

/**
 * Get the float data at the specified index.
 * 
 * @param index The index in which to get the data from.
 * @return The data at the specified index.
 */
float Buffer::getData(int index)
{
	return buffer[index];
}

/**
 * Method used for setting the value at the specified
 * index to the specified value of the float.
 * 
 * @param index The index of the float data.
 * @param data The data to set it to.
 */
void Buffer::setData(int index, float data)
{
	buffer[index] = data;
}

/**
 * Method used for setting the values at the specified
 * index to the specified values of the floats in the
 * data array.
 * 
 * @param index The index of the float data.
 * @param data The data to set it to.
 */
void Buffer::setData(int index, float* data, int length)
{
	for (int i = 0; i < length; i++)
	{
		buffer[index + i] = data[i];
	}
}

//	/**
//	 * 
//	 * 
//	 * @param offset
//	 * @param size
//	 * @param dx
//	 * @param dy
//	 * @param dz
//	 */
//	void Buffer::translate(int offset, int size, float dx, float dy, float dz)
//	{
//		buffer.position(offset);
//		
//		for (int i = 0; i < size; i += 3)
//		{
//			buffer.put(buffer.get(offset + i + 0) + dx);
//			buffer.put(buffer.get(offset + i + 1) + dy);
//			buffer.put(buffer.get(offset + i + 2) + dz);
//		}
//		
//		buffer.rewind();
//	}

/**
 * Bind the Buffer and mapBuffer in order to edit the data within the
 * Buffer.
 */
void Buffer::beginEditing()
{
//		int currentlyBound = GL11.glGetInteger(GL_ARRAY_BUFFER_BINDING);
//		
//		if (currentlyBound == id)
//		{
//			return;
//		}
	
//		if (!isBound())
//		{
		bind();
//		}
	
//		System.out.println(currentlyBound + ", " + id);
	
	//mapBuffer = (byte*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	
	buffer = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);//mapBuffer.order(ByteOrder.nativeOrder()).asFloatBuffer();
}

/**
 * Unbind the Buffer. No longer able to edit after this call.
 */
void Buffer::endEditing()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/**
 * Get whether or not the Bound is currently bound and ready to
 * be used.
 * 
 * @return Whether the Texture is bound or not.
 */
bool Buffer::isBound()
{
	return currentId == id;
}

/**
 * Bind the Buffer as the current Buffer to be used.
 */
void Buffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	
	bind(id);
}

/**
 * Method to keep track of which Buffer is currently bound.
 * 
 * @param id The id of the Buffer that is being bound.
 */
void Buffer::bind(int id)
{
	Buffer::currentId = id;
}