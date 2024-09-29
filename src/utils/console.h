#pragma once
#include "../include/imgui.h"
#include "singleton.h"
#include <string>
#include <vector>

struct console : public singleton<console>
{
	console(token){};
	ImGuiTextBuffer m_buffer;
	ImGuiTextFilter m_filter; // Keep scrolling if already at the bottom.
	void clear();
	void add_tagged_line(const char *_tag, std::string _msg, ...);
	void add_line(std::string _msg);
	void render(const char *title, bool *p_open = NULL);

  private:
	bool m_auto_scroll = true;
	std::vector<std::string> text_buffer;
};