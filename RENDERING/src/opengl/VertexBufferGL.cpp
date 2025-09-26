// RENDERING/src/opengl/VertexBufferGL.cpp

#include "opengl/VertexBufferGL.hpp"

#include <glfw/glfw3.h>
#include <glad/glad.h>

namespace Lobster
{
	template<size_t N>
	VertexBufferGL<N>::VertexBufferGL(const float* data)
	{
		glGenBuffers(1,&id);
		glBindBuffer(GL_ARRAY_BUFFER,id);
		Data(data);
	}

	template<size_t N>
	VertexBufferGL<N>::~VertexBufferGL()
	{
		Unbind();
		glDeleteBuffers(1,&id);
	}

	template<size_t N>
	void VertexBufferGL<N>::Data(const float* data,unsigned int MODE)
	{
		glBufferData(GL_ARRAY_BUFFER,size,data,MODE);
	}

	template<size_t N>
	void VertexBufferGL<N>::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER,id);
	}

	template<size_t N>
	void VertexBufferGL<N>::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER,0);
	}
}