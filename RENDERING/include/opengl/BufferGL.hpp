// RENDERING/include/opengl/BufferGL.hpp

#pragma once

namespace Lobster
{
	template<class B,size_t N>
	class BufferGL
	{
	public:
		virtual ~Buffer() = default;

		virtual void Data(B* data) = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	protected:
		unsigned int id = 0;

		B* data;
		size_t size = N;
	};
}