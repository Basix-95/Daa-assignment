#include <stdio.h>

int main() {
    int tests[10][2] = {
        {4, 10}, {5, 15}, {6, 12}, {5, 8}, {7, 20},
        {4, 6}, {5, 25}, {6, 18}, {8, 30}, {10, 50}
    };

    int weights[10][10] = {
        {5, 3, 4, 2},
        {2, 3, 4, 5, 9},
        {1, 2, 3, 8, 4, 5},
        {3, 4, 2, 1, 5},
        {2, 3, 4, 5, 9, 7, 6},
        {1, 2, 3, 4},
        {12, 7, 11, 8, 9},
        {3, 5, 6, 2, 4, 7},
        {4, 8, 5, 3, 6, 2, 9, 7},
        {5, 10, 15, 22, 25, 30, 35, 40, 45, 50}
    };

    int values[10][10] = {
        {60, 50, 70, 30},
        {10, 20, 30, 40, 50},
        {10, 15, 40, 90, 50, 60},
        {30, 50, 20, 10, 60},
        {12, 18, 25, 35, 50, 40, 30},
        {20, 30, 40, 50},
        {24, 13, 23, 15, 16},
        {10, 20, 30, 15, 25, 35},
        {10, 40, 30, 50, 70, 20, 60, 80},
        {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}
    };

    FILE *file = fopen("result.txt", "w");
    if (file == NULL) {
        printf("Error creating result.txt\n");
        return 1;
    }

    for (int t = 0; t < 10; t++) {
        int n = tests[t][0];
        int W = tests[t][1];
        int dp[11][51] = {0};

        printf("\n#Test %d\n", t + 1);

        for (int i = 1; i <= n; i++) {
            for (int w = 0; w <= W; w++) {
                dp[i][w] = dp[i - 1][w];

                if (weights[t][i - 1] <= w) {
                    int take = values[t][i - 1] +
                               dp[i - 1][w - weights[t][i - 1]];

                    if (take > dp[i][w])
                        dp[i][w] = take;
                }
            }

            printf("After item %d:\n", i);
            for (int r = 0; r <= i; r++) {
                for (int c = 0; c <= W; c++)
                    printf("%4d", dp[r][c]);
                printf("\n");
            }
        }

        printf("Maximum value: %d\n", dp[n][W]);
        fprintf(file, "#Test %d %d %d\n", n, W, dp[n][W]);
    }

    fclose(file);
    return 0;
}
