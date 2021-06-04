#include "Buttons.h"

const unsigned int KEYBOARD_OFFSET = 232;
namespace Ceres
{

    Button Buttons::GetButton(SDL_Scancode scanCode)
    {
        return Button((int) scanCode);
    }

    Button Buttons::GetButton(SDL_GameControllerButton button)
    {
        return Button( ((int) button) + KEYBOARD_OFFSET );
    }

}