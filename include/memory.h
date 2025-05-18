/* This file defines the data structures and functions to track and manage the allocated memory blocks. It is not exposed to the end user.*/

#ifndef MEMORY_H
#define MEMORY_H

#include<stddef.h>
#include<stdbool.h>

typedef struct MemoryBlock{
    struct MemoryBlock* next;
    size_t size;
    bool marked;
    void* data;
} MemoryBlock;

void *gc_internal_malloc(size_t size); //Internal function to allocate memory and wraps it in a memory block
void gc_register_allocation(MemoryBlock* block); //Adds a block to the internal tracking list
MemoryBlock *gc_get_allocations(void); //Returns the head of the allocated list
void gc_free_unmarked(void); // Sweeps unmarked memory blocks

#endif //MEMORY_H
