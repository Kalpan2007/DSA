#include <iostream>
#include <vector>
using namespace std;

class DoubleHashing {
    vector<int> hashtable;
    int size;
    int prime; // for secondary hash function

public:
    // constructor
    DoubleHashing(int s) {
        size = s;
        hashtable.resize(size, -1);  // -1 means empty
        prime = getPrime();          // find nearest smaller prime for secondary hashing
    }

    // primary hash function
    int hash1(int key) {
        return key % size;
    }

    // secondary hash function
    int hash2(int key) {
        return prime - (key % prime);
    }

    // helper function: find nearest smaller prime
    int getPrime() {
        for (int i = size - 1; i >= 2; i--) {
            bool isPrime = true;
            for (int j = 2; j * j <= i; j++) {
                if (i % j == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) return i;
        }
        return 3; // fallback
    }

    // insert function
    void insert(int key) {
        int index = hash1(key);
        int step = hash2(key);

        int i = 0;
        while (hashtable[(index + i * step) % size] != -1) {
            i++;
            if (i == size) {
                cout << "Hash Table is Full! Cannot insert " << key << endl;
                return;
            }
        }
        hashtable[(index + i * step) % size] = key;
    }

    // search function
    bool search(int key) {
        int index = hash1(key);
        int step = hash2(key);

        int i = 0;
        while (hashtable[(index + i * step) % size] != -1) {
            if (hashtable[(index + i * step) % size] == key)
                return true;
            i++;
            if (i == size) return false; // full loop done
        }
        return false;
    }

    // remove function
    void remove(int key) {
        int index = hash1(key);
        int step = hash2(key);

        int i = 0;
        while (hashtable[(index + i * step) % size] != -1) {
            if (hashtable[(index + i * step) % size] == key) {
                hashtable[(index + i * step) % size] = -2; // mark deleted
                return;
            }
            i++;
            if (i == size) return;
        }
    }

    // display function
    void display() {
        for (int i = 0; i < size; i++) {
            if (hashtable[i] >= 0)
                cout << i << " --> " << hashtable[i] << endl;
            else if (hashtable[i] == -1)
                cout << i << " --> EMPTY" << endl;
            else
                cout << i << " --> DELETED" << endl;
        }
    }
};

// main function
int main() {
    DoubleHashing dh(7);

    dh.insert(49);
    dh.insert(63);
    dh.insert(56);
    dh.insert(52);
    dh.insert(54);
    dh.insert(48);

    cout << "Hash Table after insertion:\n";
    dh.display();

    cout << "\nSearch 56: " << (dh.search(56) ? "Found" : "Not Found") << endl;
    cout << "Search 100: " << (dh.search(100) ? "Found" : "Not Found") << endl;

    cout << "\nRemoving 52...\n";
    dh.remove(52);
    dh.display();

    return 0;
}
