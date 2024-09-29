#pragma once
#include "input_devices.h"
#include "input_key.h"
#include <functional>
#include <unordered_map>
#include <vector>

    class input_manager
    {
      public:
        using action_callback_func = std::function<bool(input_source, int, float)>;

        struct action_callback
        {
            std::string Ref;
            action_callback_func Func;
        };

      private:
        struct action_event
        {
            std::string ActionName;
            input_source Source;
            int SourceIndex;
            float Value;
        };

      public:
        input_manager();
        ~input_manager();

        void register_device(const input_device &device);
        void remove_device(intput_device_type source, int inputIndex);

        void register_action_callback(const std::string &actionName, const action_callback &callback);
        void remove_action_callback(const std::string &actionName, const std::string &callbackRef);

        void map_input_to_action(input_key key, const input_action &action);
        void unmap_input_from_action(input_key key, const std::string &action);

      private:
        friend class Game;

        // process_input will get new device state and compare with old state; then generate action events
        void process_input();

        std::vector<action_event> generate_action_event(int deviceIndex, input_key key, float newVal);
        void propagate_action_event(action_event event);

      private:
        bool _active{false};

        std::unordered_map<input_key, std::vector<input_action>> _input_actionMapping{};
        std::unordered_map<std::string, std::vector<action_callback>> _action_callback{};

        std::vector<input_device> _devices;
    };