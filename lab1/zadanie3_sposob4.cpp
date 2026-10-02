#include <stdio.h>
#include <omp.h>

int main() {
    printf("Vvedite chislo potokov \n");
    int npotok = 0;
    scanf_s("%d", &npotok);
    int next = npotok - 1;
    omp_lock_t lock;
    omp_init_lock(&lock);

    omp_set_num_threads(npotok);
#pragma omp parallel shared(next, lock)
    {
        int tid = omp_get_thread_num();
        int done = 0;

        while (!done) {
            omp_set_lock(&lock);
            if (next == tid) {
                printf("Potok %d: Hello World\n", tid);
                next--;
                done = 1;
            }
            omp_unset_lock(&lock);
        }
    }
    omp_destroy_lock(&lock);
    return 0;
}
