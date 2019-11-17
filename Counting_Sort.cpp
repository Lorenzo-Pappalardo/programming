#include <iostream>
#include <fstream>

using namespace std;

//Are you sure Lord Faro?
int *C;
int Cs;
//I don't think it's a great idea...

template<class T>
void print(ostream &os, T *a, int N) {
    for (int i = 0; i < N; i++)
        os << a[i] << ' ';
    //os << endl;
}

template<class T>
void countingSort(T *a, int N) {
    T min = a[0];
    T max = a[0];
    for (int i = 0; i < N; i++) {
        if (a[i] > max) max = a[i];
        if (a[i] < min) min = a[i];
    }
    T dim = max - min + 1;
    T sorted[dim];
    for (int i = 0; i < dim; i++)
        sorted[i] = 0;
    for (int i = 0; i < N; i++)
        sorted[a[i] - min]++;
    //Please Lord Faro, this is wrong...
    C = new int[dim];
    Cs = dim;
    C[0] = 0;
    int tmp = 0;
    for (int i = 1; i < dim; i++) {
        tmp += sorted[i - 1];
        C[i] = tmp;
    }
    //I've done what you asked... Now give me 10/10
    int i = 0;
    int j = 0;
    while (i < N) {
        while (sorted[j] > 0) {
            a[i++] = j + min;
            sorted[j]--;
        }
        j++;
    }
}

int main() {
    fstream input, output;
    input.open("input.txt", fstream::in);
    output.open("output.txt", fstream::out);

    int N;

    while (input >> N) {
        int *arr = new int[N];
        for (int i = 0; i < N; i++)
            input >> arr[i];
        countingSort(arr, N);
        print(output, C, Cs);
        print(output, arr, N);
        output << endl;
    }
}