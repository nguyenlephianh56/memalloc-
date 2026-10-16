#include <stdio.h>
#include "common.h"

void print_result(const char *name, const Block blocks[], int n, const Process procs[], int m) {
    printf("--- %s ---\n", name);
    printf("%-9s %-6s %s\n", "Process", "Size", "Block");
    for (int i = 0; i < m; i++) {
        if (procs[i].block_idx != NOT_ALLOCATED) {
            int b_idx = procs[i].block_idx;
            printf("P%-8d %-6d B%d (%d)\n", procs[i].id, procs[i].size, blocks[b_idx].id, blocks[b_idx].size);
        } else {
            printf("P%-8d %-6d Khong cap duoc\n", procs[i].id, procs[i].size);
        }
    }
    printf("Con trong moi block: ");
    for (int j = 0; j < n; j++) {
        printf("B%d=%d%s", blocks[j].id, blocks[j].remaining, (j == n - 1) ? "" : " ");
    }
    printf("\n");
}
