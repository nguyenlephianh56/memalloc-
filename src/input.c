#include <stdio.h>
#include "common.h"

/*
 * Định dạng file:
 *   dòng 1: số block n
 *   dòng 2: n kích thước block
 *   dòng 3: số tiến trình m
 *   dòng 4: m kích thước tiến trình
 * Trả về 0 nếu thành công, -1 nếu lỗi (có in lý do ra stderr).
 */
int read_input_file(const char *filename, Block blocks[], int *n, Process procs[], int *m)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Loi: khong mo duoc file '%s'\n", filename);
        return -1;
    }

    int nb, np, size;

    if (fscanf(f, "%d", &nb) != 1 || nb <= 0 || nb > MAX_BLOCKS) {
        fprintf(stderr, "Loi: so block khong hop le (phai tu 1 den %d)\n", MAX_BLOCKS);
        fclose(f);
        return -1;
    }
    for (int i = 0; i < nb; i++) {
        if (fscanf(f, "%d", &size) != 1 || size <= 0) {
            fprintf(stderr, "Loi: kich thuoc block thu %d thieu hoac khong hop le\n", i + 1);
            fclose(f);
            return -1;
        }
        blocks[i].id = i + 1;
        blocks[i].size = size;
        blocks[i].remaining = size;
    }

    if (fscanf(f, "%d", &np) != 1 || np <= 0 || np > MAX_PROCESSES) {
        fprintf(stderr, "Loi: so tien trinh khong hop le (phai tu 1 den %d)\n", MAX_PROCESSES);
        fclose(f);
        return -1;
    }
    for (int i = 0; i < np; i++) {
        if (fscanf(f, "%d", &size) != 1 || size <= 0) {
            fprintf(stderr, "Loi: kich thuoc tien trinh thu %d thieu hoac khong hop le\n", i + 1);
            fclose(f);
            return -1;
        }
        procs[i].id = i + 1;
        procs[i].size = size;
        procs[i].block_idx = NOT_ALLOCATED;
    }

    fclose(f);
    *n = nb;
    *m = np;
    return 0;
}
