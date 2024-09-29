#include <algorithm>
#include "input_manager.h"
#include "../console.h"
#include <iostream>
#include <vector>

    input_source get_input_source_from_key(input_key key)
    {
        switch (key)
        {
        case input_key::key_a:
        case input_key::key_b:
        case input_key::key_c:
        case input_key::key_d:
        case input_key::key_e:
        case input_key::key_f:
        case input_key::key_g:
        case input_key::key_h:
        case input_key::key_i:
        case input_key::key_j:
        case input_key::key_k:
        case input_key::key_l:
        case input_key::key_m:
        case input_key::key_n:
        case input_key::key_o:
        case input_key::key_p:
        case input_key::key_q:
        case input_key::key_r:
        case input_key::key_s:
        case input_key::key_t:
        case input_key::key_u:
        case input_key::key_v:
        case input_key::key_w:
        case input_key::key_x:
        case input_key::key_y:
        case input_key::key_z:
            return input_source::KEYBOARD;
        case input_key::GAMEPAD_L_THUMB_X:
        case input_key::GAMEPAD_L_THUMB_Y:
        case input_key::GAMEPAD_R_THUMB_X:
        case input_key::GAMEPAD_R_THUMB_Y:
        case input_key::GAMEPAD_R_TRIGGER:
        case input_key::GAMEPAD_L_TRIGGER:
        case input_key::GAMEPAD_Y:
        case input_key::GAMEPAD_X:
        case input_key::GAMEPAD_B:
        case input_key::GAMEPAD_A:
        case input_key::GAMEPAD_START:
        case input_key::GAMEPAD_SELECT:
        case input_key::GAMEPAD_BUMPER_R:
        case input_key::GAMEPAD_BUMPER_L:
        case input_key::GAMEPAD_L3:
        case input_key::GAMEPAD_R3:
        case input_key::GAMEPAD_DPAD_UP:
        case input_key::GAMEPAD_DPAD_RIGHT:
        case input_key::GAMEPAD_DPAD_LEFT:
        case input_key::GAMEPAD_DPAD_DOWN:
            return input_source::GAMEPAD;
        case input_key::MOUSE_LEFT:
        case input_key::MOUSE_RIGHT:
        case input_key::MOUSE_MIDDLE:
        case input_key::MOUSE_MOVE_X:
        case input_key::MOUSE_MOVE_Y:
            return input_source::MOUSE;
        default:
            return input_source::UNKNOWN;
        }
    }

    input_manager::input_manager()
    {
        _active = true;
        auto &console = console::get_instance();
        console.add_tagged_line("Input Manager", "Input Manager intialized!");
    }

    input_manager::~input_manager()
    {
        _active = false;
    }

    void input_manager::register_action_callback(const std::string &actionName, const input_manager::action_callback &callback)
    {
        _action_callback[actionName].emplace_back(callback);
    }

    void input_manager::remove_action_callback(const std::string &actionName, const std::string &callbackRef)
    {
        erase_if(_action_callback[actionName], [callbackRef](const action_callback &callback) {
            return callback.Ref == callbackRef;
        });
    }

    void input_manager::map_input_to_action(input_key key, const input_action &action)
    {
        // TODO: Check for duplicates
        _input_actionMapping[key].emplace_back(action);
    }

    void input_manager::unmap_input_from_action(input_key key, const std::string &action)
    {
        std::erase_if(_input_actionMapping[key], [action](const input_action &input_action) {
            return input_action.actionName == action;
        });
    }

    void input_manager::process_input()
    {
        std::vector<action_event> events{};
        for (auto &device : _devices)
        {
            // get new state for device
            auto newState = device.StateFunc(device.Index);

            // compare to old state for device
            for (auto &keyState : newState)
            {
                if (device.CurrentState[keyState.first].value != keyState.second.value)
                {
                    // TODO: Fix cases where conflicting mappings -- additive fashion?
                    auto generatedEvents = generate_action_event(device.Index, keyState.first, keyState.second.value);
                    events.insert(events.end(), generatedEvents.begin(), generatedEvents.end());
                    // save new state value
                    device.CurrentState[keyState.first].value = keyState.second.value;
                }
            }
        }
        // propagate action events
        for (auto &event : events)
        {
            propagate_action_event(event);
        }
    }

    std::vector<input_manager::action_event> input_manager::generate_action_event(int DeviceIndex, input_key key, float newVal)
    {
        auto &actions = _input_actionMapping[key];

        std::vector<action_event> action_events{};

        input_source source = get_input_source_from_key(key);

        for (auto &action : actions)
        {
            action_events.emplace_back(action_event{
                .ActionName = action.actionName,
                .Source = source,
                .SourceIndex = DeviceIndex,
                .Value = newVal * action.scale});
        }

        return action_events;
    }

    void input_manager::propagate_action_event(action_event event)
    {
        for (size_t i = _action_callback[event.ActionName].size() - 1; i >= 0; i--)
        {
            auto &actionCallback = _action_callback[event.ActionName][i];

            if (actionCallback.Func(event.Source, event.SourceIndex, event.Value))
                break;
        }
    }

    void input_manager::register_device(const input_device &device)
    {
        auto &console = console::get_instance();
        console.add_tagged_line("input_manager", "Device registered of type: {}", static_cast<int>(device.Type));
        _devices.emplace_back(device);
        console.add_tagged_line("input_manager", "Device #: {}", _devices.size());
    }

    void input_manager::remove_device(intput_device_type type, int inputIndex)
    {
        auto &console = console::get_instance();
        erase_if(_devices, [type, inputIndex](const input_device &device) {
            return device.Type == type && device.Index == inputIndex;
        });
        console.add_tagged_line("input_manager", "Device unregistered of type: ", static_cast<int>(type));
        console.add_tagged_line("input_manager", "Device #: {}", _devices.size());
    }