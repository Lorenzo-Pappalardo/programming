#include <iostream>
#include <fstream>
#include <sstream>

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

    void setKey(T key) {
        this->key = key;
    }

    void setParent(Node<T> *parent) {
        this->parent = parent;
    }

    void setLeft(Node<T> *left) {
        this->left = left;
    }

    void setRight(Node<T> *right) {
        this->right = right;
    }

    T getKey() {
        return key;
    }

    Node<T> *getParent() {
        return parent;
    }

    Node<T> *getLeft() {
        return left;
    }

    Node<T> *getRight() {
        return right;
    }
};

template<class T>
class BST {
    Node<T> *root;

    void _insert(T key) {
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
        while (tmp && tmp->getLeft()) {
            tmp = tmp->getLeft();
        }
        return tmp;
    }

    Node<T> *successor(Node<T> *tmp) {
        if (tmp->getRight()) return min(tmp->getRight());
        T savedKey = tmp->getKey();
        do tmp = tmp->getParent();
        while (savedKey > tmp->getKey());
        return tmp;
    }

    void _remove(T key, Node<T> *tmp) {
        if (tmp && tmp->getKey() == key) {
            if (tmp->getRight() && tmp->getLeft()) {
                Node<T> *s = successor(tmp);
                tmp->setKey(s->getKey());
                _remove(s->getKey(), s);
            } else {
                Node<T> *p = tmp->getParent();
                Node<T> *c = tmp->getLeft();
                if (!c) c = tmp->getRight();
                if (p) {
                    if (key < p->getKey()) p->setLeft(c);
                    else p->setRight(c);
                } else root = c;
                if (c) {
                    c->setParent(p);
                }
            }
        }
    }

    bool isLeftChild(Node<T> *node) {
        return node == node->getParent()->getLeft();
    }

    void insertNodeUp(Node<T> *before, Node<T> *after) {
        if (before->getParent()) {
            if (isLeftChild(before)) before->getParent()->setLeft(after);
            else before->getParent()->setRight(after);
        } else root = after;
        after->setParent(before->getParent());
        before->setParent(after);
    }

    void _inorder(ostream &os, Node<T> *tmp) {
        if (tmp) {
            _inorder(os, tmp->getLeft());
            os << tmp->getKey() << ' ';
            _inorder(os, tmp->getRight());
        }
    }

    void _preorder(ostream &os, Node<T> *tmp) {
        if (tmp) {
            os << tmp->getKey() << ' ';
            _preorder(os, tmp->getLeft());
            _preorder(os, tmp->getRight());
        }
    }

    void _postorder(ostream &os, Node<T> *tmp) {
        if (tmp) {
            _postorder(os, tmp->getLeft());
            _postorder(os, tmp->getRight());
            os << tmp->getKey() << ' ';
        }
    }

public:
    BST() {
        root = nullptr;
    }

    BST *insert(T key) {
        _insert(key);
        return this;
    }

    BST *remove(T key) {
        Node<T> *toDel = _search(key, root);
        if (toDel) _remove(key, toDel);
        return this;
    }

    void leftRotate(T key) {
        Node<T> *pivot = _search(key, root);
        if (pivot && pivot->getRight()) {
            Node<T> *newParent = pivot->getRight();
            insertNodeUp(pivot, newParent);
            pivot->setRight(newParent->getLeft());
            if (newParent->getLeft()) newParent->getLeft()->setParent(pivot);
            newParent->setLeft(pivot);
        }
    }

    void rightRotate(T key) {
        Node<T> *pivot = _search(key, root);
        if (pivot && pivot->getLeft()) {
            Node<T> *newParent = pivot->getLeft();
            insertNodeUp(pivot, newParent);
            pivot->setLeft(newParent->getRight());
            if (newParent->getRight()) newParent->getRight()->setParent(pivot);
            newParent->setRight(pivot);
        }
    }

    void inorder(ostream &os) {
        _inorder(os, root);
        os << endl;
    }

    void preorder(ostream &os) {
        _preorder(os, root);
        os << endl;
    }

    void postorder(ostream &os) {
        _postorder(os, root);
        os << endl;
    }
};

int main() {
    fstream input, output;
    input.open("input.txt", fstream::in);
    output.open("output.txt", fstream::out);

    string type;
    int N;
    int R;
    string visit;

    while (input >> type >> N >> R >> visit) {
        if (type == "int") {
            BST<int> *t = new BST<int>();
            for (int i = 0; i < N + R; i++) {
                string value;
                input >> value;
                if (value[0] == 'i') {
                    value = value.substr(4);
                    stringstream ss;
                    ss << value;
                    int tmp;
                    ss >> tmp;
                    t->insert(tmp);
                } else if (value[0] == 'c') {
                    value = value.substr(5);
                    stringstream ss;
                    ss << value;
                    int tmp;
                    ss >> tmp;
                    t->remove(tmp);
                } else if (value[0] == 'l') {
                    value = value.substr(5);
                    stringstream ss;
                    ss << value;
                    int tmp;
                    ss >> tmp;
                    t->leftRotate(tmp);
                } else {
                    value = value.substr(6);
                    stringstream ss;
                    ss << value;
                    int tmp;
                    ss >> tmp;
                    t->rightRotate(tmp);
                }
            }
            if (visit == "inorder") {
                t->inorder(output);
            } else if (visit == "preorder") {
                t->preorder(output);
            } else {
                t->postorder(output);
            }
        }
        if (type == "double") {
            BST<double> *t = new BST<double>();
            for (int i = 0; i < N + R; i++) {
                string value;
                input >> value;
                if (value[0] == 'i') {
                    value = value.substr(4);
                    stringstream ss;
                    ss << value;
                    double tmp;
                    ss >> tmp;
                    t->insert(tmp);
                } else if (value[0] == 'c') {
                    value = value.substr(5);
                    stringstream ss;
                    ss << value;
                    double tmp;
                    ss >> tmp;
                    t->remove(tmp);
                } else if (value[0] == 'l') {
                    value = value.substr(5);
                    stringstream ss;
                    ss << value;
                    double tmp;
                    ss >> tmp;
                    t->leftRotate(tmp);
                } else {
                    value = value.substr(6);
                    stringstream ss;
                    ss << value;
                    double tmp;
                    ss >> tmp;
                    t->rightRotate(tmp);
                }
            }
            if (visit == "inorder") {
                t->inorder(output);
            } else if (visit == "preorder") {
                t->preorder(output);
            } else {
                t->postorder(output);
            }
        }
    }
}