#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    int id; // Unique identifier for stability test
} Element;

#define T Element

void merge(T *a, T *ae, T *b, T *be, T *e, T *r) {
    ae = ae >= e ? e : ae, be = be >= e ? e : be;
    while(a < ae && b < be) *r++ = b->key < a->key ? *b++ : *a++;
    while(a < ae || b < be) *r++ =  b < be ? *b++ : *a++;
}
void _pp_merge_sort(T* v, T* w, size_t n) {
    if(n <= 1) return;
    size_t m = (n+1)/2; n /= 2;
    _pp_merge_sort(v, w, m/2);
    _pp_merge_sort(v+m/2, w+m/2, (m+1)/2);
    _pp_merge_sort(v+m, w+m, n/2);
    _pp_merge_sort(v+m+n/2, w+m+n/2, (n+1)/2);
    merge(v, v+(m/2), v+(m/2), v+m, v+m, w);
    merge(v+m, v+m+(n/2), v+m+(n/2), v+m+n, v+m+n, w+m);
    merge(w, w+m, w+m, w+m+n, w+m+n, v);
}
void pp_merge_sort(T* a, T *e) {
    T *b = malloc((e-a) * sizeof(T));
    _pp_merge_sort(a, b, e-a);
    free(b);
}

int compare(const void *a, const void *b) {
    return ((Element *)a)->key - ((Element *)b)->key;
}

void test_stability(void (*sort_func)(Element *, Element *), Element *arr, size_t size) {
    Element *original = malloc(size * sizeof(Element));
    memcpy(original, arr, size * sizeof(Element));

    sort_func(arr, arr + size);

    int stable = 1;
    for(size_t i = 1; i < size; i++) {
        if (arr[i].key == arr[i - 1].key && arr[i].id < arr[i - 1].id) {
            stable = 0;
            break;
        }
    }

    printf("Sort function %p is %s\n", (void *)sort_func, stable ? "stable" : "unstable");
    free(original);
}

void run_tests() {
    Element arr[1024];
    for(int i = 0; i < 1024; i += 1)
        arr[i].key = rand() % 20, arr[i].id = i;
    size_t size = sizeof(arr) / sizeof(arr[0]);

    test_stability(pp_merge_sort, arr, size);
}

int main() {
    srand(clock());
    run_tests();
    return 0;
}
