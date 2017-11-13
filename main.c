#include <stdio.h>
#ifdef _OPENMP
# include <omp.h>
#endif

/**
 * The following program contains a loop that has a clear loop-carry
 * dependence. If possible, the second program in the loop will be
 * parallel and remove the loop-carry dependence so that the loops
 * may be parallelized.
 *
 * @return exit code - 0 for a successful termination
 */
int main()
{
    // Shared variables
    int a[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int b[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int n = 8;

    // Adds the iteration number to element indexed by
    // the iteration number - 1 in the array.
    // Then assigns that value to the location indexed
    // by the iteration number. Runs n-1 times.
    printf("Serial:\n");
    a[0] = 0;
    for (int i = 1; i < n; i++) {
        a[i] = a[i-1] + i;
        printf("The value of a on iteration %i: %i\n", i, a[i]);
    }

    // This parallelizable loop yields the same result when starting on iteration 1
    printf("\nParallel:\n");
    b[0] = 0;
# pragma omp parallel for num_threads(n)
    for (int i = 1; i < n; i++) {
        b[i] = i * (i+1) / 2;
        // remember that we can't expect the output to be serial
        // since there is no guarantee that the threads will finish in order.
        printf("The value of a on iteration %i: %i\n", i, b[i]);
    }

    return 0;
}