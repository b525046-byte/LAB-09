#include <stdio.h>
#include <string.h>

char str[10][100], f[10][100];
int m, ov[10][10], used[10], bestTotal = -1;

int overlap(char *a, char *b) {
    int la = strlen(a), lb = strlen(b);
    int max = la < lb ? la : lb;
    for (int k = max; k >= 1; k--) {
        if (strncmp(a + la - k, b, k) == 0)
            return k;
    }
    return 0;
}

void dfs(int last, int count, int total) {
    if (count == m) {
        if (total > bestTotal) bestTotal = total;
        return;
    }
    for (int next = 0; next < m; next++) {
        if (used[next]) continue;
        used[next] = 1;
        dfs(next, count + 1, total + (last == -1 ? 0 : ov[last][next]));
        used[next] = 0;
    }
}

int main() {
    int n, i, j;

    printf("Enter number of strings (max 8): ");
    scanf("%d", &n);
    printf("Enter strings:\n");
    for (i = 0; i < n; i++)
        scanf("%99s", str[i]);

    m = 0;
    for (i = 0; i < n; i++) {
        int drop = 0;
        for (j = 0; j < n; j++) {
            if (i != j && strstr(str[j], str[i]) &&
                (strlen(str[j]) > strlen(str[i]) || j < i))
                drop = 1;
        }
        if (!drop) strcpy(f[m++], str[i]);
    }

    char s[10][100];
    int count = m;
    for (i = 0; i < m; i++)
        strcpy(s[i], f[i]);

    while (count > 1) {
        int bi = 0, bj = 1, best = -1;
        for (i = 0; i < count; i++) {
            for (j = 0; j < count; j++) {
                if (i == j) continue;
                int o = overlap(s[i], s[j]);
                if (o > best) {
                    best = o;
                    bi = i;
                    bj = j;
                }
            }
        }
        char tmp[200];
        strcpy(tmp, s[bi]);
        strcat(tmp, s[bj] + best);
        strcpy(s[bi], tmp);
        if (bj != count - 1)
            strcpy(s[bj], s[count - 1]);
        count--;
    }
    int greedyLen = strlen(s[0]);
    printf("\nGreedy superstring: %s (length %d)\n", s[0], greedyLen);

    int sumLen = 0;
    for (i = 0; i < m; i++) {
        sumLen += strlen(f[i]);
        for (j = 0; j < m; j++)
            ov[i][j] = (i == j) ? 0 : overlap(f[i], f[j]);
    }
    dfs(-1, 0, 0);
    int optLen = sumLen - bestTotal;
    printf("Optimal length (brute force): %d\n", optLen);
    printf("Ratio greedy/optimal: %.3f\n", (double)greedyLen / optLen);
    return 0;
}
