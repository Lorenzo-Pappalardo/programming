#include <iostream>
using namespace std;

static const int BLACK=0;
static const int RED=1;

template <class T>
class Node {
    T key;
    int color;
    Node<T> *parent, *left, *right;
public:
    Node(T key, int color) {
        this->key = key;
        this->color = color;
        parent = left = right = nullptr;
    }

    void setKey(T key) { this->key = key; }

    void setColor(int color) { this->color = color; }

    void setPointer(Node<T> *pointer, char choice) {
        if (choice == 'p') parent = pointer;
        else if (choice = 'l') left = pointer;
        else if (choice == 'r') right = pointer;
        else cerr << "Invalid choice!";
    }

    const T getKey() const { return key; }

    const char getColor() const {
        if (color) return 'R';
        return 'B';
    }

    Node<T> *getPointer(char choice) const {
        if (choice == 'p') return parent;
        if (choice == 'l') return left;
        if (choice == 'r') return right;
        cerr << "Invalid choice!";
        return nullptr;
    }
};

template<class T>
class RBT {
    Node<T> *root;
    string visit;

    void _print(ostream &os, Node<T> *tmp) {
        if (tmp && visit == "in") {
            _print(os, tmp->getPointer('l'));
            os << '(' << tmp->getKey() << ',' << tmp->getColor() << ") ";
            _print(os, tmp->getPointer('r'));
        } else if (tmp && visit == "pre") {
            os << '(' << tmp->getKey() << ',' << tmp->getColor() << ") ";
            _print(os, tmp->getPointer('l'));
            _print(os, tmp->getPointer('r'));
        } else if (tmp && visit == "post") {
            _print(os, tmp->getPointer('l'));
            _print(os, tmp->getPointer('r'));
            os << '(' << tmp->getKey() << ',' << tmp->getColor() << ") ";
        }
    }
public:
    RBT() { root = nullptr; }

    void print(ostream &os, string visit) {
        this->visit = visit;
        _print(os, root);
    }
};

int main() {
}