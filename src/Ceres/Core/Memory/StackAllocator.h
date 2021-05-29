#pragma once

#include "Ceres/Core/Common/Types.h"

namespace Ceres
{
    class StackAllocator
    {
        public:

            StackAllocator(SizeType size, SizeType alignment);
            ~StackAllocator();

            uint8* allocate(SizeType size, SizeType alignment = 1);
            void freeTo(SizeType marker);
            SizeType getMarker() const { return _head; }

        private:

            uint8* _data;
            SizeType _head;
            SizeType _size;
    };
}
