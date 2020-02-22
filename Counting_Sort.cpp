#include <fstream>
#include <iostream>

using namespace std;

template<class T>
void print(ostream &os, T *a, int N) {
    for (int i = 0; i < N; i++)
        os << a[i] << ' ';
}

template<class T>
void countingSort(ostream &os, T *a, int N) {
    T max = a[0];
    T min = a[0];
    for (int i = 1; i < N; i++) {               //Finding max and min
        if (a[i] > max) max = a[i];
        if (a[i] < min) min = a[i];
    }
    T size = max - min + 1;
    T count[size];
    for (int i = 0; i < size; i++)              //Initializing count array
        count[i] = 0;
    for (int i = 0; i < N; i++)                 //Counting elements
        count[a[i] - min]++;
    for (int i = 1; i < size; i++)              //Summing frequencies
        count[i] += count[i - 1];
    T tmp[N];
    for (int i = N - 1; i >= 0; i--) {          //Sorting temporary array
        tmp[count[a[i] - min] - 1] = a[i];
        count[a[i] - min]--;
    }
    for (int i = 0; i < N; i++)                 //Copying sorted elements into the original array
        a[i] = tmp[i];
    print(os, count, size);
}

int main() {
    fstream input, output;
    input.open("input.txt", fstream::in);
    output.open("output.txt", fstream::out);

    string type;
    int N;

    while (input >> type >> N) {
        if (type == "int" || type == "bool") {
            int a[N];
            for (int i = 0; i < N; i++)
                input >> a[i];
            countingSort(output, a, N);
            print(output, a, N);
            output << endl;
        } else if (type == "double") {
            double a[N];
            for (int i = 0; i < N; i++)
                input >> a[i];
            int tmp[N];
            for (int i = 0; i < N; i++)
                tmp[i] = (int) (a[i] * 10);
            countingSort(output, tmp, N);
            for (int i = 0; i < N; i++)
                a[i] = (double) (tmp[i]) / 10;
            print(output, a, N);
            output << endl;
        } else {
            char a[N];
            for (int i = 0; i < N; i++)
                input >> a[i];
            output << endl;
        }
    }
    input.close();
    output.close();
}