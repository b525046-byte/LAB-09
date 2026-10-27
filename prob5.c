#include <stdio.h>

int main() {
    int n, i, total = 0;
    int rating[1000], candy[1000];

    printf("Enter number of children: ");
    scanf("%d", &n);
    printf("Enter ratings: ");
    for (i = 0; i < n; i++)
        scanf("%d", &rating[i]);

    for (i = 0; i < n; i++)
        candy[i] = 1;

    for (i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1])
            candy[i] = candy[i - 1] + 1;
    }

    for (i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1] && candy[i] <= candy[i + 1])
            candy[i] = candy[i + 1] + 1;
    }

    printf("Candies: ");
    for (i = 0; i < n; i++) {
        printf("%d ", candy[i]);
        total += candy[i];
    }
    printf("\nMinimum total candies: %d\n", total);
    return 0;
}
