#include <iostream>
#include <time.h>
#include <limits.h>
#include <fstream>
#include <cstring>
using namespace std;

void sattoloFill(int *a, size_t len) {
    int i, j;
    srand(unsigned(time(0)));
    for (size_t k = 0; k < len; k++) {
        a[k] = k;
    }
    for(i = len - 1; i > 0; i--) {
        do {
            j = rand() % i;
        } while(j >= i);
        std::swap(a[i], a[j]);
    }
}

void trashCache(int *arr, size_t len) {
    int k = 0;
    for (size_t i = 0; i < len; i++) {
        k = arr[k];
    }
    cerr << k;
}

int main() {
    ofstream fileOut;
    fileOut.open("time.txt");

    size_t trashArrSize = 17 * 1024 * 1024 / sizeof(int);
    int *trashArr = new int[trashArrSize];
    sattoloFill(trashArr, trashArrSize);

    size_t arrSize =  / sizeof(int);

}