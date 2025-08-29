#include <iostream>
#include <map>
using namespace std;

class quadraticprobing {
    map<int, int> hashtable; // index -> key
    int size;
    int c1, c2; // quadratic coefficients

public:
    // constructor
    quadraticprobing(int m, int c1_val = 1, int c2_val = 3) {
        size = m;
        c1 = c1_val;
        c2 = c2_val;
    }

    // hash function
    int hashfunction(int key) {
        return key % size;
    }

    // insert key
    void insert(int key) {
        int mainindex = hashfunction(key);
        
        for (int i = 0; i < size; i++) {
            int newindex = (mainindex + c1 * i + c2 * i * i) % size;

            if (hashtable.find(newindex) == hashtable.end() || hashtable[newindex] == -2) {
                hashtable[newindex] = key;
                cout << "inserted " << key << " at index " << newindex << endl;
                return;
            }
        }
        cout << "hash table is full, cannot insert key " << key << endl;
    }

    // search key
    bool search(int key) {
        int mainindex = hashfunction(key);

        for (int i = 0; i < size; i++) {
            int newindex = (mainindex + c1 * i + c2 * i * i) % size;

            if (hashtable.find(newindex) == hashtable.end()) {
                cout << "key " << key << " not found!" << endl;
                return false;
            }
            if (hashtable[newindex] == key) {
                cout << "key " << key << " found at index " << newindex << endl;
                return true;
            }
        }
        cout << "key " << key << " not found!" << endl;
        return false;
    }

    // delete key
    void remove(int key) {
        int mainindex = hashfunction(key);

        for (int i = 0; i < size; i++) {
            int newindex = (mainindex + c1 * i + c2 * i * i) % size;

            if (hashtable.find(newindex) == hashtable.end()) {
                cout << "key " << key << " not found, cannot delete!" << endl;
                return;
            }
            if (hashtable[newindex] == key) {
                hashtable[newindex] = -2; // mark as deleted
                cout << "key " << key << " deleted from index " << newindex << endl;
                return;
            }
        }
        cout << "key " << key << " not found, cannot delete!" << endl;
    }

    // display table
    void display() {
        cout << "\nhash table (quadratic probing with map):" << endl;
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
    quadraticprobing h(m);

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
