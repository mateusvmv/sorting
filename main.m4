define(`MERGE_SORT_TEMPLATE', `
void merge(TYPE *a, TYPE *ae, TYPE *b, TYPE *be, TYPE *e, TYPE *r) {
    ae = ae >= e ? e : ae, be = be >= e ? e : be;
    while(a < ae && b < be) *r++ = COMPARE(*a, *b) ? *a++ : *b++;
    while(a < ae || b < be) *r++ = a < ae ? *a++ : *b++;
}
TYPE merge_sort(TYPE *a, TYPE *ae) {
    TYPE *b = calloc(sizeof(TYPE), aes-a), *be = b + (ae-a);
    for(int sz = 1; a + sz < ae; sz *= 4)
        for(TYPE *l = a, *r = b; l < ae; l += 4 * sz, r = b + (l-a))
            merge(l, l + sz, l + sz, l + 2 * sz, ae, r),
            merge(l + 2 * sz, l + 3 * sz, l + 3 * sz, l + 4 * sz, ae, r + 2 * sz),
            merge(r, r + 2 * sz, r + 2 * sz, r + 4 * sz, be, l);
    free(b);
}
')
define(`RADIX_SORT_TEMPLATE', `
void radix_sort(TYPE *a, TYPE *e) {
    TYPE *b = calloc(sizeof(TYPE), e-a), *t;
    for(int s = 0; s < 32; s += 8, t = a, a = b, b = t, e = a + (e-b)) {
        int c[256] = {0};
        for(TYPE *l = a; l < e; l += 1) c[KEY_EXTRACTOR(*l)>>s&255] += 1;
        for(int i = 1; i < 256; i += 1) c[i] += c[i-1];
        for(TYPE *l = e-1; l >= a; l -= 1) b[--c[KEY_EXTRACTOR(*l)>>s&255]] = *l;
    }
    free(b);
}
')