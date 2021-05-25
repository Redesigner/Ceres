#pragma once

namespace Ceres
{
    struct Vector3
    {
        public:
            Vector3(float x, float y, float z);
            ~Vector3();

            float X, Y, Z;
        private:
    };
}