#include <stdio.h>

int heap[1000];
int size = 0;

void push(int x) {
    int i = size++;
    heap[i] = x;
    while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
        int p = (i - 1) / 2;
        int tmp = heap[p];
        heap[p] = heap[i];
        heap[i] = tmp;
        i = p;
    }
}

int pop() {
    int top = heap[0];
    heap[0] = heap[--size];
    int i = 0;
    while (1) {
        int l = 2 * i + 1, r = 2 * i + 2, big = i;
        if (l < size && heap[l] > heap[big]) big = l;
        if (r < size && heap[r] > heap[big]) big = r;
        if (big == i) break;
        int tmp = heap[big];
        heap[big] = heap[i];
        heap[i] = tmp;
        i = big;
    }
    return top;
}

int main() {
    int D, F, n, i, j;
    int d[1000], f[1000];

    printf("Enter target D and starting fuel F: ");
    scanf("%d %d", &D, &F);
    printf("Enter number of stations: ");
    scanf("%d", &n);
    printf("Enter distance and fuel for each station:\n");
    for (i = 0; i < n; i++)
        scanf("%d %d", &d[i], &f[i]);

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (d[j] > d[j + 1]) {
                int t = d[j]; d[j] = d[j + 1]; d[j + 1] = t;
                t = f[j]; f[j] = f[j + 1]; f[j + 1] = t;
            }
        }
    }

    int reach = F, stops = 0, idx = 0;
    while (reach < D) {
        while (idx < n && d[idx] <= reach)
            push(f[idx++]);
        if (size == 0) {
            printf("Cannot reach the target: -1\n");
            return 0;
        }
        reach += pop();
        stops++;
    }
    printf("Minimum refuelling stops: %d\n", stops);
    return 0;
}
