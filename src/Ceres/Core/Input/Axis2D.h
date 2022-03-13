#pragma once

#include "Buttons.h"
#include "Joystick.h"
#include "../Common/Vector2.h"

#include <vector>

namespace Ceres
{
    /**
     * @brief 2-dimenstional input axis
     * 
     */
    struct Axis2D
    {
        public:
            /**
             * @brief Get the value of our axes combined
             * 
             * @return Vector2 with a maximum length of 1
             */
            virtual Vector2 GetValue() const = 0;
    };

    struct Axis2DKey : public Axis2D
    {
        /**
         * @brief Construct a new Axis2DKey object
         * 
         * @param up Key for Y+
         * @param down Key for Y-
         * @param left Key for X-
         * @param right Key for X+
         */
        Axis2DKey(Button up, Button down, Button left, Button right);

        virtual Vector2 GetValue() const override;

        private:
            bool buttonPressed(Button button) const;
            Button _up, _left, _down, _right;
    };

    struct Axis2DJoy : public Axis2D
    {
        /**
         * @brief Construct a new Axis2DJoy object
         * 
         * @param controllerContainer Object holding all of our controllers
         * @param playerIndex The index of the controller
         * @param axisX The device's X-axis index
         * @param axisY The device's Y-axis index
         */
        Axis2DJoy(std::vector<Joystick>& controllerContainer, int playerIndex, int axisX, int axisY);

        virtual Vector2 GetValue() const override;

        private:
            int _axisX, _axisY;
            std::vector<Joystick>& _controllerContainer;
            int _playerIndex;
    };
}