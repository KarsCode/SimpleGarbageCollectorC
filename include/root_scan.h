/* This file is responsible for declaring the function that scans the stack and global variables to identify root references or active pointers. These roots server as the starting point for the mark phase.*/

#ifndef ROOT_SCAN_H
#define ROOT_SCAN_H

void gc_scan_roots(void);

#endif