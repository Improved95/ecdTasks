#include <iostream>
#include <time.h>
#include <limits.h>
#include <fstream>
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
        swap(a[i], a[j]);
    }
}    

size_t bypass(int *arr, size_t step, size_t len, ostream &fileOut) {
    size_t k = 0, sk = 0, bypassNumber = 1;
    volatile size_t t1 = 0, t2 = 0, startTime, endTime;
    for (size_t j = 0; j < bypassNumber; j++) {
        for (size_t i = 0; i < len; i++) {
            startTime = __builtin_ia32_rdtsc();
            sk = arr[k];
            endTime = __builtin_ia32_rdtsc();
            t1 += endTime - startTime;

            startTime = __builtin_ia32_rdtsc();
            k = arr[sk + step];
            endTime = __builtin_ia32_rdtsc();
            t2 += endTime - startTime;
        }
    }
    cerr << k;
    cerr << sk;

    fileOut << step << " " << t1 / (len * bypassNumber) << " " 
            << t2 / (len * bypassNumber) << endl;

    // return time / (len * nb);
    return 0;
}

int main() {
    ofstream fileOut;
    fileOut.open("time.txt");

    size_t len = 64 * 1024 * 1024 / sizeof(int);
    int *arr = new int[len * sizeof(int)];

    sattoloFill(arr, len - 128);

    for (size_t i = 0; i < 20; i++) {
        cerr << i << " " << bypass(arr, i, len, fileOut) << endl;
    }

}