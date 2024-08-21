//
// Created by mtoia on 21/08/24.
//

#include "libft.h"

int partition(void *base, int low, int high, size_t size, int (*compar)(const void *, const void *)) {
    char *pivot = (char *)base + high * size;
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        char *ptr1 = (char *)base + j * size;
        if (compar(ptr1, pivot) < 0) {
            i++;
            char *ptr2 = (char *)base + i * size;
            for (size_t k = 0; k < size; k++) {
                char tmp = ptr1[k];
                ptr1[k] = ptr2[k];
                ptr2[k] = tmp;
            }
        }
    }
    char *ptr1 = (char *)base + (i + 1) * size;
    char *ptr2 = (char *)base + high * size;
    for (size_t k = 0; k < size; k++) {
        char tmp = ptr1[k];
        ptr1[k] = ptr2[k];
        ptr2[k] = tmp;
    }
    return i + 1;
}

void quicksort(void *base, int low, int high, size_t size, int (*compar)(const void *, const void *)) {
    if (low < high) {
        int pi = partition(base, low, high, size, compar);
        if (pi > 0)
            quicksort(base, low, pi - 1, size, compar);
        quicksort(base, pi + 1, high, size, compar);
    }
}

void ft_sort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
    if (nmemb > 0)
        quicksort(base, 0, nmemb - 1, size, compar);
}