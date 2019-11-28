#include <iostream>
#include <fstream>

using namespace std;

template<class T>
class Node {
    T key;
    Node<T> *parent, *left, *right;
public:
    Node(T key) {
        this->key = key;
        parent = left = right = nullptr;
    }

    void setKey(T key) { this->key = key; }

    void setParent(Node<T> *parent) { this->parent = parent; }

    void setLeft(Node<T> *left) { this->left = left; }

    void setRight(Node<T> *right) { this->right = right; }

    T getKey() { return key; }

    Node<T> *getParent() { return parent; }

    Node<T> *getLeft() { return left; }

    Node<T> *getRight() { return right; }
};

template<class T>
class BST {
    Node<T> *root;

    void _inorder(ostream &os, Node<T> *tmp) {
        if (tmp) {
            _inorder(os, tmp->getLeft());
            os << tmp->getKey() << ' ';
            _inorder(os, tmp->getRight());
        }
    }

    Node<T> *_search(T key, Node<T> *tmp) {
        while (tmp) {
            if (key == tmp->getKey()) return tmp;
            if (key <= tmp->getKey()) tmp = tmp->getLeft();
            else tmp = tmp->getRight();
        }
        return nullptr;
    }

    Node<T> *min(Node<T> *tmp) {
        while (tmp && tmp->getLeft()) { tmp = tmp->getLeft(); }
        return tmp;
    }

    Node<T> *successor(Node<T> *tmp) {
        if (tmp->getRight()) return min(tmp->getRight());
        else {
            T savedKey = tmp->getKey();
            do {
                tmp = tmp->getParent();
            } while (savedKey > tmp->getKey());
        }
        return tmp;
    }

    BST *_del(T key, Node<T> *tmp) {
        Node<T> *toDel = _search(key, tmp);
        if (toDel) {
            if (toDel->getLeft() && toDel->getRight()) {
                Node<T> *s = successor(toDel);
                toDel->setKey(s->getKey());
                return _del(toDel->getKey(), s);
            } else {
                Node<T> *parent = toDel->getParent();
                Node<T> *child = toDel->getLeft();
                if (!child) child = toDel->getRight();
                if (parent) {
                    if (key <= parent->getKey()) parent->setLeft(child);
                    else parent->setRight(child);
                } else root = child;
                if (child) { child->setParent(parent); }
            }
        }
        return this;
    }

public:
    BST() { root = nullptr; }

    BST *insert(T key) {
        Node<T> *tmp = root;
        Node<T> *p = nullptr;
        auto *newnode = new Node<T>(key);
        while (tmp) {
            p = tmp;
            if (key <= tmp->getKey()) tmp = tmp->getLeft();
            else tmp = tmp->getRight();
        }
        if (p) {
            if (key <= p->getKey()) p->setLeft(newnode);
            else p->setRight(newnode);
            newnode->setParent(p);
        } else root = newnode;
        return this;
    }

    BST *del(T key) { return _del(key, root); }

    void inorder(ostream &os) {
        _inorder(os, root);
        os << endl;
    }
};

int main() {
    auto *t = new BST<int>();
    t->insert(5)->insert(4)->insert(9)->insert(7)->insert(37)->insert(23);
    t->inorder(cout);
    t->del(4);
    t->del(9);
    t->del(37);
    t->del(5);
    cout << "RES:\n";
    t->inorder(cout);
}