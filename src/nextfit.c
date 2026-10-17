#include "common.h"

/*
 * Next Fit: giống First Fit nhưng mỗi tiến trình bắt đầu tìm từ block
 * của lần cấp phát thành công trước đó (không quay về block 0), và duyệt vòng.
 */
void next_fit(Block blocks[], int n, Process procs[], int m)
{
    int last = 0;                       /* vị trí cấp phát gần nhất; khởi tạo lại mỗi lần gọi */

    for (int i = 0; i < m; i++) {
        procs[i].block_idx = NOT_ALLOCATED;

        for (int k = 0; k < n; k++) {   /* duyệt tối đa n block, đi vòng tròn */
            int j = (last + k) % n;
            if (blocks[j].remaining >= procs[i].size) {
                procs[i].block_idx = j;
                blocks[j].remaining -= procs[i].size;
                last = j;               /* nhớ vị trí cho tiến trình kế tiếp */
                break;
            }
        }
    }
}
