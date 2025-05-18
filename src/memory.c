#include "../include/memory.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static MemoryBlock *allocations = NULL; // Head of the linked list tracking all allocated blocks

/**
 * Allocates a new memory block of given size.
 * Internally allocates a MemoryBlock struct for metadata and a data buffer for user.
 * Adds the new block to the allocations list.
 * Returns pointer to the allocated data buffer.
 */

void *gc_internal_malloc(size_t size) {
    MemoryBlock *block = malloc(sizeof(MemoryBlock));
    if (!block) return NULL;

    block->size = size;
    block->marked = false;
    block->data = malloc(size);
    if (!block->data) {
        free(block);
        return NULL;
    }

    block->next = allocations;
    allocations = block;
    return block->data;
}

/**
 * Registers a pre-existing MemoryBlock by adding it to the allocations list.
 * Used if allocations are created outside gc_internal_malloc.
 */
void gc_register_allocation(MemoryBlock *block) {
    block->next = allocations;
    allocations = block;
}

/**
 * Returns the head of the linked list containing all allocated memory blocks.
 * Useful for iterating over all tracked allocations during GC phases.
 */
MemoryBlock *gc_get_allocations(void) {
    return allocations;
}

/**
 * Sweeps through all allocated blocks, freeing those that are unmarked.
 * Unmarked blocks are unreachable and considered garbage.
 * Marked blocks are kept, but their mark flags are reset for the next GC cycle.
 */
void gc_free_unmarked(void) {
    MemoryBlock **curr = &allocations;
    while (*curr) {
        MemoryBlock *block = *curr;
        if (!block->marked) {
            printf("[GC] Freeing unreachable block of size %zu\n", block->size);  // DEBUG
            free(block->data);
            MemoryBlock *to_free = block;
            *curr = block->next;
            free(to_free);
        } else {
            block->marked = false; // reset for next GC cycle
            curr = &block->next;
        }
    }
}

