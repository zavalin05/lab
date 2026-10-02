#include <stdio.h>
#include <omp.h>

int main() {
    printf("Vvedite chislo potokov \n");
        int N =0;
        scanf_s("%d", &N);
#pragma omp parallel num_threads(N)
    {
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();
        printf("Thread %d of %d: Hello World\n", tid, nthreads);
    }
return 0;
}

