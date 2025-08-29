#include <iostream>
#include <map>
using namespace std;

class linearprobing {
    map<int, int> hashtable; // index -> key
    int size;

public:
    // constructor
    linearprobing(int m) {
        size = m;
    }

    // hash function
    int hashfunction(int key) {
        return key % size;
    }

    // insert key
    void insert(int key) {
        int mainindex = hashfunction(key);
        int i = mainindex;

        do {
            // if slot is empty or marked deleted (-2)
            if (hashtable.find(i) == hashtable.end() || hashtable[i] == -2) {
                hashtable[i] = key;
                cout << "inserted " << key << " at index " << i << endl;
                return;
            }
            i = (i + 1) % size;
        } while (i != mainindex);

        cout << "hash table is full, cannot insert key " << key << endl;
    }

    // search key
    bool search(int key) {
        int mainindex = hashfunction(key);
        int i = mainindex;

        do {
            if (hashtable.find(i) == hashtable.end()) {
                cout << "key " << key << " not found!" << endl;
                return false;
            }
            if (hashtable[i] == key) {
                cout << "key " << key << " found at index " << i << endl;
                return true;
            }
            i = (i + 1) % size;
        } while (i != mainindex);

        cout << "key " << key << " not found!" << endl;
        return false;
    }

    // delete key
    void remove(int key) {
        int mainindex = hashfunction(key);
        int i = mainindex;

        do {
            if (hashtable.find(i) == hashtable.end()) {
                cout << "key " << key << " not found, cannot delete!" << endl;
                return;
            }
            if (hashtable[i] == key) {
                hashtable[i] = -2; // mark as deleted
                cout << "key " << key << " deleted from index " << i << endl;
                return;
            }
            i = (i + 1) % size;
        } while (i != mainindex);

        cout << "key " << key << " not found, cannot delete!" << endl;
    }

    // display table
    void display() {
        cout << "\nhash table (linear probing with map):" << endl;
        for (int i = 0; i < size; i++) {
            if (hashtable.find(i) == hashtable.end())
                cout << i << " --> [empty]" << endl;
            else if (hashtable[i] == -2)
                cout << i << " --> [deleted]" << endl;
            else
                cout << i << " --> " << hashtable[i] << endl;
        }
    }
};

int main() {
    int m = 7; // hash table size
    linearprobing h(m);

    // hardcoded values
    int values[] = {50, 21, 58, 17, 28, 35};

    cout << "inserting keys...\n";
    for (int k : values) {
        h.insert(k);
    }

    h.display();

    cout << "\nsearching keys...\n";
    h.search(21);
    h.search(99);

    cout << "\ndeleting keys...\n";
    h.remove(21);
    h.remove(99);

    h.display();

    return 0;
}
