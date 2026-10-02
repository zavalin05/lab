#include <stdio.h>
#include <omp.h>


int main() {
    printf("Vvedite chislo potokov \n");
    int npotok = 0;
    scanf_s("%d", &npotok);
    int ids[8];
    omp_set_num_threads(npotok);

#pragma omp parallel shared(ids)
    {
        int tid = omp_get_thread_num();
        ids[tid] = tid;

#pragma omp barrier

#pragma omp single
        {
            for (int i = npotok - 1; i >= 0; i--)
                printf("Potok %d: Hello World\n", ids[i]);
        }
    }
    return 0;
}
