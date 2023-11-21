#include <iostream>
#include <cstring>
#include <immintrin.h>

#define M 1000
#define N 4

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
        for (size_t i = 0; i < N; i++) {
            size_t j = 0;
            if (N >= 4) {
                size_t aligned_size = N - N % 4;
                for (; j < aligned_size; j += 4) {
                    __m128 va = _mm_loadu_ps(&(*this)[i][j]);
                    __m128 vb = _mm_loadu_ps(&source[i][j]);
                    __m128 vres = _mm_add_ps(va, vb);
                    _mm_storeu_ps(&((*this)[i][j]), vres);
                }
            }
            for (; j < N; ++i) {
                (*this)[i][j] += source[i][j];
            }
        }
    }

    Matrix operator-(const Matrix &source) {
        Matrix temp;
        for (size_t i = 0; i < N; i++) {
            size_t j = 0;
            if (N >= 4) {
                size_t aligned_size = N - N % 4;
                for (; j < aligned_size; j += 4) {
                    __m128 va = _mm_loadu_ps(&(*this)[i][j]);
                    __m128 vb = _mm_loadu_ps(&source[i][j]);
                    __m128 vres = _mm_sub_ps(va, vb);
                    _mm_storeu_ps(&temp[i][j], vres);
                }
            }
            for (; j < N; ++i) {
                temp[i][j] = (*this)[i][j] - source[i][j];
            }
        }
        return temp;
    }

    void operator-=(const Matrix &source) {
        for (size_t i = 0; i < N; i++) {
            size_t j = 0;
            if (N >= 4) {
                size_t aligned_size = N - N % 4;
                for (; j < aligned_size; j += 4) {
                    __m128 va = _mm_loadu_ps(&(*this)[i][j]);
                    __m128 vb = _mm_loadu_ps(&source[i][j]);
                    __m128 vres = _mm_sub_ps(va, vb);
                    _mm_storeu_ps(&((*this)[i][j]), vres);
                }
            }
            for (; j < N; ++i) {
                (*this)[i][j] -= source[i][j];
            }
        }
    }

    Matrix operator*(const Matrix &source) {
        Matrix temp;
        for (size_t i = 0; i < N; i++) {
            for (size_t k = 0; k < N; k++) {
                float this_scalar = (*this)[i][k];
                size_t j = 0;
                size_t aligned_size = N - N % 4;
                if (N >= 4) {
                    __m128 v_scalar =  _mm_set1_ps(this_scalar);
                    for (; j < aligned_size; j += 4) {
                        __m128 v_source = _mm_loadu_ps(&source[k][j]);
                        __m128 v_mul = _mm_mul_ps(v_scalar, v_source);
                        __m128 v_temp = _mm_loadu_ps(&temp[i][j]);
                        __m128 v_res = _mm_add_ps(v_temp, v_mul);
                        _mm_storeu_ps(&temp[i][j], v_res);
                    }
                }
                for (; j < N; j++) {
                    temp[i][j] += this_scalar * source[k][j];
                }
            }
        }
        return temp;
    }

    void operator/=(const float divisor) {
        for (size_t i = 0; i < N; i++) {
            size_t j = 0;
            if (N >= 4) {
                size_t aligned_size = N - N % 4;
                for (; j < aligned_size; j += 4) {
                    __m128 va = _mm_loadu_ps(&(*this)[i][j]);
                    __m128 vres = _mm_div_ps(va, _mm_set1_ps(divisor));
                    _mm_storeu_ps(&((*this)[i][j]), vres);
                }
            }
            for (; j < N; j++) {
                (*this)[i][j] /= divisor;
            }
        }
    }

    float maxSumRows() {
        float maxSum = 0;
        for (size_t i = 0; i < N; i++) {
            float sum = 0;
            size_t j = 0;
            if (N >= 4) {
                size_t aligned_size = N - N % 4;
                for (; j < aligned_size; j += 4) {
                    __m128 vector = _mm_loadu_ps((*this)[i] + j);
                    __m128 v_sum = _mm_hadd_ps(vector, vector);
                    v_sum = _mm_hadd_ps(v_sum, v_sum);
                    float res;
                    _mm_store_ss(&res, v_sum);
                    sum += res;
                }
            }
            for (; j < N; j++) {
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

    cout << "Vect" << endl;
    ma.coutMatrix();
    mo.coutMatrix();

    return 0;
}
