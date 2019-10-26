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
        int biggest = i;
        if (l <= heapsize && (arr[l] > arr[i]))
            biggest = l;
        if (r <= heapsize && (arr[r] > arr[biggest]))
            biggest = r;
        if (biggest != i) {
            swap(i, biggest);
            maxHeapify(biggest);
        }
    }

public:
    Max_Heap(int dim) {
        this->dim = dim + 1;
        arr = new T[dim + 1];
        heapsize = 1;
    }

    void insert(T key) {
        if (heapsize <= dim) {
            arr[heapsize] = key;
            int i = heapsize++;
            while (i > 1 && (arr[i] > arr[parent(i)])) {
                swap(i, parent(i));
                i = parent(i);
            }
        }
    }

    void buildMaxHeap() {
        for (int i = floor(heapsize / 2); i > 0; i--)
            maxHeapify(i);
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
            auto *mh = new Max_Heap<int>(N);
            for (int i = 0; i < N; i++) {
                int key;
                input >> key;
                mh->insert(key);
            }
            mh->buildMaxHeap();
            mh->print(output);
        } else if (type == "double") {
            auto *mh = new Max_Heap<double>(N);
            for (int i = 0; i < N; i++) {
                double key;
                input >> key;
                mh->insert(key);
            }
            mh->buildMaxHeap();
            mh->print(output);
        } else {
            auto *mh = new Max_Heap<char>(N);
            for (int i = 0; i < N; i++) {
                char key;
                input >> key;
                mh->insert(key);
            }
            mh->buildMaxHeap();
            mh->print(output);
        }
    }
}