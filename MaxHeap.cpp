//
// Created by LORENZOPAPPALARDO on 19/10/2019.
//

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

inline int parent(int i) { return floor(i >> 1); }
inline int left(int i) { return i << 1; }
inline int right(int i) { return (i << 1) + 1; }

template<class T>
class Max_Heap {
    int dim;
    int heapsize;
    T *arr;

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
        for (int i = floor(heapsize / 2); i > 0; i--)
            maxHeapify(i);
    }

    void insert(T key) {
        if (heapsize <= dim) {
            int i = heapsize;
            arr[heapsize++] = key;
            while (i > 1 && arr[i] > arr[parent(i)]) {
                swap(i, parent(i));
                i = parent(i);
            }
        } else
            cerr << "No more space!";
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
        if (type == "int" || type == "bool") {
            auto *mh = new Max_Heap<int>();
            for (int i = 0; i < N; i++) {
                int key;
                input >> key;
                mh->insert(key);
            }
            //mh->buildMaxHeap();
            mh->print(output);
        } else if (type == "double") {
            auto *mh = new Max_Heap<double>();
            for (int i = 0; i < N; i++) {
                double key;
                input >> key;
                mh->insert(key);
            }
            //mh->buildMaxHeap();
            mh->print(output);
        } else {
            auto *mh = new Max_Heap<char>();
            for (int i = 0; i < N; i++) {
                char key;
                input >> key;
                mh->insert(key);
            }
            //mh->buildMaxHeap();
            mh->print(output);
        }
    }
}