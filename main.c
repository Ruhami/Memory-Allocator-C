#include "memoryAPI.h"
void teseINIT()
{
	MemoryAllocator * allocator;
	void* memory = malloc(sizeof(size_t) * 50);
	allocator = MemoryAllocator_init(memory, 50);
	print(allocator);
	
	printf("NOT OK");
	return;
}

void testALLOCATE()
{


}

void testFREE()
{


}


void testOPTIMIZE()
{


}


int main()
{
	
	

	/*m = MemoryAllocator_allocate(memory, 8);
	print(memory);
	m = MemoryAllocator_allocate(memory, 30);
	print(memory);*/
	teseINIT();
	return 0;

}
