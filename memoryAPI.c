#include "memoryAPI.h"
#include <assert.h>
#define SIZE sizeof(size_t)
static size_t num_blocks = 0;
struct MemoryAllocator 
{
	size_t m_size;
	void* m_memoryPool;

};

MemoryAllocator* MemoryAllocator_init(void* memoryPool, size_t size)
{
	MemoryAllocator* memoryAllocator;
	assert(memoryPool);
	memoryAllocator = (MemoryAllocator*)calloc(size, sizeof(MemoryAllocator));
	if (size % SIZE != 0)
	{
		size -= (size % SIZE);
	}
	memoryAllocator->m_memoryPool = memoryPool;
	memoryAllocator->m_size = size;
	return memoryAllocator;
}

void* MemoryAllocator_allocate(MemoryAllocator* allocator, size_t size)
{
	size_t index = 0;
	size_t last_index = 0;
	size_t *block = (size_t*)allocator->m_memoryPool;
	size += SIZE;
	
	if (size > allocator->m_size)
			return NULL;

	if (size% SIZE != 0)
		size += (SIZE - size% SIZE);
	
	while (index < allocator->m_size)
	{
		if (size > (allocator->m_size - index))
			return NULL;

		if (*(block + index) == 0)/*memory from this point is empty*/
		{
			*(block+index) = size + 1;
			num_blocks++;
			return block+(index + SIZE);
		}
		else if (*(block+index)%SIZE == 1)/*this blok is not free*/
		{
			index += (*block+index) - 1 + SIZE;
		}
		else/*the blok is free*/
		{
			if (*(block+index) == size)/*the size of blok same like given size*/
			{
				*(block+index) += 1;	
				num_blocks++;
				return block+(index + SIZE);
			}
			if (*(block+index) > size)
			{
				last_index = *(block+index);
				*(block+index) = size + 1;
				index += last_index - size + SIZE;
				*(block+index) = last_index - size - SIZE;
				num_blocks++;
				return block+last_index;
			}
			if (*(block+index) < size)
			{
				last_index = index;
				index += *(block+index) + SIZE;
				if (*(block+index)%SIZE == 0)
				{
					*(block+last_index) += *(block+index) + SIZE;
				}
			}
		}			
	}
	return NULL;
}

/* Return number of still allocated blocks */
size_t MemoryAllocator_free(MemoryAllocator* allocator, void* ptr)
{ 
	size_t *block = (size_t*)allocator->m_memoryPool;
	if ((size_t*)ptr < block || (size_t*)ptr > (block + allocator->m_size * SIZE))
		return num_blocks;

	if ((*((size_t*)ptr))%SIZE == 1)
	{
		(*((size_t*)ptr)) -= 1;
		num_blocks--;
	}
	return num_blocks;

}

/* Return the size of largest free block */
size_t MemoryAllocator_optimize(MemoryAllocator* allocator)
{
	size_t *block = (size_t*)allocator->m_memoryPool;
	size_t i = 0;
	size_t j = 0;
	size_t max_block = 0;
	while (i < allocator->m_size)
	{
		if (*(block+i)%SIZE == 0)
		{
			j = SIZE + *(block+i);
			if (*(block+j)%SIZE == 0)
			{
				*(block+i) += *(block+j) + SIZE;
				if (max_block < *(block+j))
					max_block = *(block+j);
			}
			else
			{
				i = j;
				j = *(block+i) + SIZE;
			}
		}
		else
		{
			i = *(block+i) + SIZE;	
		}
	}
	return max_block;		
}

void print(MemoryAllocator* allocator)
{
	size_t i;
	printf("%ld \n", allocator->m_size);
	for (i = 0; i < (allocator)->m_size; ++i)
	{
	    printf("%ld ",  *((size_t*)allocator->m_memoryPool + i));
	}
	printf("\n");
}


