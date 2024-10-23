#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "sorting.c"

void generate_random_array(int *arr, int n) {
    for(int i = 0; i < n; i++)
        arr[i] = rand() % 1000000;
}

int is_sorted(int *arr, int n) {
    for(int i = 1; i < n; i += 1)
        if(arr[i] < arr[i-1]) return 0;
    return 1;
}

int main() {
    // Input sizes for benchmarking
    int sizes[] = {
        10, 20, 40, 60, 80, 100, 150, 200, 400, 600, 800,
        1000, 5000, 10000, 50000, 100000, 200000,
        500000, 1000000, 1500000, 2000000, 2500000
    };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    // Files to store timing results
    FILE *f_shell = fopen("shell_sort.dat", "w");
    FILE *f_merge_inplace = fopen("merge_sort_inplace.dat", "w");
    FILE *f_merge_shell = fopen("merge_sort_shell_sort.dat", "w");
    FILE *f_merge = fopen("merge_sort.dat", "w");
    FILE *f_radix = fopen("radix_sort.dat", "w");
    FILE *f_heap = fopen("heap_sort.dat", "w");
    FILE *f_insertion = fopen("insertion.dat", "w");
    FILE *f_quick = fopen("quick.dat", "w");
    FILE *f_merge_pp = fopen("merge_sort_pp.dat", "w");

    srand(clock());

    // Benchmarking loop
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i], iter;
        int *arr = malloc(n * sizeof(int));
        int *copy = malloc(n * sizeof(int));
        clock_t start, end;
        double time_taken;

        generate_random_array(arr, n);

        #define measure(fn, file, ...)\
            time_taken = 0;\
            for(iter = 0; time_taken < 10000000; iter++)\
                memcpy(copy, arr, n * sizeof(*arr)),\
                start = clock(),\
                fn(__VA_ARGS__),\
                end = clock(),\
                assert(is_sorted(copy, n)),\
                time_taken += 1e9 * (end - start) / CLOCKS_PER_SEC;\
            fprintf(file, "%d %f\n", n, time_taken / iter / n);

        measure(shell_sort, f_shell, copy, copy+n);
        measure(merge_sort_inplace, f_merge_inplace, copy, copy+n);
        measure(merge_sort_shell_sort, f_merge_shell, copy, copy+n);
        measure(merge_sort, f_merge, copy, copy+n);
        measure(radix_sort, f_radix, copy, copy+n);
        measure(heap_sort, f_heap, copy, copy+n);
        if(n < 1024) measure(insertion, f_insertion, copy, copy+n);
        measure(quick_sort, f_quick, copy, copy+n);
        measure(pp_merge_sort, f_merge_pp, copy, n);

        free(arr);
        free(copy);
    }

    fclose(f_shell);
    fclose(f_merge_inplace);
    fclose(f_merge_shell);
    fclose(f_merge);
    fclose(f_radix);
    fclose(f_heap);

    printf("Benchmarking complete. Data files generated.\n");

    return 0;
}
