#include <iostream>
#include <ctime>
#include <vector>
#include <immintrin.h>

#define M 1000
#define N 3

using namespace std;
using std::vector;

class Matrix {
private:
    float **array;

public:
    Matrix() {
        array = new float*[N];
        #pragma omp parallel for
        for (size_t i = 0; i < N; i++) {
            array[i] = new float[N];
        }
        #pragma omp parallel for
        for (size_t i = 0; i < N; i++) {
            #pragma omp parallel for
            for (size_t j = 0; j < N; j++) {
                array[i][j] = 0;
            }
        }
    }
    ~Matrix() {
        #pragma omp parallel for
        for (size_t i = 0; i < N; i++) {
            delete array[i];
        }
        delete[] array;
    }

    float * operator[](const size_t i) {
        return array[i];
    }
    float * operator[](const size_t i) const {
        return array[i];
    }

    void operator=(const Matrix &source) {
        #pragma omp parallel for
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                (*this)[i][j] = source[i][j];
            }
        }
    }

    Matrix operator+(const Matrix &source) {
        Matrix temp;
        #pragma omp parallel for
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                temp[i][j] = (*this)[i][j] + source[i][j];
            }
        }
        return temp;
    }

    Matrix operator-(const Matrix &source) {
        Matrix temp;
        #pragma omp parallel for
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                temp[i][j] = (*this)[i][j] - source[i][j];
            }
        }
        return temp;
    }

    Matrix operator*(const Matrix &source) {
        Matrix temp;
        vector<float> resV;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                float res = 0;
                for (size_t k = 0; k < N; k++) {
                    res += (*this)[i][k] * source[k][j];
                }
                temp[i][j] = res;
            }
        }
        return temp;
    }

    Matrix operator/(const float source) {
        Matrix temp;
        #pragma omp parallel for
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                temp[i][j] = (*this)[i][j] / (float)source;
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
                cout << array[i][j] << " ";
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

    // ma.coutMatrix();
    // mo.coutMatrix();

    if (__builtin_cpu_supports("avx2")) {
        cout << "work" << endl;
    }

    return 0;
}
