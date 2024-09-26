#pragma once
#include "singleton.h"
#include "../include/imgui.h"
#include <string>
#include <vector>

struct logger : public singleton<logger>
{
	logger(token){};
	ImGuiTextBuffer m_buffer;
	ImGuiTextFilter m_filter; // Keep scrolling if already at the bottom.
	void clear();
	void add_log(std::string _msg);
	void draw(const char *title, bool *p_open = NULL);

  private:
	bool m_auto_scroll = true;
	std::vector<std::string> text_buffer;
};