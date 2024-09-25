#define DOCTEST_CONFIG_IMPLEMENT
#include "../test/factorial_test.h"
#include "include/factorial.h"
#include "include/imgui.h"
#include "include/prime_factorial.h"
#include "ui/window.h"
#include <doctest/doctest.h>
#include <iostream>
#include <libintl.h>
#include <stdio.h>
#include <string.h>

const bool testing = false;

int main(int _argc, char **_argv)
{
	if (testing)
	{
		doctest::Context context;
		int res = context.run(); // run tests
	}

	window main_window;
	main_window.init();
	std::cout << gettext("Main window init..") << std::endl;

	// Main application loop
	while (!main_window.should_exit())
	{
		main_window.render();
	}
	std::cout << gettext("Terminating..") << std::endl;

	main_window.terminate();
	return 0;
}
