#include <stdio.h>

int main() {
    int n, i, j;
    char sym[50];
    int freq[100], parent[100], active[100], len[50], order[50];

    printf("Enter number of symbols: ");
    scanf("%d", &n);
    printf("Enter symbol and frequency:\n");
    for (i = 0; i < n; i++)
        scanf(" %c %d", &sym[i], &freq[i]);

    for (i = 0; i < 2 * n; i++) {
        parent[i] = -1;
        active[i] = (i < n);
    }

    int count = n;
    for (int step = 1; step < n; step++) {
        int m1 = -1, m2 = -1;
        for (i = 0; i < count; i++) {
            if (!active[i]) continue;
            if (m1 == -1 || freq[i] < freq[m1]) {
                m2 = m1;
                m1 = i;
            } else if (m2 == -1 || freq[i] < freq[m2]) {
                m2 = i;
            }
        }
        freq[count] = freq[m1] + freq[m2];
        parent[m1] = count;
        parent[m2] = count;
        active[m1] = 0;
        active[m2] = 0;
        active[count] = 1;
        count++;
    }

    for (i = 0; i < n; i++) {
        len[i] = 0;
        int node = i;
        while (parent[node] != -1) {
            node = parent[node];
            len[i]++;
        }
        if (len[i] == 0) len[i] = 1;
        order[i] = i;
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            int a = order[j], b = order[j + 1];
            if (len[a] > len[b] || (len[a] == len[b] && sym[a] > sym[b])) {
                order[j] = b;
                order[j + 1] = a;
            }
        }
    }

    long code = 0;
    int prevLen = len[order[0]];
    int totalBits = 0;
    printf("\nSymbol  Freq  Length  Code\n");
    for (i = 0; i < n; i++) {
        int s = order[i];
        code = code << (len[s] - prevLen);
        prevLen = len[s];
        printf("%c       %-5d %-7d ", sym[s], freq[s], len[s]);
        for (int b = len[s] - 1; b >= 0; b--)
            printf("%ld", (code >> b) & 1);
        printf("\n");
        totalBits += freq[s] * len[s];
        code++;
    }
    printf("Total encoded length: %d bits\n", totalBits);
    return 0;
}
