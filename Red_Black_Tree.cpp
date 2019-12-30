#include <iostream>
#include <fstream>

using namespace std;

static const int BLACK = 0;
static const int RED = 1;

template<class T>
class Node {
    T key;
    int color;
    Node<T> *parent, *left, *right;
public:
    Node(T key, int color = RED) {
        this->key = key;
        this->color = color;
        parent = left = right = nullptr;
    }

    void setKey(T key) {
        this->key = key;
    }

    void setColor(int color) {
        this->color = color;
    }

    void setPointer(Node<T> *pointer, char choice) {
        if (choice == 'p') parent = pointer;
        else if (choice == 'l') left = pointer;
        else if (choice == 'r') right = pointer;
        else cerr << "Invalid choice!";
    }

    const T getKey() const {
        return key;
    }

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

    bool isLeftChild(Node<T> *node) {
        return node == node->getPointer('p')->getPointer('l');
    }

    Node<T> *getUncle(Node<T> *node) {
        if (!node->getPointer('p') || !node->getPointer('p')->getPointer('p')) return nullptr;
        if (isLeftChild(node->getPointer('p'))) {
            return node->getPointer('p')->getPointer('p')->getPointer('r');
        }
        return node->getPointer('p')->getPointer('p')->getPointer('l');
    }

    void swapColors(Node<T> *n1, Node<T> *n2) {
        int tmp = n1->getColor();
        n1->setColor(n2->getColor());
        n2->setColor(tmp);
    }

    void insertNodeUp(Node<T> *before, Node<T> *node) {
        if (before->getPointer('p')) {
            if (isLeftChild(before)) {
                before->getPointer('p')->setPointer(node, 'l');
            } else {
                before->getPointer('p')->setPointer(node, 'r');
            }
        } else root = node;
        node->setPointer(before->getPointer('p'), 'p');
        before->setPointer(node, 'p');
    }

    void rightRotation(Node<T> *node) {
        Node<T> *newParent = node->getPointer('l');
        insertNodeUp(node, newParent);
        node->setPointer(newParent->getPointer('r'), 'l');
        if (newParent->getPointer('r')) newParent->getPointer('r')->setPointer(node, 'p');
        newParent->setPointer(node, 'r');
    }

    void leftRotation(Node<T> *node) {
        Node<T> *newParent = node->getPointer('r');
        insertNodeUp(node, newParent);
        node->setPointer(newParent->getPointer('l'), 'r');
        if (newParent->getPointer('l')) newParent->getPointer('l')->setPointer(node, 'p');
        newParent->setPointer(node, 'l');
    }

    void insertFixUp(Node<T> *node) {
        do {
            if (node == root) {
                node->setColor(BLACK);
            } else {
                Node<T> *p = node->getPointer('p');
                Node<T> *gp = p->getPointer('p');
                Node<T> *u = getUncle(node);
                if (p->getColor() != BLACK) {
                    if (u != nullptr && u->getColor() == RED) {
                        p->setColor(BLACK);
                        gp->setColor(BLACK);
                        u->setColor(BLACK);
                        node = gp;
                    } else {
                        if (isLeftChild(p)) {
                            if (isLeftChild(node))
                                swapColors(p, gp);
                            else {
                                leftRotation(p);
                                swapColors(node, gp);
                            }
                            rightRotation(gp);
                        } else {
                            if (isLeftChild(node)) {
                                rightRotation(p);
                                swapColors(node, gp);
                            } else swapColors(p, gp);
                            leftRotation(gp);
                        }
                        return;
                    }
                }
            }
        } while (true);
    }

    Node<T> *search(T key) {
        Node<T> *tmp = root;
        Node<T> *parent = nullptr;
        while (tmp) {
            if (key == tmp->getKey()) return tmp;
            parent = tmp;
            if (key < tmp->getKey()) tmp = tmp->getPointer('l');
            else tmp = tmp->getPointer('r');
        }
        return parent;
    }

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
        os << endl;
    }

public:
    RBT() {
        root = nullptr;
    }

    void print(ostream &os, string visit) {
        this->visit = visit;
        _print(os, root);
    }

    RBT *insert(T key) {
        Node<T> *newNode = new Node<T>(key);
        if (!root) {
            newNode->setColor(BLACK);
            root = newNode;
        } else {
            Node<T> *tmp = search(key);
            if (tmp->getKey() != key) {
                newNode->setPointer(tmp, 'p');
                if (key < tmp->getKey())
                    tmp->setPointer(newNode, 'l');
                else tmp->setPointer(newNode, 'r');
                insertFixUp(newNode);
            }
        }
        return this;
    }
};

int main() {
    fstream input, output;
    input.open("input.txt", fstream::in);
    output.open("output.txt", fstream::out);

    string type;
    int N;
    string visit;

    while (input >> type >> N >> visit) {
        if (type == "int") {
            RBT<int> *t = new RBT<int>();
            for (int i = 0; i < N; i++) {
                int value;
                input >> value;
                t->insert(value);
            }
            if (visit == "inorder") t->print(output, "in");
            else if (visit == "preorder") t->print(output, "pre");
            else if (visit == "postorder") t->print(output, "post");
        }
    }
}