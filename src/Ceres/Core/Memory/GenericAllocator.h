#pragma once

#include "Ceres/Core/Common/Types.h"
#include "Ceres/Core/Memory/FirstFreeAllocator.h"

namespace Ceres
{
    class GenericAllocator
    {
        private:
            struct DataBlockEntry;
        public:
            class Handle;
            class WeakHandle;

        public:
            GenericAllocator(SizeType size, SizeType numBlocks);

            /* Allocates a reference counted block of the given size */
            Handle allocateBlock(SizeType size);

            /**
             * Defragments a number of blocks by shifting them to the left.
             * Returns the number of blocks actually shifted.
             */
            SizeType defragmentBlocks(SizeType num);
            SizeType getNumBlocksUsed() const { return _numUsedBlocks; }

        private:

            DataBlockEntry* getBlockEntry(const Handle& handle) const;
            uint8* getBlockData(const Handle& handle) const;
            void incrementReferenceCount(const Handle& handle);
            void decrementReferenceCount(const Handle& handle);

            FirstFreeAllocator _allocator;
            DataBlockEntry* _dataBlockTable;
            SizeType _maxNumBlocks;
            SizeType _numUsedBlocks;

            struct DataBlockEntry
            {
                uint8* data;
                SizeType size;
                uint64 id;
                uint64 referenceCount;
            };

        public:

            class Handle
            {
                friend class GenericAllocator;
                friend class WeakHandle;

                public:
                    Handle();
                    Handle(const Handle& other);
                    Handle(Handle&& other);
                    ~Handle();

                    Handle& operator=(const Handle& other);
                    Handle& operator=(Handle&& other);
                    bool operator==(const Handle& other) const;
                    bool operator!=(const Handle& other) const { return !(*this == other); }

                    bool isExplicitlyNull() const;
                    uint8* get() const;
                    void clear();

                private:
                    Handle(GenericAllocator& allocator, uint64 index, uint64 id);

                    GenericAllocator* _allocator;
                    SizeType _index;
                    uint64 _id;
            };

            class WeakHandle
            {
                public:
                    WeakHandle();
                    WeakHandle(const WeakHandle& other);
                    WeakHandle(const Handle& other);

                    WeakHandle& operator=(const WeakHandle& other);
                    WeakHandle& operator=(const Handle& other);
                    bool operator==(const WeakHandle& other) const;
                    bool operator!=(const WeakHandle& other) const { return !(*this == other); }

                    bool isExplicitlyNull() const;
                    Handle pin() const;

                private:
                    GenericAllocator* _allocator;
                    SizeType _index;
                    uint64 _id;
            };
    };
}
