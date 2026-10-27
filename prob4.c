#include <stdio.h>

long long heap[1000];
int size = 0;

void push(long long x) {
    int i = size++;
    heap[i] = x;
    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        int p = (i - 1) / 2;
        long long tmp = heap[p];
        heap[p] = heap[i];
        heap[i] = tmp;
        i = p;
    }
}

long long pop() {
    long long top = heap[0];
    heap[0] = heap[--size];
    int i = 0;
    while (1) {
        int l = 2 * i + 1, r = 2 * i + 2, small = i;
        if (l < size && heap[l] < heap[small]) small = l;
        if (r < size && heap[r] < heap[small]) small = r;
        if (small == i) break;
        long long tmp = heap[small];
        heap[small] = heap[i];
        heap[i] = tmp;
        i = small;
    }
    return top;
}

int main() {
    int n, i;
    long long x, cost = 0;

    printf("Enter number of sticks: ");
    scanf("%d", &n);
    printf("Enter lengths: ");
    for (i = 0; i < n; i++) {
        scanf("%lld", &x);
        push(x);
    }

    while (size > 1) {
        long long a = pop();
        long long b = pop();
        cost += a + b;
        push(a + b);
    }
    printf("Minimum total cost: %lld\n", cost);
    return 0;
}
