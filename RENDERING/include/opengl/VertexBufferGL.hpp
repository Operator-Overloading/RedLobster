// RENDERING/include/opengl/VertexBufferGL.hpp

#pragma once
#include "BufferGL.hpp"

namespace Lobster
{
	template<size_t N>
	class VertexBufferGL : BufferGL<const float,N>
	{
	public:
		VertexBufferGL(const float* data);
		~VertexBufferGL();

		void Data(const float* data,unsigned int MODE = 0x88E4);

		void Bind();
		void Unbind();
	};
}