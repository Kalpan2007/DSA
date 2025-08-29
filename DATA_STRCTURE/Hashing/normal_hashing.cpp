#include<iostream>
#include<vector>
#include<map>
using namespace std;

class NormalHashing {
    map<int, int> hashtable;
    int size;
public:

    // constructor
    NormalHashing(int s) {
        size = s;
    }

    // hash function - simple modulo
    int hashfunction(int key) {
        return key % size;
    }

    // insert function 
    void insert(int key) {
        int i = hashfunction(key);
        if (hashtable.find(i) == hashtable.end()) {
            hashtable[i] = key;
        } else {
            cout << " Collision occurred for key " << key << " at index " << i << endl;
        }
    }

    // search function 
    bool search(int key) {
        int i = hashfunction(key);
        if (hashtable.find(i) != hashtable.end() && hashtable[i] == key) {
            cout << "Key " << key << " found at index " << i << endl;
            return true;
        }
        cout << "Key " << key << " not found" << endl;
        return false;
    }

    // delete function 
    void deleteKey(int key) {
        int i = hashfunction(key);
        if (hashtable.find(i) != hashtable.end() && hashtable[i] == key) {
            hashtable.erase(i);
            cout << " Deleted key " << key << " from index " << i << endl;
        } else {
            cout << " Key " << key << " not found, cannot delete" << endl;
        }
    }

    // print hash table
    void printtable() {
        cout << "\n Hash Table:" << endl;
        for (auto i : hashtable) {
            cout << "Index: " << i.first << " → Key: " << i.second << endl;
        }
    }
};

int main() {
    int m = 7; 
    NormalHashing h(m);

    // Hardcoded vector of keys
    vector<int> values = {50, 21, 58, 17};

    cout << "Inserting keys...\n";
    for (int k : values) {
        h.insert(k);
    }

    h.printtable();

    // Searching
    cout << "\n Searching keys...\n";
    h.search(21);
    h.search(99);

    // Deleting
    cout << "\n Deleting keys...\n";
    h.deleteKey(21);
    h.deleteKey(99);

    h.printtable();

    return 0;
}
