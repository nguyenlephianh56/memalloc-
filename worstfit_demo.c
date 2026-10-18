
#include <stdio.h>

#define MAX 1000

int main() {
    int n, m;
    int block[MAX], original[MAX];
    int process[MAX], allocated[MAX];
    int i, j, worst;
    int failed = 0, total = 0, largest = 0;

    printf("Nhap so block: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("So block khong hop le!\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Nhap kich thuoc B%d: ", i + 1);
        scanf("%d", &block[i]);

        if (block[i] <= 0) return 1;
        original[i] = block[i];
    }

    printf("Nhap so tien trinh: ");
    scanf("%d", &m);

    if (m <= 0 || m > MAX) {
        printf("So tien trinh khong hop le!\n");
        return 1;
    }

    for (i = 0; i < m; i++) {
        printf("Nhap kich thuoc P%d: ", i + 1);
        scanf("%d", &process[i]);

        if (process[i] <= 0) return 1;
        allocated[i] = -1;
    }

    // Thuat toan Worst Fit
    for (i = 0; i < m; i++) {
        worst = -1;

        for (j = 0; j < n; j++) {
            if (block[j] >= process[i]) {
                if (worst == -1 ||
                    block[j] > block[worst]) {
                    worst = j;
                }
            }
        }

        if (worst != -1) {
            allocated[i] = worst;
            block[worst] -= process[i];
        } else {
            failed++;
        }
    }

    // In ket qua
    printf("\n--- Worst Fit ---\n");
    printf("%-10s %-10s %-15s\n",
           "Process", "Size", "Block");

    for (i = 0; i < m; i++) {
        printf("P%-9d %-10d", i + 1, process[i]);

        if (allocated[i] != -1) {
            j = allocated[i];
            printf("B%d (%d)\n", j + 1, original[j]);
        } else {
            printf("Khong cap duoc\n");
        }
    }

    printf("Con trong moi block: ");
    for (i = 0; i < n; i++) {
        printf("B%d=%d ", i + 1, block[i]);

        total += block[i];

        if (block[i] > largest) {
            largest = block[i];
        }
    }

    printf("\nThat bai: %d | Tong con trong: %d",
           failed, total);
    printf(" | Block trong lon nhat: %d\n", largest);

    return 0;
}
