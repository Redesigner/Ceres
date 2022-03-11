#include "Buttons.h"

const unsigned int KEYBOARD_OFFSET = 232;
namespace Ceres
{

    Button Buttons::GetButton(SDL_Scancode scanCode)
    {
        return Button(scanCode);
    }

    Button Buttons::GetButton(SDL_GameControllerButton button)
    {
        return Button(button + KEYBOARD_OFFSET);
    }

    Button Buttons::GetButton(uint8_t buttonId)
    {
        return Button(buttonId + 233);
    }

}