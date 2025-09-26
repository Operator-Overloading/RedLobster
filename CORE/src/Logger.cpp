// CORE/src/Logger.cpp

#include "Logger.hpp"

#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>

#ifdef ENGINE_PLATFORM_WINDOWS
#include <windows.h>
#endif

namespace Lobster
{
	std::vector<Logger::LogEntry> Logger::logs;
	bool Logger::autoscroll = true;

	void Logger::Log(LogLevel lvl,const std::string& message)
	{
#ifdef ENGINE_PLATFORM_WINDOWS
		int color_code = 7;

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		switch(lvl)
		{
		case LOG_LEVEL_DEBUG:
			color_code = 15;
			break;
		case LOG_LEVEL_INFO:
			color_code = 7;
			break;
		case LOG_LEVEL_WARNING:
			color_code = 14;
			break;
		case LOG_LEVEL_ERROR:
			color_code = 12;
			break;
		default:
			break;
		}

		SetConsoleTextAttribute(hConsole,color_code);
#endif

		auto now = std::chrono::system_clock::now();
		auto now_time = std::chrono::system_clock::to_time_t(now);

		tm current_time;
		_localtime64_s(&current_time,&now_time);

		std::stringstream ss_log;
		ss_log << std::put_time(&current_time,"%Y-%m-%d %X");
		ss_log << LevelToString(lvl);
		ss_log << message.c_str();
		ss_log << '\n';

		logs.push_back({lvl,ss_log.str()});

		if(logs.size() > max_logs)
		{
			logs.erase(logs.begin());
		}

		std::cout << ss_log.str();

#ifdef ENGINE_PLATFORM_WINDOWS
		SetConsoleTextAttribute(hConsole,7);
#endif
	}

	void Logger::Log(LogLevel lvl,std::vector<std::string> messages)
	{
		std::string log;

		for(std::string msg : messages)
			log += msg;

		Log(lvl,log);
	}

	void Logger::Log(LogLevel lvl,std::vector<const char*> messages)
	{
		std::string log;

		for(const char* msg : messages)
			log += msg;

		Log(lvl,log);
	}

	void Logger::DrawImguiConsole()
	{
#ifdef _IMGUI
		ImGui::Begin("Console");

		if(ImGui::Button("Clear"))
			logs.clear();

		ImGui::SameLine();
		bool copy = ImGui::Button("Copy");

		ImGui::SameLine();
		if(ImGui::Button("Options"))
			ImGui::OpenPopup("Options");

		if(ImGui::BeginPopup("Options"))
		{
			ImGui::Checkbox("Auto-scroll",&autoscroll);
			ImGui::EndPopup();
		}

		ImGui::Separator();

		ImGui::BeginChild("Scrolling",ImVec2(0,0),false,ImGuiWindowFlags_HorizontalScrollbar);

		if(copy)
			ImGui::LogToClipboard();

		for(const auto& log : logs)
		{
			ImVec4 color = ImVec4(1.0f,1.0f,1.0f,1.0f);

			switch(log.level)
			{
			case LOG_LEVEL_DEBUG:
				color = ImVec4(1.0f,1.0f,1.0f,1.0f);
			case LOG_LEVEL_INFO:
				color = ImVec4(0.8f,0.8f,0.8f,1.0f);
			case LOG_LEVEL_WARNING:
				color = ImVec4(1.0f,1.0f,0.0f,1.0f);
			case LOG_LEVEL_ERROR:
				color = ImVec4(1.0f,0.3f,0.3f,1.0f);
			}

			ImGui::PushStyleColor(ImGuiCol_Text,color);
			ImGui::TextUnformatted(log.message.c_str());
			ImGui::PopStyleColor();
		}

		if(autoscroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);

		ImGui::EndChild();
		ImGui::End();
#endif
	}
}