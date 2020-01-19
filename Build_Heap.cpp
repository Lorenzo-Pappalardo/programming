#include <iostream>
#include <fstream>

using namespace std;

template<class T>
class Heap {
    T *arr;
    int dim, heapsize;
    char type;

    int left(int i) const { return i << 1; }

    int right(int i) const { return (i << 1) | 1; }

    void swap(int i, int j) {
        T tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    void Heapify(int i) {
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
                Heapify(max);
            }
        } else if (type == 'm') {
            int min = i;
            if (l <= heapsize && (arr[l] < arr[min]))
                min = l;
            if (r <= heapsize && (arr[r] < arr[min]))
                min = r;
            if (min != i) {
                swap(i, min);
                Heapify(min);
            }
        }
    }

public:
    Heap(int dim, char type) {
        this->dim = dim + 1;
        arr = new T[dim + 1];
        heapsize = 0;
        this->type = type;
    }

    void insert(T key) {
        if (heapsize < dim) {
            arr[++heapsize] = key;
        }
    }

    void buildHeap() {
        for (int i = heapsize / 2; i > 0; i--) {
            Heapify(i);
        }
    }

    void print(ostream &os) {
        for (int i = 1; i <= heapsize; i++) {
            os << arr[i] << ' ';
        }
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
            Heap<double> *h = new Heap<double>(N, 'M');
            for (int i = 0; i < N; i++) {
                double value;
                input >> value;
                h->insert(value);
            }
            h->buildHeap();
            h->print(output);
        } else if (type == "char") {
            Heap<char> *h = new Heap<char>(N, 'M');
            for (int i = 0; i < N; i++) {
                char value;
                input >> value;
                h->insert(value);
            }
            h->buildHeap();
            h->print(output);
        }
    }
    input.close();
    output.close();
}