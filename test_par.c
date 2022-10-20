#include <stdio.h>
#include <omp.h>

#define THREAD_NUMBER 4

int main() {
    double start, end;

    double pi = 0.0;;
    int actual_threads;
    unsigned long numSteps = 1000000000;
    double stepSize = 1.0/numSteps;

    start = omp_get_wtime();
    omp_set_num_threads(THREAD_NUMBER);

    #pragma omp parallel
    {
        double sum = 0.0;
        double x;
        int numThreads = omp_get_num_threads();
        int thread = omp_get_thread_num();
        if (thread == 0) actual_threads = numThreads;

        for (int i = thread; i < numSteps; i += numThreads) {
            x = (0.5 + i)*stepSize;
            sum += 4.0/(1 + x*x);
        }

        #pragma omp critical
        {
            pi += sum;
        }
    }
    pi *= stepSize;

    end = omp_get_wtime();
    printf("threads used: %d\n", actual_threads);
    printf("runtime: %.10fs\n", end - start);
    printf("pi = %.15f\n", pi);

    return 0;
}