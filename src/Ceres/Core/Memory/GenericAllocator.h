#pragma once

#include "Ceres/Core/Common/Types.h"

namespace Ceres
{
    class GenericAllocator
    {
        public:

            class Handle;

            GenericAllocator(SizeType size, uint32 maxBlocks);
            ~GenericAllocator();

            Handle allocate(SizeType size, SizeType alignment = 0);
            void defragment(uint32 numBlocks);

            class Handle
            {
                friend class GenericAllocator;
                friend class WeakHandle;

                public:
                    Handle()
                        : _allocator(nullptr), _index(0), _id(0)
                    {}

                    Handle(const Handle& other)
                        : _allocator(other._allocator), _index(other._index), _id(other._id)
                    {}

                    Handle& operator=(const Handle& other)
                    {
                        clear();
                        _allocator = other._allocator; _index = other._index; _id = other._id;
                        return *this;
                    }

                    ~Handle();

                    bool operator==(const Handle& other) const
                    {
                        return _allocator == other._allocator && _index == other._index && _id == other._id;
                    }

                    bool operator==(std::nullptr_t) { return !isValid(); }

                    operator bool() const { return isValid(); }

                    bool isExplictlyNull() const { return _allocator == nullptr; }
                    bool isValid() const;
                    uint8* getData() const;
                    void clear();

                private:

                    Handle(GenericAllocator& allocator, uint32 index, uint32 id);

                    GenericAllocator* _allocator;
                    uint32 _index;
                    uint32 _id;
            };

            class WeakHandle
            {
                public:

                    WeakHandle()
                        : _allocator(nullptr), _index(0), _id(0)
                    {}

                    WeakHandle(const Handle& other)
                        : _allocator(other._allocator), _index(other._index), _id(other._id)
                    {}

                    WeakHandle(const WeakHandle& other)
                        : _allocator(other._allocator), _index(other._index), _id(other._id)
                    {}

                    WeakHandle& operator=(const Handle& other)
                    {
                        _allocator = other._allocator; _index = other._index; _id = other._id;
                        return *this;
                    }

                    WeakHandle& operator=(const WeakHandle& other)
                    {
                        _allocator = other._allocator; _index = other._index; _id = other._id;
                        return *this;
                    }

                    bool operator==(const WeakHandle& other) const
                    {
                        return _allocator == other._allocator && _index == other._index && _id == other._id;
                    }

                    Handle pin() const;

                private:

                    GenericAllocator* _allocator;
                    uint32 _index;
                    uint32 _id;
            };

        private:

            struct BlockEntry;
            struct FreeBlockEntry;
            struct FreeBlockSearchResult;

            BlockEntry* findBlockEntry(const Handle& handle) const;
            uint8* getData(const Handle& handle) const;

            void incrementReferences(const Handle& handle);
            void decrementReferences(const Handle& handle);

            int32 findFirstUnusedBlockIndex() const;
            void freeBlock(BlockEntry& entry);

            FreeBlockSearchResult findFreeBlock(SizeType size) const;
            FreeBlockSearchResult findFreeBlock(const BlockEntry& entry) const;

            struct BlockEntry
            {
                uint32 id = 0;
                uint32 referenceCount = 0;
                uint8* data = nullptr;
                SizeType size = 0;
                SizeType offset = 0;

                static const int32 INVALID_INDEX = -1;
            };

            struct FreeBlockEntry
            {
                SizeType size = 0;
                FreeBlockEntry* nextFreeBlock = nullptr;
            };

            struct FreeBlockSearchResult
            {
                FreeBlockEntry* freeBlock;
                FreeBlockEntry* previousFreeBlock;
            };

            // Block table at start of allocated data
            BlockEntry* _blockTable;

            // Start of generic data (after block table)
            uint8* _genericData;

            FreeBlockEntry* _freeHead;

            SizeType _genericSize;
            uint32 _numBlocks;
    };
}
