#pragma once

#include "Ceres/Core/Common/Types.h"

namespace Ceres
{
    class PoolAllocator
    {
        public:

            PoolAllocator(SizeType blockSize, SizeType alignment, SizeType numBlocks);
            ~PoolAllocator();

            uint8* allocate();
            void free(uint8* data);

        private:

            uint8* _data;
            uint8* _freeHead;

    };
}
