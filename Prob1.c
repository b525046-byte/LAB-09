#include <stdio.h>

int main() {
    int n, i;
    double W;
    double v[100], w[100], lam[100];
    int used[100] = {0};

    printf("Enter n and capacity W: ");
    scanf("%d %lf", &n, &W);
    printf("Enter v, w, lambda for each item:\n");
    for (i = 0; i < n; i++)
        scanf("%lf %lf %lf", &v[i], &w[i], &lam[i]);

    double t = 0, total = 0, cap = W;
    printf("\nConsumption order:\n");
    while (cap > 0) {
        int best = -1;
        double bestDen = 0;
        for (i = 0; i < n; i++) {
            if (used[i]) continue;
            double den = v[i] / w[i] - lam[i] * t;
            if (den > bestDen) {
                bestDen = den;
                best = i;
            }
        }
        if (best == -1) break;

        double take = w[best] < cap ? w[best] : cap;
        double gain = take * bestDen;
        printf("Item %d: take %.2f of %.2f at t=%.2f, density %.2f, value %.2f\n",
               best + 1, take, w[best], t, bestDen, gain);
        total += gain;
        t += take;
        cap -= take;
        used[best] = 1;
    }
    printf("Total value: %.2f\n", total);
    return 0;
}
