#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void matching_3way(int *v1, int *v2, int *v3, size_t sv1, size_t sv2, size_t sv3) {
    int i = 0, j = 0, k = 0;
    while(i < sv1 && j < sv2 && k < sv3) {
        if(v1[i] < v2[j] && v1[i] < v3[k]) i++;
        else if(v2[j] < v1[i] && v2[j] < v3[k]) j++;
        else if(v3[k] < v1[i] && v3[k] < v2[j]) k++;

        if(v1[i] == v2[j] && v2[j] == v3[k]) {
            printf("%d ", v1[i]);
            i++, j++, k++;
        }
    }

    putchar('\n');
}

int main() {
    int l1[] = {10, 25, 30, 45, 60};
    int l2[] = {10, 25, 30, 40, 50, 70};
    int l3[] = { 1,  8, 10, 18, 25};

    matching_3way(&l1[0], &l2[0], &l3[0], 5, 6, 5);

    return 0;
}