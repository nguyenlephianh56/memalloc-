#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>

/* ---------- Hằng số ---------- */
#define MAX_BLOCKS     1000
#define MAX_PROCESSES  1000
#define NOT_ALLOCATED  (-1)   /* gán cho Process.block_idx khi cấp phát thất bại */

/* ---------- Cấu trúc dữ liệu ---------- */

/* Một khối bộ nhớ trống */
typedef struct {
    int id;          /* số thứ tự block (bắt đầu từ 1, để in cho dễ nhìn) */
    int size;        /* kích thước gốc, không thay đổi */
    int remaining;   /* dung lượng còn trống, giảm dần khi cấp phát */
} Block;

/* Một tiến trình cần cấp phát */
typedef struct {
    int id;          /* số thứ tự tiến trình (bắt đầu từ 1) */
    int size;        /* kích thước yêu cầu */
    int block_idx;   /* chỉ số (index mảng) của block được cấp, NOT_ALLOCATED nếu thất bại */
} Process;

/* ---------- memory.c ---------- */
/* Gán dữ liệu mẫu cứng (dùng cho demo khi chưa đọc file) */
void init_sample_data(Block blocks[], int *n, Process procs[], int *m);

/* Sao chép mảng block để mỗi thuật toán chạy trên bản riêng, tránh ảnh hưởng nhau */
void copy_blocks(const Block src[], Block dst[], int n);

/* Đặt lại block_idx = NOT_ALLOCATED cho tất cả tiến trình trước mỗi lần chạy */
void reset_processes(Process procs[], int m);

/* ---------- input.c ---------- */
/* Đọc file input theo định dạng: n / n kích thước block / m / m kích thước process.
   Trả về 0 nếu thành công, -1 nếu lỗi (không mở được file, sai định dạng...) */
int read_input_file(const char *path, Block blocks[], int *n, Process procs[], int *m);

/* ---------- 4 thuật toán cấp phát ----------
   Quy ước chung: duyệt lần lượt từng tiến trình trong procs[],
   nếu tìm được block phù hợp thì ghi procs[i].block_idx = chỉ số block
   và trừ blocks[j].remaining đi procs[i].size; nếu không thì để NOT_ALLOCATED. */
void first_fit(Block blocks[], int n, Process procs[], int m);   /* firstfit.c */
void next_fit(Block blocks[], int n, Process procs[], int m);    /* nextfit.c  */
void best_fit(Block blocks[], int n, Process procs[], int m);    /* bestfit.c  */
void worst_fit(Block blocks[], int n, Process procs[], int m);   /* worstfit.c */

/* ---------- output.c ---------- */
/* In bảng kết quả: tiến trình nào vào block nào, tiến trình nào thất bại, block còn dư bao nhiêu */
void print_result(const char *algo_name, const Block blocks[], int n,
                  const Process procs[], int m);

/* ---------- stats.c ---------- */
int  count_failed(const Process procs[], int m);                 /* số tiến trình không được cấp */
int  total_free(const Block blocks[], int n);                    /* tổng bộ nhớ còn trống */
int  largest_free_block(const Block blocks[], int n);            /* block trống lớn nhất (đánh giá external fragmentation) */
void print_stats(const char *algo_name, const Block blocks[], int n,
                 const Process procs[], int m);

#endif /* COMMON_H */
