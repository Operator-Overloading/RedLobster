// PLATFORM/include/opengl/OpenGLWindow.hpp

#pragma once
#include "../Window.hpp"

struct GLFWwindow;

namespace Lobster
{
	class LOBSTER_API OpenGLWindow : public Window
	{
		friend class Context;
	public:
		OpenGLWindow(int width,int height,const char* title);
		virtual ~OpenGLWindow() override;
		OpenGLWindow(const OpenGLWindow&) = delete;
		OpenGLWindow& operator=(const OpenGLWindow&) = delete;

		void Update() override;

		int GetWidth() const override;
		int GetHeight() const override;
		std::string GetTitle() const override;
		bool IsMinimized() const override;
		bool IsFocused() const override;
		bool IsCursorEnabled() const override;
		bool WindowShouldClose() const override;

		void* GetHandle() override;

		void SetTitle(const std::string& title) override;
		void SetCursorConfined(bool confined) override;
		void SetCursorVisible(bool visible) override;
		void SetCursorEnabled(bool enabled) override;

		void SetWindowIcon(const char* path);
	private:
		int width, height;
		bool minimized = false, focused = true, cursor_enabled = true, cursor_in_window = false, should_close = false;
		const char* title;
		void* handle;
		GLFWwindow* window;
	};
}