#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int CALLS = 0;

template<class T>
class Heap {
    T *arr;
    int dim;
    int heapsize;
    int type;       //M for MaxHeap, m for MinHeap

    int parent(int i) const { return i >> 1; }

    int left(int i) const { return i << 1; }

    int right(int i) const { return (i << 1) | 1; }

    void swap(int i, int j) {
        T tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    void Heapify(int i) {
        CALLS++;
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
    Heap(int dim, char choice) {
        this->dim = dim;
        arr = new T[dim];
        heapsize = 0;
        type = choice;
    }

    void insert(T key) {
        if (heapsize < dim) {
            arr[++heapsize] = key;
            if (type == 'M') {
                int tmp = heapsize;
                while (tmp > 1 && arr[tmp] > arr[parent(tmp)]) {
                    swap(tmp, parent(tmp));
                    tmp = parent(tmp);
                }
            } else if (type == 'm') {
                int tmp = heapsize;
                while (tmp > 1 && arr[tmp] < arr[parent(tmp)]) {
                    swap(tmp, parent(tmp));
                    tmp = parent(tmp);
                }
            }
        }
    }

    void extract() {
        if (heapsize == 1) heapsize--;
        else if (heapsize > 1) {
            swap(1, heapsize);
            heapsize--;
            Heapify(1);
        }
    }

    void print(ostream &os) {
        os << CALLS << ' ';
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
            Heap<double> *h = new Heap<double>(N, 'M');
            for (int i = 0; i < N; i++) {
                string tmp;
                input >> tmp;
                if (tmp.substr(0, 2) == "e:") {
                    stringstream ss;
                    ss << tmp.substr(2);
                    double value;
                    ss >> value;
                    h->insert(value);
                } else h->extract();
            }
            h->print(output);
        } else if (type == "char") {
            Heap<char> *h = new Heap<char>(N, 'M');
            for (int i = 0; i < N; i++) {
                string tmp;
                input >> tmp;
                if (tmp.substr(0, 2) == "e:") {
                    stringstream ss;
                    ss << tmp.substr(2);
                    char value;
                    ss >> value;
                    h->insert(value);
                } else h->extract();
            }
            h->print(output);
        }
        CALLS = 0;
    }
    input.close();
    output.close();
}