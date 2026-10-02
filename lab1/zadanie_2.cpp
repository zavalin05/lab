#include <stdio.h>
#include <omp.h>

#define N 16000 // во всём коде N заменяется 16000

int main() {
    int a[N], b[N]; // 2 массива
    int i; // счётчик цикла
    printf("Vvedite chislo potokov \n");
    int npotok = 0;
    scanf_s("%d", &npotok);
    // Инициализация: a[i] = i
    for (i = 0; i < N; i++)
        a[i] = i;

    // Крайние элементы обрабатываем отдельно
    b[0] = a[0];
    b[N - 1] = a[N - 1];

    omp_set_num_threads(npotok);

    // --- static ---
#pragma omp parallel for shared(a, b) private(i) schedule(static)
    for (i = 1; i < N - 1; i++)
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;

    printf("static:  b[1]=%d  b[7999]=%d  b[15998]=%d\n",
        b[1], b[7999], b[15998]);

    // --- dynamic ---
#pragma omp parallel for shared(a, b) private(i) schedule(dynamic, 100)
    for (i = 1; i < N - 1; i++)
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;

    printf("dynamic: b[1]=%d  b[7999]=%d  b[15998]=%d\n",
        b[1], b[7999], b[15998]);

    // --- guided ---
#pragma omp parallel for shared(a, b) private(i) schedule(guided, 100)
    for (i = 1; i < N - 1; i++)
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;

    printf("guided:  b[1]=%d  b[7999]=%d  b[15998]=%d\n",
        b[1], b[7999], b[15998]);

    // --- runtime ---
#pragma omp parallel for shared(a, b) private(i) schedule(runtime)
    for (i = 1; i < N - 1; i++)
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;

    printf("runtime: b[1]=%d  b[7999]=%d  b[15998]=%d\n",
        b[1], b[7999], b[15998]);

    return 0;
}
