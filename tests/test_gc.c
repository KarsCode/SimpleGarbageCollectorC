#include "../include/gc.h"
#include <stdio.h>
#include <string.h>

void create_live_and_dead_objects(char **out1, char **out2) {
    // Live object: pointer stored in out1
    char *live_data1 = gc_malloc(100);
    strcpy(live_data1, "I'm alive!");
    *out1 = live_data1;

    // Dead objects: no reference kept
    gc_malloc(50);
    gc_malloc(30);

    // Live object: pointer stored in out2
    char *live_data2 = gc_malloc(100);
    strcpy(live_data2, "I'm still alive!");
    *out2 = live_data2;

    // Print before GC
    printf("Before GC:\n");
    printf("  live_data1 = %s\n", live_data1);
    printf("  live_data2 = %s\n", live_data2);
}

int main() {
    gc_init();  // Optional in this case, but good habit

    char *live_data1 = NULL;
    char *live_data2 = NULL;

    create_live_and_dead_objects(&live_data1, &live_data2);

    // Explicit GC call
    gc_collect();

    //Ensure live pointers are still valid after GC
    printf("After GC:\n");
    printf("  live_data1 = %s\n", live_data1);
    printf("  live_data2 = %s\n", live_data2);

    return 0;
}
