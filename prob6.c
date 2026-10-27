#include <stdio.h>
#include <string.h>

int main() {
    char s[1000], result[1000];
    int k, i, c;
    int count[256] = {0}, last[256];

    printf("Enter string: ");
    scanf("%999s", s);
    printf("Enter K: ");
    scanf("%d", &k);

    int n = strlen(s);
    for (i = 0; i < n; i++)
        count[(unsigned char)s[i]]++;
    for (c = 0; c < 256; c++)
        last[c] = -1;

    for (i = 0; i < n; i++) {
        int best = -1;
        for (c = 0; c < 256; c++) {
            if (count[c] == 0) continue;
            if (last[c] != -1 && i - last[c] < k) continue;
            if (best == -1 || count[c] > count[best]) best = c;
        }
        if (best == -1) {
            printf("Not possible, empty string\n");
            return 0;
        }
        result[i] = best;
        count[best]--;
        last[best] = i;
    }
    result[n] = '\0';
    printf("Rearranged string: %s\n", result);
    return 0;
}
