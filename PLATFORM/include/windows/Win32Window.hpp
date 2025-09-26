// PLATFORM/include/windows/Win32Window.hpp

#pragma once
#include "Win32.hpp"
#include "../Window.hpp"

#include <optional>

namespace Lobster
{
	class LOBSTER_API Win32Window : public Window
	{
		friend class Context;
	private:
		class WindowClass
		{
		public:
			static const char* GetName();
			static HINSTANCE GetInstance();
		private:
			WindowClass();
			~WindowClass();
			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;
			static constexpr const char* wnd_class_name = "REDLOBSTERWINDOW";
			static WindowClass wnd_class;
			HINSTANCE instance;
		};
	public:
		Win32Window(int width,int height,const char* title);
		virtual ~Win32Window() override;
		Win32Window(const Win32Window&) = delete;
		Win32Window&operator=(const Win32Window&) = delete;

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

		static std::optional<int> ProcessMessages();
	private:
		static LRESULT __stdcall HandleMsgSetup(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam);
		static LRESULT __stdcall HandleMsgThunk(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam);
		LRESULT HandleMsg(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam);
	private:
		int width, height;
		bool minimized = false, focused = true, cursor_enabled = true, cursor_in_window = false, should_close = false;
		const char* title;
		HWND handle;
		std::vector<BYTE> raw_buffer;
	};
}