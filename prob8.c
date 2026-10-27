#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main() {
    int n, i;
    int start[1000], end[1000];

    printf("Enter number of meetings: ");
    scanf("%d", &n);
    printf("Enter start and end of each meeting:\n");
    for (i = 0; i < n; i++)
        scanf("%d %d", &start[i], &end[i]);

    qsort(start, n, sizeof(int), cmp);
    qsort(end, n, sizeof(int), cmp);

    int rooms = 0, maxRooms = 0, s = 0, e = 0;
    while (s < n) {
        if (start[s] < end[e]) {
            rooms++;
            s++;
            if (rooms > maxRooms) maxRooms = rooms;
        } else {
            rooms--;
            e++;
        }
    }
    printf("Minimum rooms required: %d\n", maxRooms);
    return 0;
}
