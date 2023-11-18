#include <iostream>
#include <ctime>
#include <vector>
#include <immintrin.h>
#include <cblas.h>

#define M 1000
#define N 3

using namespace std;
using std::vector;

void AVX2_Add(float* res, const float* a, const float* b, size_t size);
void AVX2_Sub(float* res, const float* a, const float* b, size_t size);
void AVX2_Div(float* res, const float* a, const float b, size_t size);

class Matrix {
private:
    float *array;

public:
    Matrix() {
        array = new float[N * N];
    }
    ~Matrix() {
        delete array;
    }

    float * operator[](const size_t i) {
        return (array + i * N);
    }
    float * operator[](const size_t i) const {
        return (array + i * N);
    }

    void operator=(const Matrix &source) {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                (*this)[i][j] = source[i][j];
            }
        }
    }

    Matrix operator+(const Matrix &source) {
        Matrix temp;
        for (size_t i = 0; i < N; i++) {
            AVX2_Add(temp[i], (*this)[i], source[i], N);
        }
        return temp;
    }

    Matrix operator-(const Matrix &source) {
        Matrix temp;
        for (size_t i = 0; i < N; i++) {
            AVX2_Sub(temp[i], (*this)[i], source[i], N);
        }
        return temp;
    }

    Matrix operator*(const Matrix &source) {
        Matrix temp;
        for (size_t i = 0; i < N; i++) {
            for (size_t k = 0; k < N; k++) {
                for (size_t j = 0; j < N; j++) {
                    float s = source[k][j];
                    float t = (*this)[i][k];

                    temp[i][j] += t * s; 
                }
            }
        }
        return temp;
    }

    Matrix operator/(const float divisor) {
        Matrix temp;
        for (size_t i = 0; i < N; i++) {
            AVX2_Div(temp[i], (*this)[i], (float)divisor, N);
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

void AVX2_Add(float* res, const float* a, const float* b, size_t size) {
    size_t i = 0;
    if (size >= 8) {
        size_t aligned_size = size - size % 8;

        for (; i < aligned_size; i += 4) {
            __m128 va = _mm_loadu_ps(&a[i]);
            __m128 vb = _mm_loadu_ps(&b[i]);
            __m128 vres = _mm_add_ps(va, vb);
            _mm_storeu_ps(&res[i], vres);
        }
    }

    for (; i < size; ++i) {
        res[i] = a[i] + b[i];
    }
}

void AVX2_Sub(float* res, const float* a, const float* b, size_t size) {
    size_t i = 0;
    if (size >= 8) {
        size_t aligned_size = size - size % 8;

        for (; i < aligned_size; i += 4) {
            __m128 va = _mm_loadu_ps(&a[i]);
            __m128 vb = _mm_loadu_ps(&b[i]);
            __m128 vres = _mm_sub_ps(va, vb);
            _mm_storeu_ps(&res[i], vres);
        }
    }

    for (; i < size; ++i) {
        res[i] = a[i] - b[i];
    }
}

void AVX2_Div(float* res, const float* a, const float b, size_t size) {
    size_t i = 0;
    if (size >= 8) {
        size_t aligned_size = size - size % 8;

        for (; i < aligned_size; i += 4) {
            __m128 va = _mm_loadu_ps(&a[i]);
            __m128 vres = _mm_div_ps(va, _mm_set1_ps(b));
            _mm_storeu_ps(&res[i], vres);
        }
    }

    for (; i < size; ++i) {
        res[i] = a[i] / b;
    }
}

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

    Matrix ms = ma * ma;
    ma.coutMatrix();
    ms.coutMatrix();

    return 0;
}

// cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, A, N, B, N, 0.0, C, N);
// 0.00529352 0.00985796 -0.007962 
// -0.0121013 0.00514698 0.010341 
// 0.0101311 -0.00505653 0.00390048 

/*Matrix operator*(const Matrix &source) {
        Matrix temp;
        for (size_t i = 0; i < N; i++) {
            for (size_t k = 0; k < N; k++) {
                size_t j = 0;
                size_t aligned_size = N - N % 8;
                if (N >= 8) {
                    __m128 v_scalar =  _mm_set1_ps((*this)[i][k]);
                    for (; j < aligned_size; j += 4) {
                        __m128 v_source = _mm_loadu_ps(source[k]);
                        __m128 v_mul = _mm_mul_ps(v_source, v_scalar);
                        __m128 v_temp = _mm_loadu_ps(&temp[i][j]);
                        __m128 v_res = _mm_add_ps(v_temp, v_mul);
                        _mm_storeu_ps(&temp[i][j], v_res);
                    }
                }
                for (; j < N; j++) {
                    temp[i][j] += (*this)[i][k] * source[k][j];
                }
            }
        }
        return temp;
    }*/