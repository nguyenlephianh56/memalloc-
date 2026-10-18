
#include "common.h"

// Thuat toan Worst Fit
void worst_fit(Block blocks[], int n, Process procs[], int m) {
    int i, j, worst;

    // Duyet tung tien trinh
    for (i = 0; i < m; i++) {
        worst = -1;
        procs[i].block_idx = NOT_ALLOCATED;

        // Tim block con trong lon nhat
        for (j = 0; j < n; j++) {
            if (blocks[j].remaining >= procs[i].size) {
                if (worst == -1 ||
                    blocks[j].remaining > blocks[worst].remaining) {
                    worst = j;
                }
            }
        }

        // Cap phat bo nho
        if (worst != -1) {
            procs[i].block_idx = worst;
            blocks[worst].remaining -= procs[i].size;
        }
    }
}
