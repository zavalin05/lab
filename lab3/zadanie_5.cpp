#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE* f;
    errno_t err = fopen_s(&f, "points.txt", "r");
    if (err != 0) { printf("It was not possible to open points.txt\n"); return 1; }

    int n;
    if (fscanf_s(f, "%d", &n) != 1) { printf("Bad file\n"); return 1; }

    double* x = (double*)malloc(n * sizeof(double));
    double* y = (double*)malloc(n * sizeof(double));
    double* z = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        if (fscanf_s(f, "%lf %lf %lf", &x[i], &y[i], &z[i]) != 3) {
            printf("Error in  %d\n", i);
            return 1;
        }
    }
    fclose(f);

    double sx = 0.0, sy = 0.0, sz = 0.0;

#pragma omp parallel for reduction(+:sx, sy, sz)
    for (int i = 0; i < n; i++) {
        sx += x[i];
        sy += y[i];
        sz += z[i];
    }

    printf("Centr: (%f, %f, %f)\n", sx / n, sy / n, sz / n);

    free(x); free(y); free(z);
    return 0;
}

