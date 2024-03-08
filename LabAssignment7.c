#include <stdio.h>

int main() {

    int array1[] = { 97, 16, 45, 63, 13, 22, 7, 58, 72 };
    int array2[] = { 90, 80, 70, 60, 50, 40, 30, 20, 10 };
    int n = sizeof(array1) / sizeof(array1[0]);
    int p = sizeof(array2) / sizeof(array2[0]);
    int tmp, swap;

    
    for (int i = 0; i < n - 1; i++) {
        swap = 0;
        for (int j = 0; j < n - 1; j++) {
            if (array1[j] > array1[j + 1]) {
                tmp = array1[j];
                array1[j] = array1[j + 1];
                array1[j + 1] = tmp;
            }
            swap++;
        }
    }
    printf("Total number of swaps: %d\n", swap);

    for (int i = 0; i < p - 1; i++) {
        swap = 0;
        for (int j = 0; j < p - 1; j++) {
            if (array2[j] > array2[j + 1]) {
                tmp = array2[j];
                array2[j] = array2[j + 1];
                array2[j + 1] = tmp;
            }
            swap++;
        }
    }
    printf("Total number of swaps: %d\n", swap);

    return 0;
}