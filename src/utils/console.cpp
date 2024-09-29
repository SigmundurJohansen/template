#include "console.h"
#include "spdlog/cfg/env.h"  // support for loading levels from the environment variable
#include "spdlog/fmt/ostr.h" // support for user defined types
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <algorithm>
#include <iterator>
#include <vector>
#include <chrono>

void console::clear()
{
	text_buffer.clear();
	m_filter.Clear();
}

void console::add_line(std::string _msg) // IM_FMTARGS(2)
{
	text_buffer.emplace_back(_msg);
}

void console::add_tagged_line(const char *_tag,std::string _msg, ...)
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	text_buffer.emplace_back(std::string{_tag + _msg.insert(0, " : ") + "\n"}.c_str());
}

void show_history()
{
}

void console::render(const char *title, bool *p_open)
{
	
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar;
	if (!ImGui::Begin(title, p_open, window_flags))
	{
		ImGui::End();
		return;
	}
	ImGui::SameLine();
	m_filter.Draw("Filter", 200.0f);
	ImGui::SameLine();
	if (ImGui::Button("Clear"))
		clear();
	ImGui::SameLine();
	if (ImGui::Button("History"))
		show_history();
	ImGui::SetItemTooltip("Clear the scrolling text box");	
	ImGui::Separator();

	static int max_height_in_lines = 8;
	// ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
	// ImGui::DragInt("Max Height (in Lines)", &max_height_in_lines, 0.2f);
	static ImGuiChildFlags child_flags = ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY;

	if (ImGui::BeginChild("scrolling", ImVec2(0, 0), child_flags, ImGuiWindowFlags_HorizontalScrollbar))
	{
		std::string my_filter = m_filter.InputBuf;
		std::vector<std::string> filtered;
		std::copy_if(text_buffer.begin(), text_buffer.end(), std::back_inserter(filtered),
					 [my_filter](std::string i) {
						 return i.find(my_filter) != std::string::npos;
					 });

		for (int i = 0; i < filtered.size(); i++)
		{
			ImGui::Text(filtered[i].c_str());
		}
	}

	if (m_auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		ImGui::SetScrollHereY(1.0f);

	ImGui::EndChild();
	static char buf1[32] = "";
	ImGui::InputText("##", buf1, 32);
	ImGui::SameLine();
	if (ImGui::Button("Button"))
	{
		add_line(buf1);
		buf1[0] = 0;
	}
	ImGui::End();
}