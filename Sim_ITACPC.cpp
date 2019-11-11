#include <iostream>
#include <cmath>
using namespace std;

class Node {
    unsigned short index;
    unsigned short meters;
    unsigned short movement;
public:
    Node(int index, int meters, int movement) {
        this->index = index;
        this->meters = meters;
        this->movement = movement;
    }
    unsigned short getIndex() { return index; }
    unsigned short getMeters() { return meters; }
    void update() { meters += movement; }
};

void swap(Node **a, int i, int j) {
    Node *tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int partition(Node **a, int start, int end) {
	Node *x = a[start];
	int i = start - 1;
    int j = end + 1;
    do {
    	do j--;
		while (x->getMeters() < a[j]->getMeters());

        do i++;
        while (x->getMeters() > a[i]->getMeters());

        if (i < j) swap(a, i, j);
	} while (i < j);
    return j;
}

void quickSort(Node **a, int start, int end) {
	int mid;
	if (start < end) {
		mid = partition(a, start, end);
		quickSort(a, start, mid);
		quickSort(a, mid+1, end);
    }
}

void print(ostream &os, Node **a, int N) {
    for (int i = 0; i < N; i++) {
        os << a[i]->getMeters() << ' ';
    }
    os << endl;
}

int main() {
    unsigned short N;
    cout << "Insert N: ";
    cin >> N;
    
    Node **arr = new Node*[N];

    for (int i=0; i<N; i++) {
        unsigned short a, b;
        cin >> a;
        cin >> b;
        arr[i] = new Node(i, a, b);
    }

    //quickSort(arr, 0, N - 1);
    //print(cout, arr, N);

    unsigned int start = 0;

    while (start != N - 2) {
        for (int i = 0; i < N; i++) arr[i]->update();
        quickSort(arr, start + 1, N - 1);
        unsigned short mid = N - start;
        if (mid % 2 == 1) mid = floor((N - start) / 2);
        else mid = floor((N - start) / 2) - 1;
        if (arr[mid]->getMeters() == arr[mid + 1]->getMeters() && arr[mid]->getIndex() > arr[mid + 1]->getIndex()) {
            swap(arr, mid, mid + 1);
        }
        start += mid;
    }

    //print(cout, arr, N);
    cout << arr[N - 1]->getIndex() << endl;
}