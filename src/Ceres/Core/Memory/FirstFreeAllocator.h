#pragma once

#include "Ceres/Core/Common/Types.h"

namespace Ceres
{
    class FirstFreeAllocator
    {
        public:
            FirstFreeAllocator(SizeType size, SizeType alignment);
            ~FirstFreeAllocator();

            uint8* allocateBlock(SizeType size);
            void freeBlock(uint8* data, SizeType size);

            /* Try to shift the block to the left if there is a free block. Returns the next address */
            uint8* tryShiftBlock(uint8* data, SizeType size);

        private:

            /* Entry in a linked list that stores the size of the free block */
            struct FreeBlockEntry
            {
                FreeBlockEntry* next;
                SizeType size;

                /* Merges two free blocks together and returns true if they were merged */
                static bool tryMergeBlocks(FreeBlockEntry* block1, FreeBlockEntry* block2);
            };

            /* Result from a search that contains two free block entries */ 
            struct FreeBlockSearchResult
            {
                FreeBlockEntry* previous;
                FreeBlockEntry* next;
            };

            FreeBlockSearchResult findFreeBlockOfSize(SizeType size) const;
            FreeBlockSearchResult findFreeBlocksAround(uint8* data) const;

            uint8* _data;
            FreeBlockEntry* _freeListHead;
    };
}
