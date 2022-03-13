#pragma once

using uchar = unsigned char;

namespace Ceres
{
    struct Color
    {
        public:
            /// A 24-bit color value, with each channel ranging from 0-255.
            /// Internally represented as a BGR value.
            Color(uchar r, uchar g, uchar b) : R(r), G(g), B(b) {};

            uchar B;
            uchar G;
            uchar R;
            uchar A;

        static Color Red() { return Color(255, 0, 0); }
        static Color Blue() { return Color(0, 0, 255); }
    };
}