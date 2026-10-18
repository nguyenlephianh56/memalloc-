#include "common.h"

void first_fit(Block blocks[], int n, Process procs[], int m)
{
    for (int i = 0; i < m; i++) {
        procs[i].block_idx = NOT_ALLOCATED;

        for (int j = 0; j < n; j++) {
            if (blocks[j].remaining >= procs[i].size) {
                procs[i].block_idx = j;
                blocks[j].remaining -= procs[i].size;
                break;                
            }
        }
    }
}
