#include "utils/inputs/input_key.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "../test/factorial_test.h"
#include "ui/window.h"
#include "utils/console.h"
#include "utils/inputs/input_manager.h"
#include <doctest/doctest.h>
#include <iostream>
#include <libintl.h>

const bool testing = true;
doctest::Context context;

int main(int _argc, char **_argv)
{
	if (testing)
		int res = context.run(); // run tests

	auto &input = input_manager::get_instance();
	input.set_key_mapping();
	window main_window;
	main_window.init();

	std::cout << gettext("Main window init..") << std::endl;
	while (!main_window.should_exit())
	{
		main_window.render();
		input.process_input();
	}
	std::cout << gettext("Terminating..") << std::endl;

	main_window.terminate();
	return 0;
}
