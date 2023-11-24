#include <iostream>
#include <cstring>
#include <immintrin.h>
#include <cblas.h>

#define M 10
#define N 2048

using namespace std;

class Matrix {
private:
    float *array;

public:
    Matrix() {
        array = new float[N * N];
        std::memset(array, 0, N * N * sizeof(float));
    }
    ~Matrix() {
        delete array;
    }

    Matrix(const Matrix &source) {
        Matrix temp;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                temp[i][j] = source[i][j];
            }
        }
    }

    void operator=(const Matrix &source) {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                (*this)[i][j] = source[i][j];
            }
        }
    }

    float * operator[](const size_t i) {
        return (array + (i * N));
    }
    float * operator[](const size_t i) const {
        return (array + (i * N));
    }

    void operator+=(const Matrix &source) {
        cblas_saxpy(N * N, 1.0, source[0], 1, (*this)[0], 1);
    }

    void operator-=(const Matrix &source) {
        cblas_saxpy(N * N, -1.0, source[0], 1, (*this)[0], 1);
    }

    Matrix operator*(const Matrix &source) {
        Matrix temp;
        cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans, N, N, N, 1.0, source[0], N, (*this)[0], N, 0.0, temp[0], N);
        return temp;
    }

    void operator/=(const float divisor) {
        cblas_sscal(N * N, 1 / divisor, (*this)[0], 1);
    }

    float maxSumRows() {
        float maxSum = 0;
        for (size_t i = 0; i < N; i++) {
            float sum = cblas_sasum(N, (*this)[i], 1);
            if (sum > maxSum) {
                maxSum = sum;
            }
        }
        return maxSum;
    }

    float maxSumColumns() {
        float maxSum = 0;
        for (size_t i = 0; i < N; i++) {
            float sum = 0;
            for (size_t j = 0; j < N; j++) {
                sum += (*this)[j][i];
            }
            if (sum > maxSum) {
                maxSum = sum;
            }
        }
        return maxSum;
    }

    void coutMatrix() {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                cout << array[i * N + j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main() {
    srand(100);
    Matrix ma, mb, mr, mo;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            float a = rand() % 100;
            ma[i][j] = a;
            mb[j][i] = a;
            mr[i][j] = 0;
            mo[i][j] = 0;
        }
        mr[i][i] = 1;
        mo[i][i] = 1;
    }

    mb /= (ma.maxSumRows() * ma.maxSumColumns());
    mr -= (mb * ma);

    Matrix mrc;
    mrc = mr;
    for (size_t i = 1; i < M + 1; i++) {
        mo += mr;
        mr = mr * mrc;
    }
    mo = mo * mb;

    cout << "blas2" << endl;
    ma.coutMatrix();
    mo.coutMatrix();

    return 0;
}
