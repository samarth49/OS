#include <stdio.h>

int main() {
    // Number of processes and resources
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    // Maximum resource matrix
    int max[n][m];

    // Allocation matrix
    int alloc[n][m];

    // Available resources vector
    int avail[m];

    // Need matrix
    int need[n][m];

    // Input the maximum resource matrix
    printf("Enter the maximum resource matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input the allocation matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input the available resources vector
    printf("Enter the available resources vector:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate the need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Banker's Algorithm
    int work[m];
    int finish[n];

    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int safeSeq[n];
    int count = 0;

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }

                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }

                    safeSeq[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if (found == 0) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }

    printf("System is in a safe state. Safe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", safeSeq[i]+1);
    }
    printf("\n");

    return 0;
}

