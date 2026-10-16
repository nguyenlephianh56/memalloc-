#include "common.h"

void init_sample_data(Block blocks[], int *n, Process procs[], int *m)
{
    int bs[] = {100, 500, 200, 300, 600};   /* kích thước 5 block */
    int ps[] = {212, 417, 112, 426};        /* kích thước 4 tiến trình */
    *n = 5;
    *m = 4;
    for (int i = 0; i < *n; i++) {
        blocks[i].id = i + 1;
        blocks[i].size = bs[i];
        blocks[i].remaining = bs[i];
    }
    for (int i = 0; i < *m; i++) {
        procs[i].id = i + 1;
        procs[i].size = ps[i];
        procs[i].block_idx = NOT_ALLOCATED;
    }
}

void copy_blocks(const Block src[], Block dst[], int n)
{
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
}

void reset_processes(Process procs[], int m)
{
    for (int i = 0; i < m; i++)
        procs[i].block_idx = NOT_ALLOCATED;
}
