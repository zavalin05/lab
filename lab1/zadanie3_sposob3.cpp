#include <stdio.h>
#include <omp.h>

int main() {
    printf("Vvedite chislo potokov \n");
    int npotok = 0;
    scanf_s("%d", &npotok);

    omp_set_num_threads(npotok);

#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();

        for (int step = nthreads - 1; step >= 0; step--) {
            if (tid == step)
                printf("Potok %d: Hello World\n", tid);
#pragma omp barrier
        }
    }
    return 0;
}
