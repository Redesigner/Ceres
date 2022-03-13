#pragma once

#include "Axis.h"
#include "Axis2D.h"
#include "Buttons.h"
#include "Joystick.h"
#include "../Common/Vector2.h"

#include <functional>
#include <string>
#include <map>
#include <unordered_map>
#include <forward_list>

extern "C"
{
    #include <SDL2/SDL.h>
}

using voidFunctionType = std::function<void(void)>;
using cursorFunctionType = std::function<void(int, int)>;

namespace Ceres
{
    /**
     * @brief Object for handling our various button inputs
     * 
     */
    class InputHandler
    {
        public:
            InputHandler();
            ~InputHandler();

            void RegisterController(int deviceIndex);

            /**
             * @brief Callback for when a button is pressed
             * 
             * @param input button that was pressed
             */
            void HandleInput(Button input);
            /**
             * @brief Callback for when a mouse cursor is moved
             * 
             * @param x movement of the mouse cursor along the X-axis, in pixels
             * @param y movement of the mouse cursor along the Y-axis, in pixels
             */
            void HandleCursorInput(int x, int y);

            /**
             * @brief Associate a Button with an action
             * 
             * @param input button to be associated
             * @param actionName name of the action
             */
            void BindInput(Button input, std::string actionName);
            /**
             * @brief Associate an action with a function. Calls the function when the action is called
             * 
             * @param actionName name of the action
             * @param function function to be called
             */
            void BindAction(std::string actionName, voidFunctionType function);
            void BindCursorInput(cursorFunctionType& function);

            /**
             * @brief Associate a 1-dimensional axis with a unique name
             * 
             * @param id the axis's name
             * @param positive Button representing +
             * @param negative Button representing -
             */
            void BindAxis(std::string id, Button positive, Button negative);
            /**
             * @brief Get the value of an axis from its name
             * 
             * @param id name of the axis
             * @return sign representing the direction pressed; zero if both buttons or neither are pressed
             */
            float GetAxisValue(std::string id) const;

            /**
             * @brief Associates a group of buttons as a 2-dimensional axis with a name
             * 
             * @param id the axis's name
             * @param up Button representing Y+
             * @param down Button representing Y-
             * @param left Button representing X-
             * @param right Button representing X+
             */
            void BindAxis2D(std::string id, Button up, Button down, Button left, Button right);
            /**
             * @brief Associates 2 joystick axes as a 2-dimensional axis with a name
             * 
             * @param id the axis's name
             * @param playerIndex The slot # of the joystick/controller
             * @param axisX device's X-axis index. Negative values are inverted
             * @param axisY device's Y-axis index Negative values are inverted
             */
            void BindAxis2D(std::string id, int playerIndex, int axisX, int axisY);
            /**
             * @brief Get the value of a 2-dimensional axis
             * 
             * @param id the axis's name
             * @return the longest of all axes associated with 'id'
             */
            Vector2 GetAxis2DValue(std::string id) const;

            /**
             * @brief Get whether or not a Button is pressed
             * 
             * @param button Button being checked
             * @return true if the button is pressed down, false if the button is not being pressed
             */
            bool ButtonPressed(Button button) const;

        private:
            std::vector<Joystick> _controllers;
            std::unordered_map<Button, std::string> _inputMap;
            std::unordered_map<std::string, voidFunctionType> _actionMap;
            std::forward_list<cursorFunctionType> _cursorInputMap;
            std::unordered_map<std::string, Axis> _axisMap;
            std::multimap<std::string, Axis2D*> _axis2DMap;
    };
}