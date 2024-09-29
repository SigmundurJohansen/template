#pragma once
#include "../singleton.h"
#include "input_key.h"
#include <functional>
#include <map>
#include <unordered_map>

enum class intput_device_type
{
	keyboard,
	mouse,
	gamepad
};

struct input_device_state
{
	float value{-99.f};
};

using input_device_state_callback_func = std::function<std::unordered_map<input_key, input_device_state>(int)>;

struct input_device
{
	intput_device_type m_type;
	int m_index;
	std::unordered_map<input_key, input_device_state> m_current_state;
	input_device_state_callback_func m_state_func;
};