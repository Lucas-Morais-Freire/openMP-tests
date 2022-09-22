#include <stdio.h>
#include <omp.h>

#define THREAD_NUMBER 4

int main() {
    double start, end;

    double pi = 0.0;;
    int actual_threads;
    unsigned long numSteps = 175000000;
    double stepSize = 1.0/numSteps;

    start = omp_get_wtime();
    omp_set_num_threads(THREAD_NUMBER);

    #pragma omp parallel
    {
        double x;
        double temp = 0.0;
        int numThreads = omp_get_num_threads();
        int thrd = omp_get_thread_num();
        if (thrd == 0) actual_threads = numThreads;

        for (int i = thrd; i < numSteps; i += numThreads) {
            x = (0.5 + i)*stepSize;
            temp += 4.0/(1 + x*x);
        }
        #pragma omp atomic
            pi += temp;
    }
    pi *= stepSize;

    end = omp_get_wtime();

    printf("threads used: %d\n", actual_threads);
    printf("runtime: %.10fs\n", end - start);
    printf("pi = %.15f\n", pi);

    return 0;
}