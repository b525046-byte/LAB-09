#include <stdio.h>
#include <limits.h>

long long heap[10000];
int size = 0;

void push(long long x) {
    int i = size++;
    heap[i] = x;
    while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
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
        int l = 2 * i + 1, r = 2 * i + 2, big = i;
        if (l < size && heap[l] > heap[big]) big = l;
        if (r < size && heap[r] > heap[big]) big = r;
        if (big == i) break;
        long long tmp = heap[big];
        heap[big] = heap[i];
        heap[i] = tmp;
        i = big;
    }
    return top;
}

int main() {
    int n, i;
    long long x, mn = LLONG_MAX, ans = LLONG_MAX;

    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter array: ");
    for (i = 0; i < n; i++) {
        scanf("%lld", &x);
        if (x % 2 == 1) x = x * 2;
        push(x);
        if (x < mn) mn = x;
    }

    while (1) {
        long long top = pop();
        if (top - mn < ans) ans = top - mn;
        if (top % 2 == 1) break;
        top = top / 2;
        if (top < mn) mn = top;
        push(top);
    }
    printf("Minimum deviation: %lld\n", ans);
    return 0;
}
