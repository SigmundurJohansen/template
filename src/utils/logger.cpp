#include "logger.h"
#include <algorithm>
#include <iterator>
#include <vector>

void logger::clear()
{
	text_buffer.clear();
}

void logger::add_log(std::string _msg) // IM_FMTARGS(2)
{
	text_buffer.emplace_back(_msg);
}

void logger::draw(const char *title, bool *p_open)
{
	if (!ImGui::Begin(title, p_open))
	{
		ImGui::End();
		return;
	}

	// Main window
	ImGui::SameLine();
	if (ImGui::Button("Clear"))
	{
		clear();
	}
	ImGui::SameLine();
	m_filter.Draw("Filter", -100.0f);

	ImGui::Separator();
	if (ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar))
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
	ImGui::End();
}