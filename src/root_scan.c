#include "../include/root_scan.h"
#include "../include/memory.h"
#include <stdint.h>
#include <stdbool.h>

extern void *__libc_stack_end;

/**
 * This function is responsible for the root scanning phase of the GC
 * This involves examining certain known memory locations(in this case, the stack to find pointers to allocated memory blocks).
 * Any allocated block that is pointed to by the root is considered to be 'live' and marked to avoid being swept during the sweeping phase.
 */

 /**
  * Please note that on x86/x86_64 Linux, the stack grows downward. The top of the stack is at a higher memory address (__lib_stack_end), and the current stack pointer is at a lower address (&local_var).
  */



void gc_scan_roots(void) {
    uintptr_t *stack_top = (uintptr_t *)__libc_stack_end; 

    // Local variable to get current stack pointer (stack bottom)
    uintptr_t local_var = 0;
    uintptr_t *stack_bottom = &local_var;

    for (uintptr_t *ptr = stack_bottom; ptr < stack_top; ptr++) // Here we iterate over every word-sized chunk of the stack memory between the current stack pointer and the end of the stack
    {
        uintptr_t potential_ptr = *ptr;

        for (MemoryBlock *block = gc_get_allocations(); block != NULL; block = block->next) {
            uintptr_t block_start = (uintptr_t)block->data;
            uintptr_t block_end = block_start + block->size;

            if (potential_ptr >= block_start && potential_ptr < block_end) {
                block->marked = true;
            }
        }
    }
}
