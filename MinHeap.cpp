#include <iostream>
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
        arr = new T[dim];
        heapsize = 1;
    }

    void insert(T key) {
        if (heapsize < dim) {
            arr[heapsize++] = key;
        }
    }

    void buildHeap() {
        for (int i=floor(heapsize/2); i>0; i--) {
            MinHeapify(i);
        }
    }

    void print(ostream &os) {
        for (int i=1; i<heapsize; i++)
            os << arr[i] << ' ';
        os << endl;
    }
};

int main() {
    auto *arr = new MinHeap<int>(10);
    arr->insert(3);
    arr->insert(65);
    arr->insert(12);
    arr->insert(45);
    arr->insert(87);
    arr->insert(23);
    arr->insert(75);
    arr->insert(72);
    arr->insert(54);
    arr->insert(98);
    cout << "Before: ";
    arr->print(cout);
    arr->buildHeap();
    cout << "After: ";
    arr->print(cout);
}