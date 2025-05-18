# Simple Mark-and-Sweep Garbage Collector in C

This project implements a simple **mark-and-sweep garbage collector** in the C programming language. It serves as an educational demonstration of how automatic memory management can be layered on top of a language that does not provide built-in garbage collection.

## Overview

Garbage collection (GC) is a memory management technique used to automatically reclaim memory that is no longer reachable by the program. While languages like Java and Python include garbage collection as part of the runtime, C requires manual memory management. This project showcases how to build a custom garbage collector using the classic mark-and-sweep approach.

## Features

- Custom `gc_malloc(size_t)` for memory allocation with tracking.
- Memory managed using linked lists of `MemoryBlock` structures.
- Mark phase: identifies live memory through stack scanning.
- Sweep phase: deallocates unreachable memory blocks.
- Minimal test suite to demonstrate usage and effectiveness.

## Project Structure

```
gc_project/
├── include/
│   ├── gc.h            # Public interface for GC functions
│   ├── memory.h        # Internal memory block structures
│   └── root_scan.h     # Stack scanning declarations
├── src/
│   ├── gc.c            # High-level garbage collection logic
│   ├── memory.c        # Allocation and sweep logic
│   └── root_scan.c     # Mark phase implementation (stack scanning)
├── tests/
│   └── test_gc.c       # Sample test program
├── Makefile            # Build script
└── README.md           # Project documentation
```

## How It Works

### 1. Allocation

Memory is allocated using `gc_malloc(size)`, which wraps the system `malloc()` and tracks the allocation in a `MemoryBlock` linked list.

### 2. Root Scanning (Mark Phase)

During garbage collection, the stack is scanned for potential pointers to allocated memory blocks. If a match is found, the block is marked as "live."

### 3. Sweeping

All memory blocks not marked during the mark phase are considered unreachable and are freed. The `marked` flag is then reset for the next cycle.

## Example Output

```text
Before GC: live_data1 = I'm alive!
Before GC: live_data2 = I'm still alive!
[GC] Freeing unreachable block of size 50
[GC] Freeing unreachable block of size 30
Garbage collection done.
```

## Building and Running

### Build

```bash
make
```

This compiles all source files into an executable.

### Run

```bash
./test_gc
```

This runs the test demonstrating garbage collection in action.

## Key Concepts

| Term             | Description |
|------------------|-------------|
| `MemoryBlock`    | Struct storing metadata for each allocation |
| `gc_malloc()`    | Allocates memory and tracks it for GC |
| `gc_collect()`   | Initiates a mark-and-sweep collection |
| `gc_scan_roots()`| Performs root scanning by analyzing stack memory |
| `gc_free_unmarked()` | Frees memory blocks not marked as reachable |

## Limitations

- Stack scanning only; does not track static or global references.
- Platform-specific reliance on `__libc_stack_end`.
- Not thread-safe.
- No compaction or generational strategies.
- Limited portability across non-glibc environments.

## Motivation

This project is intended as a systems programming exercise to understand:
- How garbage collection works internally.
- The challenges of memory management in C.
- How pointers and stack memory can be analyzed at runtime.

## References

- [Writing a Simple Garbage Collector in C](https://maplant.com/2020-04-25-Writing-a-Simple-Garbage-Collector-in-C.html)
- [Computer Systems: A Programmer's Perspective (CS:APP)](https://csapp.cs.cmu.edu/)
- [MIT OpenCourseWare - Garbage Collection](https://ocw.mit.edu/)
