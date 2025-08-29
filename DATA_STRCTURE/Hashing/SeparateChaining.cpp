#include <iostream>
#include <vector>
#include <map>
#include <list>
using namespace std;

class SeparateChaining
{

    map<int, list<int>> hashtable;
    int size;

public:
    // constructor
    SeparateChaining(int s)
    {
        size = s;
    }

    //  hash function - simple modulo to calculate index
    int hashfunction(int key)
    {
        return key % size;
    }

    // insert fucntion
    void insert(int key)
    {
        int i = hashfunction(key);
        hashtable[i].push_back(key);
        cout << key << " inserted at index " << i << endl;
    }

    // search function
    bool search(int key)
    {
        int i = hashfunction(key);
        for (int k : hashtable[i])
        {
            if (k == key)
            {
                cout << "Key " << key << " found at index " << i << endl;
                return true;
            }
        }
        cout << "Key " << key << " not found!" << endl;
        return false;
    }

    // delete fucntion
    void deletekey(int key)
    {
        // Step 1: Find index using hash function
        int i = hashfunction(key);

        // Step 2: Get reference to the chain (bucket) at that index
        auto &chain = hashtable[i];

        // Step 3: Traverse through the chain to find the key
        for (auto it = chain.begin(); it != chain.end(); it++)
        {
            if (*it == key) // If key is found in this chain
            {
                chain.erase(it); // Step 4: Erase the key from chain
                cout << key << " deleted from index " << i << endl;
                return;
            }
        }

        // Step 5: If key not found in this chain
        cout << "Key " << key << " not found, cannot delete!" << endl;
    }

    void printtable()
    {
        for(int i = 0;i<size;i++){
            cout << i << " : ";
            if (hashtable.find(i) != hashtable.end() && !hashtable[i].empty())
            {
                for (int k : hashtable[i])
                {
                    cout << k << " -> ";
                }
                cout << "NULL";
            }
            else
            {
                cout << "empty";
            }
            cout << endl;
             }
    }
};

int main()
{
    int m = 10; // hash table size
    SeparateChaining h(m);

    // Hardcoded keys
    int values[] = {50, 21, 58, 17, 28, 35 , 10, 5, 99, 100};

    cout << "Inserting keys...\n";
    for (int k : values)
    {
        h.insert(k);
    }

    h.printtable();

    // Searching
    cout << "\nSearching keys...\n";
    h.search(21);
    h.search(99);

    // Deleting
    cout << "\nDeleting keys...\n";
    h.deletekey(28);
    h.deletekey(99);

    h.printtable();

    return 0;
}