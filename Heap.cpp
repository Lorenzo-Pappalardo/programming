#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

inline int parent(int i) { return floor(i >> 1); }
inline int left(int i) { return i << 1; }
inline int right(int i) { return (i << 1) | 1; }

template<class T>
class MinHeap {
    T *arr;
    int dim;
    int heapsize;

    void swap(int i, int j) {
        T tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    void MaxHeapify(int i) {
        int l = left(i);
        int r = right(i);
        int max = i;
        if (l < heapsize && (arr[l] > arr[i])) {
            max = l;
        }
        if (r < heapsize && (arr[r] > arr[max])) {
            max = r;
        }
        if (max != i) {
            swap(i, max);
            MaxHeapify(max);
        }
    }

    void MinHeapify(int i) {
        int l = left(i);
        int r = right(i);
        int max = i;
        if (l < heapsize && (arr[l] < arr[i])) {
            max = l;
        }
        if (r < heapsize && (arr[r] < arr[max])) {
            max = r;
        }
        if (max != i) {
            swap(i, max);
            MinHeapify(max);
        }
    }

    public:
    MinHeap(int dim = 200) {
        this->dim = dim+1;
        arr = new T[dim+1];
        heapsize = 1;
    }

    void insert(T key) {
        if (heapsize < dim) {
            arr[heapsize++] = key;
        }
    }

    void buildHeap(char type) {
        if (type == 'M') {
            for (int i=floor(heapsize/2); i>0; i--) {
                MaxHeapify(i);
            }
        } else {
            for (int i=floor(heapsize/2); i>0; i--) {
                MinHeapify(i);
            }
        }
    }

    void print(ostream &os) {
        for (int i=1; i<heapsize; i++)
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
            auto *mh = new MinHeap<double>(N);
            for (int i=0; i<N; i++) {
                double value;
                input >> value;
                mh->insert(value);
            }
            mh->buildHeap('M');
            mh->print(output);
        } else {
            auto *mh = new MinHeap<char>(N);
            for (int i=0; i<N; i++) {
                char value;
                input >> value;
                mh->insert(value);
            }
            mh->buildHeap('M');
            mh->print(output);
        }
    }
}