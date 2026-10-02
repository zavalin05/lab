# Задача 1. Параллельная область и идентификация потоков

Программа считывает с клавиатуры число потоков `N` и создаёт параллельную область с `N` потоками. Каждый поток печатает свой идентификатор, общее число потоков и строку «Hello World».

## Требования

- Компилятор C (gcc/clang) с поддержкой OpenMP

## Код (`task1.c`)

```c
#include <stdio.h>
#include <omp.h>

int main() {
    printf("Vvedite chislo potokov \n");
        int N = 0;
        scanf_s("%d", &N);
#pragma omp parallel num_threads(N)
    {
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();
        printf("Thread %d of %d: Hello World\n", tid, nthreads);
    }
    return 0;
}

