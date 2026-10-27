#include <stdio.h>
#include <limits.h>

int n, w[100], lc[200], rc[200], wt[200], level[100];

void setLevels(int node, int depth) {
    if (node < n) {
        level[node] = depth;
        return;
    }
    setLevels(lc[node], depth + 1);
    setLevels(rc[node], depth + 1);
}

int main() {
    int i, j, k, len;

    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter weights: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &w[i]);
        wt[i] = w[i];
    }

    int cur[100], m = n, next = n;
    for (i = 0; i < n; i++)
        cur[i] = i;

    while (m > 1) {
        int bestA = -1, bestB = -1, bestSum = 0;
        for (i = 0; i < m; i++) {
            for (j = i + 1; j < m; j++) {
                int sum = wt[cur[i]] + wt[cur[j]];
                if (bestA == -1 || sum < bestSum) {
                    bestSum = sum;
                    bestA = i;
                    bestB = j;
                }
                if (cur[j] < n) break;
            }
        }
        wt[next] = bestSum;
        lc[next] = cur[bestA];
        rc[next] = cur[bestB];
        cur[bestA] = next;
        next++;
        for (k = bestB; k < m - 1; k++)
            cur[k] = cur[k + 1];
        m--;
    }

    setLevels(cur[0], 0);

    int cost = 0;
    printf("\nLevels: ");
    for (i = 0; i < n; i++) {
        printf("%d ", level[i]);
        cost += w[i] * level[i];
    }
    printf("\nHu-Tucker cost: %d\n", cost);

    int st[100], top = 0;
    for (i = 0; i < n; i++) {
        st[top++] = level[i];
        while (top >= 2 && st[top - 1] == st[top - 2]) {
            st[top - 2]--;
            top--;
        }
    }
    printf("Levels form a valid alphabetic tree: %s\n", (top == 1 && st[0] == 0) ? "yes" : "no");

    int pre[101], dp[100][100];
    pre[0] = 0;
    for (i = 0; i < n; i++)
        pre[i + 1] = pre[i] + w[i];
    for (i = 0; i < n; i++)
        dp[i][i] = 0;
    for (len = 2; len <= n; len++) {
        for (i = 0; i + len - 1 < n; i++) {
            j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (k = i; k < j; k++) {
                int c = dp[i][k] + dp[k + 1][j] + pre[j + 1] - pre[i];
                if (c < dp[i][j]) dp[i][j] = c;
            }
        }
    }
    printf("DP check cost: %d\n", dp[0][n - 1]);
    printf("Match: %s\n", dp[0][n - 1] == cost ? "yes" : "NO");
    return 0;
}
