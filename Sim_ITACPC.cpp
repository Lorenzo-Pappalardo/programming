#include <iostream>
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
    cin >> N;
    
    Node **arr = new Node*[N];

    for (int i=0; i<N; i++) {
        unsigned short a, b;
        cin >> a;
        cin >> b;
        arr[i] = new Node(i, a, b);
    }

    quickSort(arr, 0, N - 1);

    print(cout, arr, N);
}