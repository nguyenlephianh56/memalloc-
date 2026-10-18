#include <stdio.h>
#include "common.h"

#ifndef ALGO
#error "Thieu -DALGO=ten_ham (first_fit, next_fit, best_fit, worst_fit)"
#endif
#define STR(x) #x
#define XSTR(x) STR(x)

static const char *pretty(void)
{
    const char *s = XSTR(ALGO);
    if (s[0]=='f') return "First Fit";
    if (s[0]=='n') return "Next Fit";
    if (s[0]=='b') return "Best Fit";
    return "Worst Fit";
}

int main(void)
{
    Block blocks[MAX_BLOCKS];
    Process procs[MAX_PROCESSES];
    int n, m;

    printf("Nhap so block: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_BLOCKS) { printf("So block khong hop le!\n"); return 1; }
    for (int i = 0; i < n; i++) {
        printf("Nhap kich thuoc B%d: ", i + 1);
        if (scanf("%d", &blocks[i].size) != 1 || blocks[i].size <= 0) { printf("Kich thuoc khong hop le!\n"); return 1; }
        blocks[i].id = i + 1;
        blocks[i].remaining = blocks[i].size;
    }

    printf("Nhap so tien trinh: ");
    if (scanf("%d", &m) != 1 || m <= 0 || m > MAX_PROCESSES) { printf("So tien trinh khong hop le!\n"); return 1; }
    for (int i = 0; i < m; i++) {
        printf("Nhap kich thuoc P%d: ", i + 1);
        if (scanf("%d", &procs[i].size) != 1 || procs[i].size <= 0) { printf("Kich thuoc khong hop le!\n"); return 1; }
        procs[i].id = i + 1;
        procs[i].block_idx = NOT_ALLOCATED;
    }

    ALGO(blocks, n, procs, m);

    printf("\n");
    print_result(pretty(), blocks, n, procs, m);
    print_stats(pretty(), blocks, n, procs, m);
    return 0;
}
