#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

double fact(long long n) {
    long long f = 1;
    for(long long i=2; i<=n; i++) {
        f *= i;
    }
    return f;
}

using namespace std;
int main(int argc, char* argv[]) {
    long double expo = 0;
    long double x = 2;
    size_t n = stoull(argv[1]);
    for (int i = 0; i < n + 1; i++) {
        expo += (pow(x, i) / fact(i));
    }
}
