#include <stdio.h>
#include <math.h>

double fact(int N) {
    if(N < 0)
        return 0;
    if (N == 0)
        return 1;
    else
        return N * fact(N - 1);
}

int main() {
    long double expo = 0;
    long double x = 2;
    size_t n = 100;
    for (int i = 0; i < n + 1; i++) {
        long double a = pow(x, i);
        long double b = fact(i);
        expo += (a / b);
    }

    printf("%Le ", expo);
}
