#include <iostream>
#include <fstream>

using namespace std;

const int BLACK = 0;
const int RED = 1;

template<class T>
class Node {
    T key;
    Node<T> *parent, *left, *right;
    int color;
public:
    Node(T key) {
        this->key = key;
        parent = left = right = nullptr;
        color = RED;
    }

    void setColor(int color) { this->color = color; }

    void setParent(Node<T> *parent) { this->parent = parent; }

    void setLeft(Node<T> *left) { this->left = left; }

    void setRight(Node<T> *right) { this->right = right; }

    T getKey() { return key; }

    int getColor() { return color; }

    Node<T> *getGrandparent() { return (this->getParent()->getParent()) ? this->getParent()->getParent() : nullptr; }

    Node<T> *getUncle() {
        if (getGrandparent()) {
            if (parent == getGrandparent()->getLeft()) return getGrandparent()->getRight();
            return getGrandparent()->getLeft();
        }
        return nullptr;
    }

    Node<T> *getParent() { return parent; }

    Node<T> *getLeft() { return left; }

    Node<T> *getRight() { return right; }
};

template<class T>
class RBT {
    Node<T> *root;

    void checkProperties(Node<T> *n) {
        if (!(n->getParent()))
            n->setColor(BLACK);
        else if (n->getParent() && n->getParent()->getColor() == BLACK);
        else if (n->getUncle() && n->getUncle()->getColor() == RED)
            redU(n);
        else blackUI(n);
    }

    void redU(Node<T> *n) {
        n->getGrandparent()->setColor(RED);
        n->getParent()->setColor(BLACK);
        Node<T> *checkUncle = n->getUncle();
        n->getUncle()->setColor(BLACK);
        checkProperties(n->getGrandparent());
    }

    void blackUI(Node<T> *n) {
        Node<T> *p = n->getParent();
        Node<T> *g = n->getGrandparent();
        if (n == p->getLeft() && p == g->getRight()) {
            rightRotate(p);
            n = n->getRight();
        } else if (n == p->getRight() && p == g->getLeft()) {
            leftRotate(p);
            n = n->getLeft();
        }
        blackUE(n);
    }

    void blackUE(Node<T> *n) {
        Node<T> *p = n->getParent();
        Node<T> *g = n->getGrandparent();
        if (n == p->getLeft()) rightRotate(g);
        else if (n == p->getRight()) leftRotate(g);
        p->setColor(BLACK);
        if (g != root) g->setColor(RED);
    }

    void leftRotate(Node<T> *pivot) {
        Node<T> *newPivot = pivot->getRight();
        pivot->setRight(newPivot->getLeft());
        if (newPivot->getLeft()) newPivot->getLeft()->setParent(pivot);
        newPivot->setParent(pivot->getParent());
        if (!(pivot->getParent())) root = newPivot;
        else if (pivot == pivot->getParent()->getLeft()) pivot->getParent()->setLeft(newPivot);
        else pivot->getParent()->setRight(newPivot);
        newPivot->setLeft(pivot);
        pivot->setParent(newPivot);
    }

    void rightRotate(Node<T> *pivot) {
        Node<T> *newPivot = pivot->getLeft();
        pivot->setLeft(newPivot->getRight());
        if (newPivot->getRight()) newPivot->getRight()->setParent(pivot);
        newPivot->setParent(pivot->getParent());
        if (!(pivot->getParent())) root = newPivot;
        else if (pivot == pivot->getParent()->getLeft()) pivot->getParent()->setLeft(newPivot);
        else pivot->getParent()->setRight(newPivot);
        newPivot->setRight(pivot);
        pivot->setParent(newPivot);
    }

    int _height(Node<T> *tmp) {
        if (!tmp) return 0;
        int leftH = _height(tmp->getLeft());
        int rightH = _height(tmp->getRight());
        if (leftH > rightH) return leftH + 1;
        return rightH + 1;
    }

public:
    RBT() {
        root = nullptr;
    }

    void insert(T key) {
        Node<T> *newNode = new Node<T>(key);
        Node<T> *current = root;
        Node<T> *last = nullptr;
        while (current) {
            last = current;
            if (key <= current->getKey()) current = current->getLeft();
            else current = current->getRight();
        }
        if (last) {
            if (key <= last->getKey()) last->setLeft(newNode);
            else last->setRight(newNode);
        } else root = newNode;
        newNode->setParent(last);
        checkProperties(newNode);
    }

    int height() { return _height(root); }
};

int main() {
    fstream input, output;
    input.open("input.txt", fstream::in);
    output.open("output.txt", fstream::out);

    string type;
    int N;

    while (input >> type >> N) {
        if (type == "int") {
            RBT<int> t;
            for (int i = 0; i < N; i++) {
                int value;
                input >> value;
                t.insert(value);
            }
            output << t.height() << endl;
        } else if (type == "double") {
            RBT<double> t;
            for (int i = 0; i < N; i++) {
                double value;
                input >> value;
                t.insert(value);
            }
            output << t.height() << endl;
        }
    }

    input.close();
    output.close();
}