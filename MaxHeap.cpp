//
// Created by LORENZOPAPPALARDO on 19/10/2019.
//

#include <iostream>
#include <cmath>

using namespace std;

inline int parent(int i) { return floor(i >> 1); }
inline int left(int i) { return i << 1; }
inline int right(int i) { return (i << 1) + 1; }

template<class T>
class Max_Heap {
    int dim;
    int heapsize;
    int *arr;

    void swap(int i, int j) {
        T tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    void maxHeapify(int i) {
        int l = left(i);
        int r = right(i);
        int max = i;
        if  (l <= heapsize && (arr[l] > arr[i]))
            max = l;
        else if (r <= heapsize && (arr[r] > arr[max]))
            max = r;
        if (max != i) {
            swap(i, max);
            maxHeapify(max);
        }
    }
public:
    Max_Heap(int dim = 100) {
        this->dim = dim;
        arr = new T[dim];
        heapsize = 1;
    }

    void buildMaxHeap() {
        for (int i=floor(heapsize/2); i>0; i--) {
            maxHeapify(i);
        }
    }

    void insert(T key) {
        if (heapsize < dim) {
            arr[heapsize++] = key;
        } else {
            cerr << "No more space!";
        }
    }

    void print(ostream &os) {
        for (int i=1; i<heapsize; i++)
            os << arr[i] << ' ';
        os << endl;
    }
};

int main() {
    Max_Heap<int> mh;
    mh.insert(32);
    mh.insert(76);
    mh.insert(12);
    mh.insert(97);
    mh.insert(23);
    mh.insert(56);
    cout << "Before:\n";
    mh.print(cout);
    cout << "After:\n";
    mh.buildMaxHeap();
    mh.print(cout);
}