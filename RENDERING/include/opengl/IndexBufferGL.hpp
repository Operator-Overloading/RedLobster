// RENDERING/include/opengl/IndexBufferGL.hpp

#pragma once
#include "BufferGL.hpp"

namespace Lobster
{
	template<size_t N>
	class IndexBufferGL : BufferGL<unsigned int,N>
	{
	public:
		IndexBufferGL(unsigned int* data);
		~IndexBufferGL();

		void Data(unsigned int* data,unsigned int MODE = 0x88E4);

		void Bind();
		void Unbind();
	};
}