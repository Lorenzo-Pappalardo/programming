#include <iostream>
#include <fstream>
#include <cmath>

int CALLS = 0;

using namespace std;

inline int parent(int i) { return floor(i >> 1); }
inline int left(int i) { return i << 1; }
inline int right(int i) { return (i << 1) | 1; }

template<class T>
class Heap {
    T *arr;
    int dim;
    int heapsize;

    void swap(int i, int j) {
        T tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    void MaxHeapify(int i, int end) {
        CALLS++;
        int l = left(i);
        int r = right(i);
        int max = i;
        if (l < end && (arr[l] > arr[i])) {
            max = l;
        }
        if (r < end && (arr[r] > arr[max])) {
            max = r;
        }
        if (max != i) {
            swap(i, max);
            MaxHeapify(max, end);
        }
    }

    void MinHeapify(int i, int end) {
        CALLS++;
        int l = left(i);
        int r = right(i);
        int max = i;
        if (l < end && (arr[l] < arr[i])) {
            max = l;
        }
        if (r < end && (arr[r] < arr[max])) {
            max = r;
        }
        if (max != i) {
            swap(i, max);
            MinHeapify(max, end);
        }
    }

    void heapsort(char type) {
        for (int i=heapsize-1; i>1; i--) {
            swap(1, i);
            if (type == 'M') {
                MaxHeapify(1, i);
            } else {
                MinHeapify(1, i);
            }
        }
    }

    public:
    Heap(int dim = 200) {
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
                MaxHeapify(i, heapsize);
            }
        } else {
            for (int i=floor(heapsize/2); i>0; i--) {
                MinHeapify(i, heapsize);
            }
        }
        heapsort(type);
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
            auto *mh = new Heap<double>(N);
            for (int i=0; i<N; i++) {
                double value;
                input >> value;
                mh->insert(value);
            }
            mh->buildHeap('M');
            output << CALLS << ' ';
            mh->print(output);
        } else {
            auto *mh = new Heap<char>(N);
            for (int i=0; i<N; i++) {
                char value;
                input >> value;
                mh->insert(value);
            }
            mh->buildHeap('M');
            output << CALLS << ' ';
            mh->print(output);
        }
        CALLS = 0;
    }
}