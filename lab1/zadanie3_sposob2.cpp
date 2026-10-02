#include <stdio.h>
#include <omp.h>

int main() {
    printf("Vvedite chislo potokov \n");
    int npotok = 0;
    scanf_s("%d", &npotok);

    int next = npotok - 1;

    omp_set_num_threads(npotok);
#pragma omp parallel shared(next)
    {
        int tid = omp_get_thread_num();
        int done = 0;

        while (!done) {
#pragma omp critical
            {
                if (next == tid) {
                    printf("Potok %d: Hello World\n", tid);
                    next--;
                    done = 1;
                }
            }
        }
    }
    return 0;
}
