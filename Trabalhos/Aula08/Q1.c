#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void merging_2way(int *v1, int *v2, size_t sv1, size_t sv2) {

    int i = 0, j = 0, k = 0;
    for(; i < sv1 && j < sv2; k++) {
        if(v1[i] < v2[j]) printf("%d ", v1[i++]);
        else if(v1[i] > v2[j]) printf("%d ", v2[j++]);
        else {
            printf("%d ", v1[i++]);
            j++;
        }
    }

    for(; i < sv1; k++) {
        printf("%d ", v1[i++]);
    }

    for(; j < sv2; k++) {
        printf("%d ", v2[j++]);
    }
}


int main() {
    int l1[] = {10, 25, 30, 45, 60};
    int l2[] = { 5, 20, 30, 40, 50, 70};

    merging_2way(&l1[0], &l2[0], 5, 6);

    putchar('\n');

    return 0;
}