#include <iostream>
#include <iomanip>
#include <cmath>

double fact(long long n)
{
    long long f=1;
    for(long long i=2; i<=n; i++)
         f*=i;
    return f;
}

using namespace std;
int main(void) {
    long double expo = 0;
    long double x = 2;
    size_t n = 85000 * 3;
    for (int i = 0; i < n + 1; i++) {
        expo += (pow(x, i) / fact(i));
    }
}