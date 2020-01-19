#include <iostream>
#include <vector>

using namespace std;

template<class T>
class MinHeap {
    T *arr;
    int dim, heapsize;

    int parent(int i) const { return i >> 1; }

    int left(int i) const { return i << 1; }

    int right(int i) const { return (i << 1) | 1; }

    void heapify(int i) {
        int l = left(i);
        int r = right(i);
        int min = i;
        if (l <= heapsize && (arr[l] < arr[max]))
            min = i;
        if (r <= heapsize && (arr[r] < arr[max]))
            min = r;
        if (min != i) {
            swap(i, min);
            heapify(min);
        }
    }

    void swap(int i, int j) {
        T tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

public:
    MinHeap(int dim) {
        this->dim = dim + 1;
        arr = new T[dim + 1];
        heapsize = 0;
    }

    void insert(T key) {
        if (heapsize < dim) {
            arr[++heapsize] = key;
            int tmp = heapsize;
            while (tmp > 1 && arr[tmp] < arr[parent(tmp)]) {
                swap(tmp, parent(tmp));
                tmp = parent(tmp);
            }
        }
    }

    T *extract() {
        if (heapsize > 0) {
            swap(1, heapsize);
            heapsize--;
            heapify(1);
            return arr[heapsize + 1];
        }
        return nullptr;
    }
};

template<class T>
class Node {
    T key;
    int frequency;
    Node<T> *left, *right;
public:
    Node(T key, int frequency) {
        this->key = key;
        this->frequency = frequency;
        left = right = nullptr;
    }

    void setKey(T key) { this->key = key; }

    void setFrequency(int frequency) { this->frequency = frequency; }

    void setLeft(Node<T> *left) { this->left = left; }

    void setRight(Node<T> *right) { this->right = right; }

    T getKey() const { return key; }

    int getFrequency() const { return frequency; }

    Node<T> *getLeft() const { return left; }

    Node<T> *getRight() const { return right; }
};

template<class T>
class HuffmanCode {
    Node<T> *root;
    vector<pair<T, string>> codes;

    void buildCodes(Node<T> *node, string code) {
        if (node) {
            if (node->getLeft() && node->getRight()) {
                buildCodes(node->getLeft(), code + '0');
                buildCodes(node->getRight(), code + '1');
            } else {
                for (int i = 0; i < codes.size(); i++)
                    if (node->getKey() == codes[i].first)
                        codes[i].second = code;
            }
        }
    }

public:
    HuffmanCode(T *symbols, int *frequencies, int N) {
        root = nullptr;
        MinHeap<Node<T>> h(N);
        codes = vector<pair<T, string>>(N);
        for (int i = 0; i < N; i++)
            codes[i] = pair<T, string>(symbols[i], "");
        for (int i = 0; i < N; i++) {
            Node<T> tmp = Node<T>(symbols[i], frequencies[i]);
            h.insert(tmp);
        }
        for (int i = 0; i < N; i++) {
            Node<T> *l = h.extract();
            Node<T> *r = h.extract();
            Node<T> sum = Node<T>('\0', l->getFrequency() + r->getFrequency());
            sum.setLeft(l);
            sum.setRight(r);
            h.insert(sum);
        }
        root = h.extract();
        buildCodes(root, "");
    }

    vector<pair<T, string>> &getCodes() { return codes; }

    string encode(string &str) {
        string res = "";
        for (int i = 0; i < str.length(); i++) {
            int j = 0;
            while (j < codes.size() && (codes[i].first != str[i])) j++;
            if (j != codes.size()) res.append(codes[i].first);
        }
        return res;
    }

    string decode(string &str) {
        string res = "";
        string tmp = "";
        int i = 0;
        while (i < str.size()) {
            tmp += str[i];
            for (int j = 0; j < codes.size(); j++) {
                if (tmp == codes[j].second) {
                    res += codes[j].first;
                    tmp = "";
                    break;
                }
            }
            i++;
        }
        return res;
    }
};

int main() {
}