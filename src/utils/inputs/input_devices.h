#pragma once
#include "input_key.h"
#include <functional>
#include <map>
#include <unordered_map>

    enum class intput_device_type
    {
        KEYBOARD,
        MOUSE,
        GAMEPAD
    };

    struct input_device_state
    {
        float value{-99.f};
    };

    using input_device_stateCallbackFunc = std::function<std::unordered_map<input_key, input_device_state>(int)>;

    struct input_device
    {
        intput_device_type Type;
        int Index;
        std::unordered_map<input_key, input_device_state> CurrentState;
        input_device_stateCallbackFunc StateFunc;
    };