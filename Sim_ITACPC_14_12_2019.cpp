#include <iostream>

using namespace std;

short factorial(unsigned long long value) {
    unsigned long long sum = 1;
    int i = 1;
    while (sum < value) {
        sum *= (++i);
    }
    return i;
}

int main() {
    unsigned long long value;
    cin >> value;
    cout << factorial(value) << endl;
}