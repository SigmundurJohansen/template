#include "multiplatform_input.h"


    void multiplatform_input::update_keyboard_state(int key, float value) {
        input_key iKey = multiplatform_key_to_input_key(key);

        _keyboardState[iKey].value = value;
    }

    void multiplatform_input::update_mouse_state(int button, float value) {
        input_key iKey = multiplatform_mouse_button_to_input_key(button);

        _mouseState[iKey].value = value;
    }
  
    input_key multiplatform_input::multiplatform_key_to_input_key(int key) {
        switch (key) {
            case GLFW_KEY_A:
                return input_key::key_a;
            case GLFW_KEY_B:
                return input_key::key_b;
            case GLFW_KEY_C:
                return input_key::key_c;
            case GLFW_KEY_D:
                return input_key::key_d;
            case GLFW_KEY_E:
                return input_key::key_e;
            case GLFW_KEY_S:
                return input_key::key_s;
            case GLFW_KEY_W:
                return input_key::key_w;
            case GLFW_KEY_SPACE:
                return input_key::SPACE;
            default:
                return input_key::unknown;
        }
    }

    input_key multiplatform_input::multiplatform_mouse_button_to_input_key(int button) {
        switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT:
                return input_key::MOUSE_LEFT;
            case GLFW_MOUSE_BUTTON_RIGHT:
                return input_key::MOUSE_RIGHT;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                return input_key::MOUSE_MIDDLE;
            default:
                return input_key::unknown;
        }
    }

    std::unordered_map<input_key, input_device_state> multiplatform_input::get_gamepad_state(const GLFWgamepadstate &state) {
        std::unordered_map<input_key, input_device_state> gamepadState {};

        // Get the buttons
        for (int i = 0; i <= GLFW_GAMEPAD_BUTTON_LAST; i++) {
            int buttonState = state.buttons[i];
            float value = buttonState == GLFW_PRESS ? 1.f : 0.f;

            switch (i) {
                case GLFW_GAMEPAD_BUTTON_B:
                    gamepadState[input_key::GAMEPAD_B].value = value;
                    break;
                case GLFW_GAMEPAD_BUTTON_A:
                    gamepadState[input_key::GAMEPAD_A].value = value;
                    break;
                case GLFW_GAMEPAD_BUTTON_X:
                    gamepadState[input_key::GAMEPAD_X].value = value;
                    break;
                case GLFW_GAMEPAD_BUTTON_Y:
                    gamepadState[input_key::GAMEPAD_Y].value = value;
                    break;
                case GLFW_GAMEPAD_BUTTON_LEFT_BUMPER:
                    gamepadState[input_key::GAMEPAD_BUMPER_L].value = value;
                    break;
                case GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER:
                    gamepadState[input_key::GAMEPAD_BUMPER_R].value = value;
                    break;
                case GLFW_GAMEPAD_BUTTON_BACK:
                    gamepadState[input_key::GAMEPAD_SELECT].value = value;
                    break;
                case GLFW_GAMEPAD_BUTTON_START:
                    gamepadState[input_key::GAMEPAD_START].value = value;
                    break;
                case GLFW_GAMEPAD_BUTTON_LEFT_THUMB:
                    gamepadState[input_key::GAMEPAD_L3].value = value;
                    break;
                case GLFW_GAMEPAD_BUTTON_RIGHT_THUMB:
                    gamepadState[input_key::GAMEPAD_R3].value = value;
                    break;
                case GLFW_GAMEPAD_BUTTON_DPAD_UP:
                    gamepadState[input_key::GAMEPAD_DPAD_UP].value = value;
                    break;
                case GLFW_GAMEPAD_BUTTON_DPAD_RIGHT:
                    gamepadState[input_key::GAMEPAD_DPAD_RIGHT].value = value;
                    break;
                case GLFW_GAMEPAD_BUTTON_DPAD_DOWN:
                    gamepadState[input_key::GAMEPAD_DPAD_DOWN].value = value;
                    break;
                case GLFW_GAMEPAD_BUTTON_DPAD_LEFT:
                    gamepadState[input_key::GAMEPAD_DPAD_LEFT].value = value;
                    break;
                case GLFW_GAMEPAD_BUTTON_GUIDE:
                default:
                    break;
            }
        }

        // get the axes
        for (int i = 0; i <= GLFW_GAMEPAD_AXIS_LAST; i++) {
            float value = state.axes[i];

            switch (i) {
                case GLFW_GAMEPAD_AXIS_LEFT_X:
                    gamepadState[input_key::GAMEPAD_L_THUMB_X].value = value;
                    break;
                case GLFW_GAMEPAD_AXIS_LEFT_Y:
                    gamepadState[input_key::GAMEPAD_L_THUMB_Y].value = -value;
                    break;
                case GLFW_GAMEPAD_AXIS_RIGHT_X:
                    gamepadState[input_key::GAMEPAD_R_THUMB_X].value = value;
                    break;
                case GLFW_GAMEPAD_AXIS_RIGHT_Y:
                    gamepadState[input_key::GAMEPAD_R_THUMB_Y].value = -value;
                    break;
                case GLFW_GAMEPAD_AXIS_LEFT_TRIGGER:
                    gamepadState[input_key::GAMEPAD_L_TRIGGER].value = value;
                    break;
                case GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER:
                    gamepadState[input_key::GAMEPAD_R_TRIGGER].value = value;
                    break;
                default:
                    break;
            }
        }

        return gamepadState;
    }
