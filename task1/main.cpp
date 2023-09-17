#include <iostream>
#include <iomanip>
#include <cmath>

double fact(int N) {
    if(N < 0) 
        return 0;
    if (N == 0)
        return 1;
    else 
        return N * fact(N - 1);
}

using namespace std;
int main(void) {
    long double expo = 0;
    long double x = 2;
    size_t n = 72000;
    for (int i = 0; i < n + 1; i++) {
        expo += (pow(x, i) / fact(i));
    }

    cout << expo;
}
