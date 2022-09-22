#include <stdio.h>
#include <omp.h>

#define THREAD_NUMBER 10

int main() {
    double start, end;

    double pi = 0.0;;
    int actual_threads;
    unsigned long numSteps = 175000000;
    double stepSize = 1.0/numSteps;

    start = omp_get_wtime();
    omp_set_num_threads(THREAD_NUMBER);

    #pragma omp parallel for reduction (+:pi)
        for (int i = 0; i < numSteps; i++) {
            pi += 4.0/(1 + (0.5 + i)*stepSize*(0.5 + i)*stepSize);
        }
    pi *= stepSize;

    end = omp_get_wtime();
    printf("runtime: %.10fs\n", end - start);
    printf("pi = %.15f\n", pi);

    return 0;
}