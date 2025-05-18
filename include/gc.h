/* This is the interface for users of the garbage collector. Anyone using the GC will include this file to access core functions pertaining to memory allocation and collection*/

#ifndef GC_H
#define GC_H

#include <stddef.h>
void gc_init(void); //Initializes the GC
void *gc_malloc(size_t size); //Allocates memory with GC tracking
void gc_collect(void); //Runs the garbage collector manually
void gc_shutdown(void); //Frees all memory and shuts down the GC

#endif //GC_H

