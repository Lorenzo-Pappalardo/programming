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

    bool isLeftChild(Node<T> *node) { return node == node->getParent()->getLeft(); }

    void insertNodeUp(Node<T> *before, Node<T> * node) {
        if (before->getParent()) {
            if (isLeftChild(node)) before->getParent()->setLeft(node);
            else before->getParent()->setRight(node);
        } else root = node;
        node->setParent(before->getParent());
        before->setParent(node);
    }

public:
    BST() { root = nullptr; }

    BST *insert(T key) {
        _insert(key);
        return this;
    }

    BST *del(T key) { return _del(key, root); }

    Node<T> *search(T key) { return _search(key, root); }

    void leftRotate(Node<T> *node) {
        Node<T> *newParent = node->getRight();
        insertNodeUp(node, newParent);
        node->setRight(newParent->getLeft());
        if (newParent->getLeft()) newParent->getLeft()->setParent(node);
        newParent->setLeft(node);
    }

    void rightRotate(Node<T>* node)
	{
		Node<T> *newParent = node->getLeft();
        insertNodeUp(node, newParent);
        node->setLeft(newParent->getRight());
        if (newParent->getRight()) newParent->getRight()->setParent(node);
        newParent->setRight(node);
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

    while(input >> type >> N >> R >> visit) {
        if (type == "int") {
            BST<int> *t = new BST<int>();
            for (int i=0; i<N+R; i++) {
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
                    t->del(tmp);
                } else if (value[0] == 'l') {
                    value = value.substr(5);
                    stringstream ss;
                    ss << value;
                    int tmp;
                    ss >> tmp;
                    t->leftRotate(t->search(tmp));
                } else {
                    value = value.substr(6);
                    stringstream ss;
                    ss << value;
                    int tmp;
                    ss >> tmp;
                    t->rightRotate(t->search(tmp));
                }
            }
            if (visit == "inorder") { t->inorder(output); }
            else if (visit == "preorder") { t->preorder(output); }
            else { t->postorder(output); }
        }
        if (type == "double") {
            BST<double> *t = new BST<double>();
            for (int i=0; i<N+R; i++) {
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
                    t->del(tmp);
                } else if (value[0] == 'l') {
                    value = value.substr(5);
                    stringstream ss;
                    ss << value;
                    double tmp;
                    ss >> tmp;
                    t->leftRotate(t->search(tmp));
                } else {
                    value = value.substr(6);
                    stringstream ss;
                    ss << value;
                    double tmp;
                    ss >> tmp;
                    t->rightRotate(t->search(tmp));
                }
            }
            if (visit == "inorder") { t->inorder(output); }
            else if (visit == "preorder") { t->preorder(output); }
            else { t->postorder(output); }
        }
    }
}