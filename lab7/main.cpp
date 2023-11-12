#include <iostream>
#include <ctime>

using namespace std;

void matrixSum () {

}

int main() {
    const size_t n = 10;
    const size_t m = 10;
    srand(100);
    
    float **matrix = new float*[n];
    for (size_t i = 0; i < n; i++) {
        matrix[i] = new float[n];
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            matrix[i][j] = rand() / (float)rand();
        }
    }

    

    for (size_t i = 0; i < n; i++) {
        delete matrix[i];
    }
    delete[] matrix;
    return 0;
}
