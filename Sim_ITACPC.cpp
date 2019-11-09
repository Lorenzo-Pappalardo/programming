#include <iostream>
using namespace std;

class Node {
    unsigned short value;
    unsigned short meters;
    unsigned short movement;
public:
    Node() {
        value = meters = movement = 0;
    }
    void insert(int value, int meters, int movement) {
        this->value = value;
        this->meters = meters;
        this->movement = movement;
    }
    unsigned short getValue() { return value; };
    unsigned short getMeters() { return meters; }
    void update() { meters += movement; }
};

void swap(Node *a, int i, int j) {
    Node tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int main() {
    unsigned short N;
    cin >> N;
    
    Node *arr = new Node[N];

    for (int i=0; i<N; i++) {
        unsigned short a, b;
        cin >> a;
        cin >> b;
        arr[i].insert(i, a, b);
    }

    unsigned short time = 0;

    while (N > 1) {
        if (time > 0) {
            for (int i=0; i<N; i++) arr[i].update();
            countSort(arr, N);
            for (int i=0; i<N/2; i++) {
                swap(arr, i, N-1-i);
            }
            N = N/2;
        }
        time++;
    }

    /*quicksort(arr, 0, N-1);
    for (int i=0; i<N; i++) {
        cout << arr[i].getValue() << ' ';
    }*/

    cout << arr[0].getValue() << endl;
}