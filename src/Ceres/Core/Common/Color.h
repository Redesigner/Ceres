#pragma once

using uchar = unsigned char;

namespace Ceres
{
    struct Color
    {
        public:
            Color(uchar r, uchar g, uchar b) : R(r), G(g), B(b) {};

            uchar B;
            uchar G;
            uchar R;
            uchar A;

        static Color Red() { return Color(255, 0, 0); }
        static Color Blue() { return Color(0, 0, 255); }
    };
}