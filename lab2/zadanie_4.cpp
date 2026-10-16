#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    // Нужно ровно 4 аргумента: имя программы + rowsA + n + colsB
    if (argc != 4) {
        printf("Ispolzovanie: %s <rowsA> <n> <colsB>\n", argv[0]);
        printf("Primer:      %s 1000 500 1000\n", argv[0]);
        return 1;
    }

    int rowsA = atoi(argv[1]);
    int n = atoi(argv[2]);
    int colsB = atoi(argv[3]);

    if (rowsA <= 0 || n <= 0 || colsB <= 0) {
        printf("Razmery matric dolzhny byt' polozhitel'nymi\n");
        return 1;
    }

    printf("Vvedite chislo potokov: ");
    int npotok = 0;
    if (scanf_s("%d", &npotok) != 1 || npotok <= 0) {
        printf("Oshibka: nuzhno vvesti polozhitel'noe chislo\n");
        return 1;
    }

    // Выделение памяти под матрицы A(rowsA x n), B(n x colsB), C(rowsA x colsB)
    double* A = (double*)malloc((size_t)rowsA * n * sizeof(double));
    double* B = (double*)malloc((size_t)n * colsB * sizeof(double));
    double* C = (double*)malloc((size_t)rowsA * colsB * sizeof(double));

    if (!A || !B || !C) {
        printf("Oshibka vydeleniya pamyati\n");
        return 1;
    }

    // Инициализация
    for (int i = 0; i < rowsA * n; i++) A[i] = 1.0;
    for (int i = 0; i < n * colsB; i++) B[i] = 2.0;

    // ---------------------------------------------------------
    // 1. Последовательное умножение матриц
    // ---------------------------------------------------------
    for (int i = 0; i < rowsA * colsB; i++) C[i] = 0.0;  // сброс C

    double t_start_seq = omp_get_wtime();

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++) {
                sum += A[i * n + k] * B[k * colsB + j]; // A[i][k] B[k][j]
            }
            C[i * colsB + j] = sum; // C[i][j]
        }
    }

    double t_end_seq = omp_get_wtime();
    double time_seq = t_end_seq - t_start_seq;

    // Сохраним C[0][0] из последовательной версии для проверки
    double c00_seq = C[0];

    // ---------------------------------------------------------
    // 2. Параллельное умножение матриц
    // ---------------------------------------------------------
    for (int i = 0; i < rowsA * colsB; i++) C[i] = 0.0;  // снова сброс C
    omp_set_num_threads(npotok);

    double t_start_par = omp_get_wtime();

#pragma omp parallel for shared(A, B, C) schedule(static)
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++) {
                sum += A[i * n + k] * B[k * colsB + j];
            }
            C[i * colsB + j] = sum;
        }
    }

    double t_end_par = omp_get_wtime();
    double time_par = t_end_par - t_start_par;
    double c00_par = C[0];

    // Вывод результатов
    printf("\nrowsA=%d  n=%d  colsB=%d  potok=%d\n", rowsA, n, colsB, npotok);
    printf("Time sequential: %.6f sec\n", time_seq);
    printf("Time parallel:   %.6f sec\n", time_par);
    printf("Speedup:         %.2fx\n", time_seq / time_par);
    printf("C[0][0] seq:     %.2f\n", c00_seq);
    printf("C[0][0] par:     %.2f\n", c00_par);

    free(A);
    free(B);
    free(C);
    return 0;
}

