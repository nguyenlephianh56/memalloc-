#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/* Con trỏ hàm chung cho 4 thuật toán */
typedef void (*AllocFn)(Block[], int, Process[], int);

static Block   g_blocks[MAX_BLOCKS];    /* dữ liệu gốc, không bị thuật toán sửa */
static Process g_procs[MAX_PROCESSES];
static int     g_n = 0;                 /* số block */
static int     g_m = 0;                 /* số process */

/* Chạy 1 thuật toán trên bản sao dữ liệu, rồi in kết quả */
static void run_algorithm(const char *name, AllocFn fn)
{
    static Block   work_blocks[MAX_BLOCKS];
    static Process work_procs[MAX_PROCESSES];

    copy_blocks(g_blocks, work_blocks, g_n);
    for (int i = 0; i < g_m; i++)
        work_procs[i] = g_procs[i];
    reset_processes(work_procs, g_m);

    fn(work_blocks, g_n, work_procs, g_m);

    print_result(name, work_blocks, g_n, work_procs, g_m);
    print_stats(name, work_blocks, g_n, work_procs, g_m);
}

static void print_menu(void)
{
    printf("\n========== MEMORY ALLOCATION SIMULATOR ==========\n");
    printf(" 1. First Fit\n");
    printf(" 2. Next Fit\n");
    printf(" 3. Best Fit\n");
    printf(" 4. Worst Fit\n");
    printf(" 5. Chay ca 4 thuat toan (so sanh)\n");
    printf(" 0. Thoat\n");
    printf("=================================================\n");
    printf("Chon: ");
}

int main(int argc, char *argv[])
{
    /* Có truyền tên file -> đọc file; không có -> dùng dữ liệu mẫu gán cứng */
    if (argc > 1) {
        if (read_input_file(argv[1], g_blocks, &g_n, g_procs, &g_m) != 0) {
            fprintf(stderr, "Loi: khong doc duoc file '%s'\n", argv[1]);
            return 1;
        }
        printf("Da doc du lieu tu file: %s\n", argv[1]);
    } else {
        init_sample_data(g_blocks, &g_n, g_procs, &g_m);
        printf("Chay kich ban 1 (small): du lieu gan cung trong code, chua truyen file input.\n");
    }
    printf("So block: %d | So tien trinh: %d\n", g_n, g_m);

    int choice;
    do {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            /* nhập sai kiểu (chữ thay vì số): xoá bộ đệm và hỏi lại */
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
            choice = -1;
        }

        switch (choice) {
        case 1: run_algorithm("First Fit", first_fit); break;
        case 2: run_algorithm("Next Fit",  next_fit);  break;
        case 3: run_algorithm("Best Fit",  best_fit);  break;
        case 4: run_algorithm("Worst Fit", worst_fit); break;
        case 5:
            run_algorithm("First Fit", first_fit);
            run_algorithm("Next Fit",  next_fit);
            run_algorithm("Best Fit",  best_fit);
            run_algorithm("Worst Fit", worst_fit);
            break;
        case 0: printf("Tam biet!\n"); break;
        default: printf("Lua chon khong hop le, nhap lai.\n");
        }
    } while (choice != 0);

    return 0;
}
