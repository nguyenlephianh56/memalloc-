#include <stdio.h>
#include "common.h"

int count_failed(const Process procs[], int m)
{
    int c = 0;
    for (int i = 0; i < m; i++)
        if (procs[i].block_idx == NOT_ALLOCATED) c++;
    return c;
}

int total_free(const Block blocks[], int n)
{
    int s = 0;
    for (int j = 0; j < n; j++) s += blocks[j].remaining;
    return s;
}

int largest_free_block(const Block blocks[], int n)
{
    int mx = 0;
    for (int j = 0; j < n; j++)
        if (blocks[j].remaining > mx) mx = blocks[j].remaining;
    return mx;
}

void print_stats(const char *algo_name, const Block blocks[], int n,
                 const Process procs[], int m)
{
    (void)algo_name;
    printf("That bai: %d | Tong con trong: %d | Block trong lon nhat: %d\n",
           count_failed(procs, m), total_free(blocks, n), largest_free_block(blocks, n));
}
