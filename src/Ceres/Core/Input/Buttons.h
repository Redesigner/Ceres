#pragma once

extern "C"
{
    #include <SDL2/SDL.h>
}

namespace Ceres
{
    enum class Button
    {
        Key_a = 4,
        Key_b = 5,
        Key_c = 6,
        Key_d = 7,
        Key_e = 8,
        Key_f = 9,
        Key_g = 10,
        Key_h = 11,
        Key_i = 12,
        Key_j = 13,
        Key_k = 14,
        Key_l = 15,
        Key_m = 16,
        Key_n = 17,
        Key_o = 18,
        Key_p = 19,
        Key_q = 20,
        Key_r = 21,
        Key_s = 22,
        Key_t = 23,
        Key_u = 24,
        Key_v = 25,
        Key_w = 26,
        Key_x = 27,
        Key_y = 28,
        Key_z = 29,

        Key_1 = 30,
        Key_2 = 31,
        Key_3 = 32,
        Key_4 = 33,
        Key_5 = 34,
        Key_6 = 35,
        Key_7 = 36,
        Key_8 = 37,
        Key_9 = 38,
        Key_0 = 39,
        
        Key_enter = 40,
        Key_esc = 41,
        Key_backspace = 42,
        Key_tab = 43,
        Key_space = 44,
        Key_minus = 45,
        Key_equals = 46,
        Key_leftbracket = 47,
        Key_rightbracket = 48,
        Key_backslash = 49,
        Key_backslash2 = 50,
        Key_semicolon = 51,
        Key_singlequote = 52,
        Key_backtick = 53,
        Key_comma = 54,
        Key_period = 55,
        Key_slash = 56,
        Key_capslock = 57,
        Key_F1 = 58,
        Key_F2 = 59,
        Key_F3 = 60,
        Key_F4 = 61,
        Key_F5 = 62,
        Key_F6 = 63,
        Key_F7 = 64,
        Key_F8 = 65,
        Key_F9 = 66,
        Key_F10 = 67,
        Key_F11 = 68,
        Key_F12 = 69,
        Key_printscreen = 70,
        Key_pause = 72,
        Key_insert = 73,
        Key_home = 74,
        Key_pageup = 75,
        Key_delete = 76,
        Key_end = 77,
        Key_pagedown = 78,
        Key_right = 79,
        Key_left = 80,
        Key_down = 81,
        Key_up = 82,
        Key_leftctrl = 224,
        Key_leftshift = 225,
        Key_leftalt = 226,
        Key_rightctrl = 228,
        Key_rightshift = 229,
        Key_rightalt = 230,

        Gamepad_invalid = 232,
        Gamepad_a = 233,
        Gamepad_b = 234,
        Gamepad_x = 235,
        Gamepad_y = 236,
        Gamepad_leftbumper = 237,
        Gamepad_rightbumper = 238,
        Gamepad_back = 239,
        Gamepad_start = 240,
        Gamepad_lefthat = 241,
        Gampead_righthat = 242,
        Gamepad_home = 243
    };

    class Buttons
    {
        public:
            static Button GetButton(SDL_Scancode scanCode);
            static Button GetButton(SDL_GameControllerButton button);
            static Button GetButton(uint8_t buttonId);
    };
}