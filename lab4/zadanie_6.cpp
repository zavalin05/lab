#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE* f;
    errno_t err = fopen_s(&f, "points.txt", "r");
    if (err != 0) { perror("points.txt"); return 1; }

    int n;
    if (fscanf(f, "%d", &n) != 1) { fprintf(stderr, "Bad file\n"); return 1; }

    double* x = (double*)malloc(n * sizeof(double));
    double* y = (double*)malloc(n * sizeof(double));
    double* z = (double*)malloc(n * sizeof(double));
    double gsum = 0.0; /* глобальная сумма */

    for (int i = 0; i < n; i++) {
        if (fscanf(f, "%lf %lf %lf", &x[i], &y[i], &z[i]) != 3) {
            fprintf(stderr, "Read error at point %d\n", i);
            return 1;
        }
    }
    fclose(f);

#pragma omp parallel
    {
#pragma omp sections
        {
#pragma omp section
            {
                double s = 0.0;
                for (int i = 0; i < n; i++) s += x[i];
#pragma omp critical
                gsum += s; /* запись в общую переменную — только под блокировкой */
            }

#pragma omp section
            {
                double s = 0.0;
                for (int i = 0; i < n; i++) s += y[i];
#pragma omp critical
                gsum += s;
            }

#pragma omp section
            {
                double s = 0.0;
                for (int i = 0; i < n; i++) s += z[i];
#pragma omp critical
                gsum += s;
            }
        } /* неявный барьер: ждем, пока все три вклада добавлены */

#pragma omp single
        printf("Result: %f\n", gsum / (3.0 * n));
    }

    free(x); free(y); free(z);
    return 0;
}
