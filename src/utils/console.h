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
	void add_line();
	void render(const char *title, bool *p_open = NULL);
	bool is_empty()
	{
		is_should_refocus = true;
		return m_is_empty;
	}
	void set_docking_id(ImGuiID id) { m_dockspace_id = id; }

  private:
	bool m_is_empty = true;
	bool m_auto_scroll = true;
	bool is_should_refocus = true;
	ImGuiID m_dockspace_id = 0;
	std::vector<std::string> text_buffer;
};