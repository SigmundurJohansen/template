#pragma once
#include "../include/imgui.h"

class window
{
  public:
	int init();
	void render();
	void terminate();
	bool should_exit() { return m_should_exit; }

  private:
	GLFWwindow *m_window = 0;
	bool m_should_exit = false;
};