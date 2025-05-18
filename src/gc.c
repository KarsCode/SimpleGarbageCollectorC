#include "gc.h"
#include "memory.h"
#include "root_scan.h"

void gc_init(void) {
    // No special initialization for this basic GC
}

void *gc_malloc(size_t size) {
    return gc_internal_malloc(size);
}

void gc_collect(void) {
    // Step 1: Mark reachable blocks
    gc_scan_roots();

    // Step 2: Sweep unreachable ones
    gc_free_unmarked();
}

void gc_shutdown(void) {
    // Run a final sweep to clean up everything
    gc_collect();
}
