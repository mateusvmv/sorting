#include <stdlib.h>
#include <assert.h>
#include <string.h>

#ifndef T
#define T int
#endif

#define swap(a, b) (t = a, a = b, b = t)

void shell_sort(T *a, T *e) {
    for(int g = (e-a); g > 0; g = g > 1 ? g/8+1 : 0)
        for(T *i = a+g, *j, t; i < e; *j = t, i += 1)
            for(j = i, t = *j; (j >= a+g) && *(j-g) > t; j -= g)
                *j = *(j-g);
}

void insertion(T *a, T *e) {
    for(T *i = a+1, *j, t; i < e; *j = t, i += 1)
        for(t = *i, j = i; j > a && *(j-1) > t; j -= 1)
            *j = *(j-1);
}

void merge_inplace(T *a, T *ae, T *b, T *be) {
    T v[8192], *c = v, *ce, *l = b, *r = b;
    if(ae-a < 8192) {
        memmove(c, a, (ae-a) * sizeof(T)), ce = c+(ae-a);
        while(c < ce) *a++ = b < be && *b < *c ? *b++ : *c++;
    } else if(be-b < 8192) {
        memmove(c, b, (be-b) * sizeof(T)), ce = c+(be-b);
        while(c < ce) *--be = a >= ae || *(ce-1) >= *(ae-1) ? *--ce : *--ae;
    } else {
        while(l > a && r < be && *(l-1) > *r) l -= 1, r += 1;
        for(T *p = l, *q = b, t; q < r;) t = *p, *p++ = *q, *q++ = t;
        merge_inplace(a, l, l, b), merge_inplace(b, r, r, be);
    }
}
void merge_sort_inplace(T *a, T *e) {
    for(int sz = 1; a+sz < e; sz *= 2)
        for(T *l = a, *r = l+2*sz; l+sz < e; l = r, r += 2*sz)
            merge_inplace(l, l+sz, l+sz, r<e?r:e);
}

void merge_sort_shell_sort(T *a, T *ae) {
    for(int sz = 1, g; a+sz < ae; sz *= 2)
        for(T *l = a, *r = l+2*sz; l+sz < ae; l = r, r += 2*sz)
            for(r = r<ae?r:ae, g = sz; g > 0; g = g > 1 ? (g+1)/2 : 0)
                for(T *i = l, *j = l+g, t; j < r; i += 1, j += 1)
                    if(*i > *j) t = *i, *i = *j, *j = t;
}

void merge(T *a, T *ae, T *b, T *be, T *e, T *r) {
    ae = ae >= e ? e : ae, be = be >= e ? e : be;
    while(a < ae && b < be) *r++ = *b < *a ? *b++ : *a++;
    while(a < ae || b < be) *r++ =  b < be ? *b++ : *a++;
}
void merge_sort(T *a, T *ae) {
    T *b = calloc(ae-a, sizeof(T)), *be = b + (ae-a);
    for(int sz = 1; a+sz < ae; sz *= 4)
        for(T *l = a, *r = b; l < ae; l += 4*sz, r = b+(l-a))
            merge(l, l+sz, l+sz, l+2*sz, ae, r),
            merge(l+2*sz, l+3*sz, l+3*sz, l+4*sz, ae, r+2*sz),
            merge(r, r+2*sz, r+2*sz, r+4*sz, be, l);
    free(b);
}

void radix_sort(T *a, T *e) {
    if(e-a < 128) return insertion(a, e);
    T *b = calloc(e-a, sizeof(T)), *t;
    for(int s = 0; s < 32; s += 8, t = a, a = b, b = t, e = a+(e-b)) {
        int c[256] = {0};
        for(T *l = a; l < e; l += 1) c[(*l^(1<<31))>>s&255] += 1;
        for(int i = 1; i < 256; i += 1) c[i] += c[i-1];
        for(T *l = e-1; l >= a; l -= 1) b[--c[(*l^(1<<31))>>s&255]] = *l;
    }
    free(b);
}

void heapify(T *a, int n, int i) {
    int l = i*2+1, r = i*2+2, max = i;
    T t;
    if(l<n && a[l] > a[max]) max = l;
    if(r<n && a[r] > a[max]) max = r;
    if(max != i) t = a[i], a[i] = a[max], a[max] = t, heapify(a, n, max);
}
void heap_sort(T *a, T *e) {
    for(int i = (e-a)/2-1; i >= 0; i -= 1) heapify(a, e-a, i);
    for(T *i = e-1, t; i > a; i -= 1)
        t = a[0], a[0] = *i, *i =  t, heapify(a, i-a, 0);
}

void quick_sort(T *a, T *e) {
    for(T *i, *j, *m, t; a+1024 < e; swap(*a, *(i-1)), quick_sort(a, i-1), a = i)
        for(m = &a[rand() % (e-a)], swap(*a, *m), i = j = a + 1; j < e; j += 1)
            if(*j <= *a) t = *i, *i++ = *j, *j = t;
    shell_sort(a, e);
}

void _pp_merge_sort(T* v, T* w, size_t n) {
    if(n < 64) return insertion(v, v+n);
    size_t m = (n+1)/2; n /= 2;
    _pp_merge_sort(v, w, m/2);
    _pp_merge_sort(v+m/2, w+m/2, (m+1)/2);
    _pp_merge_sort(v+m, w+m, n/2);
    _pp_merge_sort(v+m+n/2, w+m+n/2, (n+1)/2);
    merge(v, v+(m/2), v+(m/2), v+m, v+m, w);
    merge(v+m, v+m+(n/2), v+m+(n/2), v+m+n, v+m+n, w+m);
    merge(w, w+m, w+m, w+m+n, w+m+n, v);
}
void pp_merge_sort(T* a, size_t n) {
    T *b = malloc(n * sizeof(T));
    _pp_merge_sort(a, b, n);
    free(b);
}

#undef T
