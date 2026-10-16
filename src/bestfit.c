#include "common.h"

void best_fit(Block blocks[], int n, Process procs[], int m) {
    for (int i = 0; i < m; i++) {
        int best_idx = -1;
        int min_diff = -1;

        for (int j = 0; j < n; j++) {
            if (blocks[j].remaining >= procs[i].size) {
                int diff = blocks[j].remaining - procs[i].size;
                if (best_idx == -1 || diff < min_diff) {
                    min_diff = diff;
                    best_idx = j;
                }
            }
        }

        if (best_idx != -1) {
            procs[i].block_idx = best_idx;
            blocks[best_idx].remaining -= procs[i].size;
        } else {
            procs[i].block_idx = NOT_ALLOCATED;
        }
    }
}
