// RENDERING/src/opengl/IndexBufferGL.cpp

#include "opengl/IndexBufferGL.hpp"

#include <glfw/glfw3.h>
#include <glad/glad.h>

namespace Lobster
{
	template<size_t N>
	IndexBufferGL<N>::IndexBufferGL(unsigned int* data)
	{
		glGenBuffers(1,&id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id);
		Data(data);
	}

	template<size_t N>
	IndexBufferGL<N>::~IndexBufferGL()
	{
		Unbind();
		glDeleteBuffers(1,&id);
	}

	template<size_t N>
	void IndexBufferGL<N>::Data(unsigned int* data,unsigned int MODE)
	{
		glBufferData(GL_ARRAGL_ELEMENT_ARRAY_BUFFERY_BUFFER,size,data,MODE);
	}

	template<size_t N>
	void IndexBufferGL<N>::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id);
	}

	template<size_t N>
	void IndexBufferGL<N>::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	}
}