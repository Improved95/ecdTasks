#include <iostream>
using namespace std;

// static size_t c = 0;
// static size_t c1 = 0;

void sattoloFill(size_t *a, size_t len) {
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

void forwardFill(size_t *arr, size_t len) {
    for (size_t i = 0; i < len - 1; i++) {
        arr[i] = i + 1;
    }
    arr[len - 1] = 0;
}

void backwardFill(size_t *arr, size_t len) {
    arr[0] = len - 1;
    for (size_t i = 1; i < len; i++) {
        arr[i] = i - 1;
    }
}

void bypass(size_t *arr, size_t len) {
    for (size_t i = 0, k = 0; i * 10 < len; i++) {
        k = arr[k];
        // c1 += 1;
    }
    // c += 1;
}

int main() {
    // size_t n_min = 2048;
    // size_t n_max = 4718592;
    // size_t step = 256;

    // for (size_t i = n_min; i < n_max; i += step) {
    //     size_t *arr = new size_t[i];
    //     if (!arr) { cout << "er" << endl; return 1; }

    //     forwardFill(arr, i);
    //     bypass(arr, i);

    //     backwardFill(arr, i);
    //     bypass(arr, i);

    //     sattoloFill(arr, i);
    //     bypass(arr, i);

    //     step += 256;
    //     delete[] arr;
    // }

    size_t *arr = new size_t[20];
    sattoloFill(arr, 20);
    for (size_t i = 0; i < 20; i++) {
        cout << arr[i] << " ";
    }

    // cout << c << endl;
    // cout << c1 << endl;
    return 0;
}