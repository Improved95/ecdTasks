#include <iostream>
#include <ctime>
#include <string>

void swap(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

using namespace std;
int main(int argc, char* argv[]) {
    srand(20);
  
    size_t n = stoull(argv[1]);
    int *arr = new int[n];

    for (size_t i = 0; i < n; i++) {
        arr[i] = rand();
    }

    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    for (size_t i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}