#include <stdio.h>
#include <stdlib.h>

typedef struct MemoryAllocator MemoryAllocator;

MemoryAllocator* MemoryAllocator_init(void* memoryPool, size_t size);

void* MemoryAllocator_allocate(MemoryAllocator* allocator, size_t size);

/* Return number of still allocated blocks */
size_t MemoryAllocator_free(MemoryAllocator* allocator, void* ptr);

/* Return the size of largest free block */
size_t MemoryAllocator_optimize(MemoryAllocator* allocator);
void print(MemoryAllocator* allocator);
