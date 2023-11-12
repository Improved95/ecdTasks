#include <iostream>
#include <ctime>
#include <vector>
#define N 10
#define M 10

using namespace std;
using std::vector;

void matrixSum (float (&a)[N][N], float (&b)[N][N]) {
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            a[i][j] += b[i][j];
        }
    }
}

void matrixMul(float (&a)[N][N], float (&b)[N][N]) {
    vector<float> resV(N);
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            float res = 0;
            for (size_t k = 0; k < N; k++) {
                res += a[i][k] * b[k][j];
            }
            resV.push_back(res);
        }
        for (size_t t = 0; t < N; t++) {
            a[i][t] = resV[t];
        }
    }
}

void matrixDiv(float (&a)[N][N], float b) {
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            a[i][j] /= b;
        }
    }
}

float maxSumRows(float (&a)[N][N]) {
    float maxSum = 0;
    for (size_t i = 0; i < N; i++) {
        float sum = 0;
        for (size_t j = 0; j < N; j++) {
            sum += a[i][j];
        }
        if (sum > maxSum) {
            maxSum = sum;
        }
    }
    return maxSum;
}

float maxSumColumns(float (&a)[N][N]) {
    float maxSum = 0;
    for (size_t i = 0; i < N; i++) {
        float sum = 0;
        for (size_t j = 0; j < N; j++) {
            sum += a[j][i];
        }
        if (sum > maxSum) {
            maxSum = sum;
        }
    }
    return maxSum;
}

int main() {
    srand(100);
    float matrix[N][N];
    float matrixT[N][N];
    float matrixE[N][N];
    float matrixF[N][N];
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            float a = rand() / (float)rand();
            matrix[i][j] = a;
            matrixT[j][i] = a;
            matrixE[i][j] = 0;
            matrixF[i][j] = 0;
        }
        matrixE[i][i] = 1;
    }


    matrixSum(matrixF, matrixE);
    for (size_t i = 0; i < M - 1; i++) {
        // matrixSum(matrixF, )
    }

    return 0;
}

/*for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
           cout << matrixF[i][j] << " ";
    }
    cout << endl;
}*/