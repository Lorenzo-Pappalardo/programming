#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

inline int parent(int i) {
    return i >> 1;
}

inline int left(int i) {
    return i << 1;
}

inline int right(int i) {
    return (i << 1) | 1;
}

int CALLS = 0;

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
        for (int i = heapsize - 1; i > 1; i--) {
            swap(1, i);
            if (type == 'M') MaxHeapify(1, i);
            else MinHeapify(1, i);
        }
    }

public:
    Heap(int dim = 200) {
        this->dim = dim + 1;
        arr = new T[dim + 1];
        heapsize = 1;
    }

    void insert(T key, string choice = "i") {
        if (heapsize < dim) {
            arr[heapsize++] = key;
            if (choice == "dM") {
                int i = heapsize - 1;
                while (i > 1 && (arr[i] > arr[parent(i)])) {
                    swap(i, parent(i));
                    i = parent(i);
                }
            } else if (choice == "dm") {
                int i = heapsize - 1;
                while (i > 1 && (arr[i] < arr[parent(i)])) {
                    swap(i, parent(i));
                    i = parent(i);
                }
            }
        }
    }

    void buildHeap(char type) {
        if (type == 'M') {
            for (int i = heapsize / 2; i > 0; i--) {
                if (heapsize - i > 0) MaxHeapify(i, heapsize);
            }
        } else {
            for (int i = heapsize / 2; i > 0; i--) {
                if (heapsize - i > 0) MinHeapify(i, heapsize);
            }
        }
        heapsort(type);
    }

    void extract(char choice) {
        if (heapsize > 1) {
            swap(1, heapsize - 1);
            heapsize--;
            if (choice == 'M' && (heapsize > 1)) MaxHeapify(1, heapsize);
            else if (choice == 'm' && (heapsize > 1)) MinHeapify(1, heapsize);
        } else {
            cerr << "Empty set!\n";
        }
    }

    void print(ostream &os) {
        for (int i = 1; i < heapsize; i++)
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
            for (int i = 0; i < N; i++) {
                double value;
                //string value;
                input >> value;
                /*if (value.substr(0, 2) == "e:") {
                    stringstream ss;
                    double num;
                    ss << value.substr(2);
                    ss >> num;
                    mh->insert(num, "dm");
                } else {
                    mh->extract('m');
                }*/
                mh->insert(value);
            }
            mh->buildHeap('M');
            output << CALLS << ' ' << endl;
            //mh->print(output);
            //output << endl;
        } else {
            auto *mh = new Heap<char>(N);
            for (int i = 0; i < N; i++) {
                char value;
                //string value;
                input >> value;
                /*if (value.substr(0, 2) == "e:") {
                    stringstream ss;
                    char num;
                    ss << value.substr(2);
                    ss >> num;
                    mh->insert(num, "dm");
                } else {
                    mh->extract('m');
                }*/
                mh->insert(value);
            }
            mh->buildHeap('M');
            output << CALLS << ' ' << endl;
            //mh->print(output);
            //output << endl;
        }
        CALLS = 0;
    }
}