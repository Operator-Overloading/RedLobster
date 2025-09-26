// RENDERING/src/opengl/RendererGL.cpp

#include "opengl/RendererGL.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace Lobster
{
	RendererGL::RendererGL()
	{
		settings.drawmode = GL_TRIANGLES;

		glfwSwapInterval(settings.vsync);
	}

	void RendererGL::Shutdown()
	{
	}

	void RendererGL::BeginFrame()
	{
	}

	void RendererGL::EndFrame()
	{
	}

	void RendererGL::Clear(float r,float g,float b,float a)
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glClearColor(r,g,b,a);
	}

	void RendererGL::Resize(int width,int height)
	{
		glViewport(0,0,width,height);
	}
}