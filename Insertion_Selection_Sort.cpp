//
// Created by LORENZOPAPPALARDO on 20/10/2019.
//

#include <iostream>

using namespace std;

template<class T>
void selectionSort(T *arr, int N) {
    for (int i = 0; i < N - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < N; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        T tmp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = tmp;
    }
}

template<class T>
void insertionSort(T *arr, int N) {
    for (int i = 1; i < N; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = key;
    }
}

template<class T>
void print(ostream &os, T *arr, int N) {
    for (int i = 0; i < N; i++)
        os << arr[i] << ' ';
    os << "\n\n";
}

int main() {
    const int N = 100;
    int *arr = new int[N];
    for (int i = 0; i < N; i++) {
        arr[i] = (rand() % 100) + 1;
    }
    selectionSort(arr, N);
    print(cout, arr, N);
    insertionSort(arr, N);
    print(cout, arr, N);
}