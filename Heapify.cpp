#include <iostream>
#include <fstream>

using namespace std;

int count = 0;

template<class T>
class Heap {
    T *arr;
    int heapsize, dim;
    char type;

    int left(int i) const { return i << 1; }

    int right(int i) const { return (i << 1) | 1; }

    void swap(int i, int j) {
        T tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    void heapify(int i) {
        count++;
        int l = left(i);
        int r = right(i);
        if (type == 'M') {
            int max = i;
            if (l <= heapsize && (arr[l] > arr[max]))
                max = l;
            if (r <= heapsize && (arr[r] > arr[max]))
                max = r;
            if (max != i) {
                swap(i, max);
                heapify(max);
            }
        } else if (type == 'm') {
            int min = i;
            if (l < heapsize && (arr[l] < arr[min]))
                min = l;
            if (r < heapsize && (arr[r] < arr[min]))
                min = r;
            if (min != i) {
                swap(i, min);
                heapify(min);
            }
        }
    }

public:
    Heap(int dim, char choice = 'M') {
        this->dim = dim + 1;
        arr = new T[dim + 1];
        heapsize = 0;
        type = choice;
    }

    void insert(T key) { arr[++heapsize] = key; }

    void buildHeap() {
        for (int i = heapsize / 2; i > 0; i--) {
            heapify(i);
        }
    }

    void extract() {
        if (heapsize == 1) heapsize--;
        else if (heapsize > 0) {
            swap(1, heapsize);
            heapsize--;
            heapify(1);
        }
    }

    void print(ostream &os) {
        for (int i = 1; i <= heapsize; i++)
            os << arr[i] << ' ';
        os << endl;
    }
};

int main() {
    fstream input, output;
    input.open("input.txt", fstream::in);
    output.open("output.txt", fstream::out);

    string type;
    int N;

    while (input >> type >> N) {
        if (type == "int" || type == "double" || type == "bool") {
            Heap<double> *h = new Heap<double>(N);
            for (int i = 0; i < N; i++) {
                double value;
                input >> value;
                h->insert(value);
            }
            h->buildHeap();
            for (int i = 0; i < N; i++)
                h->extract();
        } else if (type == "char") {
            Heap<char> *h = new Heap<char>(N);
            for (int i = 0; i < N; i++) {
                char value;
                input >> value;
                h->insert(value);
            }
            h->buildHeap();
            for (int i = 0; i < N; i++)
                h->extract();
        }
        output << count << endl;
        count = 0;
    }
    input.close();
    output.close();
}