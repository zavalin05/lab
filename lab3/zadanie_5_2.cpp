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
    double sx = 0.0, sy = 0.0, sz = 0.0;

#pragma omp parallel
    {
        /* Этап 1: чтение данных (его выполняет один поток) */
#pragma omp single
        {
            for (int i = 0; i < n; i++) {
                if (fscanf(f, "%lf %lf %lf", &x[i], &y[i], &z[i]) != 3) {
                    fprintf(stderr, "Read error at point %d\n", i);
                    exit(1);
                }
            }
            fclose(f);
        } /* неявный барьер: остальные потоки ждут окончания чтения */

        /* Этап 2: каждая секция выполняет свою функцию */
#pragma omp sections
        {
#pragma omp section
            { for (int i = 0; i < n; i++) sx += x[i]; }

#pragma omp section
            { for (int i = 0; i < n; i++) sy += y[i]; }

#pragma omp section
            { for (int i = 0; i < n; i++) sz += z[i]; }
        } /* неявный барьер: ждем, пока все три суммы готовы */

        /* Этап 3: вычисление центра и вывод */
#pragma omp single
        printf("Centr: (%f, %f, %f)\n", sx / n, sy / n, sz / n);
    }

    free(x); free(y); free(z);
    return 0;
}
