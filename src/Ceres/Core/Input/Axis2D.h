#pragma once

#include "Buttons.h"
#include "Joystick.h"
#include "../Common/Vector2.h"

#include <vector>

namespace Ceres
{
    struct Axis2D
    {
        public:
            virtual Vector2 GetValue() const = 0;
    };

    struct Axis2DKey : public Axis2D
    {
        Axis2DKey(Button up, Button down, Button left, Button right);

        virtual Vector2 GetValue() const override;

        private:
            bool buttonPressed(Button button) const;
            Button _up, _left, _down, _right;
    };

    struct Axis2DJoy : public Axis2D
    {
        Axis2DJoy(std::vector<Joystick>& controllerContainer, int playerIndex, int axisX, int axisY);

        virtual Vector2 GetValue() const override;

        private:
            int _axisX, _axisY;
            std::vector<Joystick>& _controllerContainer;
            int _playerIndex;
    };
}