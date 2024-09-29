
#pragma once
#include <string>

    enum class input_key {
        unknown,
        key_a,
        key_b,
        key_c,
        key_d,
        key_e,
        key_f,
        key_g,
        key_h,
        key_i,
        key_j,
        key_k,
        key_l,
        key_m,
        key_n,
        key_o,
        key_p,
        key_q,
        key_r,
        key_s,
        key_t,
        key_u,
        key_v,
        key_w,
        key_x,
        key_y,
        key_z,
        SPACE,
        GAMEPAD_L_THUMB_X,
        GAMEPAD_L_THUMB_Y,
        GAMEPAD_R_THUMB_X,
        GAMEPAD_R_THUMB_Y,
        GAMEPAD_R_TRIGGER,
        GAMEPAD_L_TRIGGER,
        GAMEPAD_Y,
        GAMEPAD_X,
        GAMEPAD_B,
        GAMEPAD_A,
        GAMEPAD_START,
        GAMEPAD_SELECT,
        GAMEPAD_BUMPER_R,
        GAMEPAD_BUMPER_L,
        GAMEPAD_L3,
        GAMEPAD_R3,
        GAMEPAD_DPAD_UP,
        GAMEPAD_DPAD_RIGHT,
        GAMEPAD_DPAD_LEFT,
        GAMEPAD_DPAD_DOWN,
        MOUSE_POS_X,
        MOUSE_POS_Y,
        MOUSE_MOVE_X,
        MOUSE_MOVE_Y,
        MOUSE_RIGHT,
        MOUSE_LEFT,
        MOUSE_MIDDLE
    };

    enum class input_source {
        KEYBOARD,
        MOUSE,
        GAMEPAD,
        UNKNOWN
    };

    struct input_action {
        std::string actionName { "" };
        float scale { 1.f };
    };

    input_source get_input_source_from_key(input_key key);