#include <iostream>
#include <cstring>
#include <cblas.h>

#define M 1000
#define N 8

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

    Matrix operator+(const Matrix &source) {
        Matrix temp;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                temp[i][j] = (*this)[i][j] + source[i][j];
            }
        }
        return temp;
    }

    Matrix operator-(const Matrix &source) {
        Matrix temp;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                temp[i][j] = (*this)[i][j] - source[i][j];
            }
        }
        return temp;
    }

    Matrix operator*(const Matrix &source) {
        Matrix temp;
        cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans, N, N, N, 1.0, source[0], N, (*this)[0], N, 0.0, temp[0], N);
        return temp;
    }

    Matrix operator/(const float source) {
        Matrix temp;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                temp[i][j] = (*this)[i][j] / (float) source;
            }
        }
        return temp;
    }

    float maxSumRows() {
        float maxSum = 0;
        for (size_t i = 0; i < N; i++) {
            float sum = 0;
            for (size_t j = 0; j < N; j++) {
                sum += (*this)[i][j];
            }
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
    Matrix ma, mt, me;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            float a = rand() % 100;
            ma[i][j] = a;
            mt[j][i] = a;
            me[i][j] = 0;
        }
        me[i][i] = 1;
    }

    Matrix mb = mt / (ma.maxSumRows() * ma.maxSumColumns());
    Matrix mr = me - (mb * ma);

    Matrix mo, mrc;
    mrc = mr;

    mo = me;
    for (size_t i = 1; i < M + 1; i++) {
        mo = mo + mr;
        mr = mr * mrc;
    }
    mo = mo * mb;

    cout << "Blas" << endl;
    ma.coutMatrix();
    mo.coutMatrix();

    return 0;
}
