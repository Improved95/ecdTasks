#include <iostream>
#include <ctime>
#include <vector>

#define M 10
#define N 3

using namespace std;
using std::vector;

class Matrix {
    float **array;

public:
    Matrix() {
        array = new float*[N];
        for (size_t i = 0; i < N; i++) {
            array[i] = new float[N];
        }
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                array[i][j] = 0;
            }
        }
    }
    ~Matrix() {
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

    void operator=(const Matrix &other) {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                (*this)[i][j] = other[i][j];
            }
        }
    }

    Matrix operator+(const Matrix &a) {
        Matrix temp;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                temp[i][j] = (*this)[i][j] + a[i][j];
            }
        }
        return temp;
    }

    Matrix operator-(const Matrix &a) {
        Matrix temp;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                temp[i][j] = (*this)[i][j] - a[i][j];
            }
        }
        return temp;
    }

    Matrix operator*(const Matrix &a) {
        Matrix temp;
        vector<float> resV;
        for (size_t i = 0; i < N; i++) {
            float res = 0;
            for (size_t j = 0; j < N; j++) {
                for (size_t k = 0; k < N; k++) {
                    res += (*this)[i][k] * a[k][j];
                }
                temp[i][j] = res;
            }
        }
        return temp;
    }

    Matrix operator/(const float a) {
        Matrix temp;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                temp[i][j] = (*this)[i][j] / (float)a;
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
};

int main() {
    srand(100);

    Matrix ma, mt, me;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            float a = (float)(rand() % 100) / (float)(rand() % 100) * 100;
            ma[i][j] = a;
            mt[j][i] = a;
            me[i][j] = 0;
        }
        me[i][i] = 1;
    }

    Matrix mf;
    mf = me;
    for (size_t i = 1; i < M; i++) {
        Matrix mb = mt / (ma.maxSumRows() * ma.maxSumColumns());
        Matrix mr = me - (mb * ma);
        for (size_t j = 1; j < i; j++) {
            mr = mr * mr;
        }
        mf = mf + mr;
    }

     for (size_t i = 0; i < N; i++) {
         for (size_t j = 0; j < N; j++) {
             cout << mf[i][j] << " ";
         }
         cout << endl;
     }

    return 0;
}
