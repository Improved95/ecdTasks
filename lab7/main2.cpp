#include <iostream>
#include <ctime>
#include <vector>

#define M 10
#define N 10

using namespace std;

class Matrix {
// private:

public:
    float **matrix;
    Matrix() {
        matrix = new float*[N];
        for (size_t i = 0; i < N; i++) {
            matrix[i] = new float[N];
        }
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                matrix[i][j] = 0;
            }
        } 
    }
    ~Matrix() {
        for (size_t i = 0; i < N; i++) {
            delete matrix[i];
        }
        delete[] matrix;
    }
    void operator=(const Matrix &a) {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                this->matrix[i][j] = a.matrix[i][j];
            }
        }
    }

    Matrix operator+(Matrix &a) {
        Matrix matrixCopy;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                this->matrix[i][j] += a.matrix[i][j];
            }
        }
        return matrixCopy;
    }

    float * operator[](const size_t i) {
        return matrix[i];
    }
};

int main() {
    Matrix mf;
    Matrix me;
    for (size_t i = 0; i < N; i++) {
        me.matrix[i][i] = 1;
    }

    Matrix mf2 = mf + me;

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            cout << mf2[i][j];
        }
        cout << endl;
    }
    
    return 0;
}

    // for (size_t i = 0; i < N; i++) {
    //     for (size_t j = 0; j < N; j++) {
    //         cout << ;
    //     }
    //     cout << endl;
    // }