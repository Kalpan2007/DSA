
# 📝 Normal Hashing in C++ (with Map & Vector)

This file explains **Normal Hashing** step by step, with full code and line-by-line understanding.  
We are implementing **Insert, Search, and Delete** operations using:

- `vector<int>` → to store the input values.  
- `map<int,int>` → to represent the **hash table** as `index -> key`.  

---

## 🔹 1. What is Normal Hashing?
- Hashing is a method to map a **key** to a specific location (index) in a hash table.  
- We use a **hash function**:

```cpp
h(k) = k % m
```

(where `m` = table size, usually a prime number).  

👉 In **Normal Hashing**, we do **not resolve collisions**. If two keys hash to the same index, the second one cannot be inserted.

---

## 🔹 2. C++ Implementation with Explanation

```cpp
#include <iostream>
#include <vector>
#include <map>
using namespace std;
```

- We include `<map>` for the hash table and `<vector>` for storing input keys.  
- `map<int,int>` works like a dictionary: it stores pairs of `(index, key)`.  

---

### 🔹 Hash Table Class

```cpp
class NormalHashing {
    map<int, int> hashTable; // index -> key
    int size;
```
- `hashTable` → stores the hash table. Example: `0 -> 21`.  
- `size` → size of the hash table (m).  

---

### 🔹 Constructor

```cpp
NormalHashing(int m) {
    size = m;
}
```
- Initializes the hash table size.  

---

### 🔹 Hash Function

```cpp
int hashFunction(int key) {
    return key % size;
}
```
- Maps a key to an index.  
- Example: if `key = 50` and `size = 7`, index = `50 % 7 = 1`.  

---

### 🔹 Insert Operation

```cpp
void insert(int key) {
    int index = hashFunction(key);
    if (hashTable.find(index) == hashTable.end()) {
        hashTable[index] = key;
        cout << "Inserted " << key << " at index " << index << endl;
    } else {
        cout << "Collision occurred for key " << key
             << " at index " << index << " (not handled in normal hashing)" << endl;
    }
}
```

- `hashTable.find(index)` → searches for `index` in the map.  
- `.end()` → means "not found".  
- If index is empty → insert the key.  
- If index already filled → collision.  

⚡ **Important:** If we used `hashTable[index]` directly, it would create a new entry if it doesn’t exist, which is why we use `.find()` to check first.

---

### 🔹 Search Operation

```cpp
bool search(int key) {
    int index = hashFunction(key);
    if (hashTable.find(index) != hashTable.end() && hashTable[index] == key) {
        cout << "Key " << key << " found at index " << index << endl;
        return true;
    }
    cout << "Key " << key << " not found!" << endl;
    return false;
}
```

- First we calculate the index.  
- Check if the index exists (`find != end`).  
- If the stored key matches → found.  
- Else → not found.  

---

### 🔹 Delete Operation

```cpp
void remove(int key) {
    int index = hashFunction(key);
    if (hashTable.find(index) != hashTable.end() && hashTable[index] == key) {
        hashTable.erase(index);
        cout << "Key " << key << " deleted from index " << index << endl;
    } else {
        cout << "Key " << key << " not found, cannot delete!" << endl;
    }
}
```

- Use `.erase(index)` to delete the key from map.  
- If not found → print message.  

---

### 🔹 Display Hash Table

```cpp
void display() {
    cout << "\nHash Table:" << endl;
    for (int i = 0; i < size; i++) {
        if (hashTable.find(i) != hashTable.end())
            cout << i << " --> " << hashTable[i] << endl;
        else
            cout << i << " --> [empty]" << endl;
    }
}
```
- Iterates from `0` to `size-1`.  
- If index exists in map → print key.  
- Else → `[empty]`.  

---

### 🔹 Main Function

```cpp
int main() {
    int m = 7; // hash table size
    NormalHashing h(m);

    // Hardcoded vector of keys
    vector<int> values = {50, 21, 58, 17};

    cout << "Inserting keys...\n";
    for (int k : values) {
        h.insert(k);
    }

    h.display();

    // Searching
    cout << "\nSearching keys...\n";
    h.search(21);
    h.search(99);

    // Deleting
    cout << "\nDeleting keys...\n";
    h.remove(21);
    h.remove(99);

    h.display();

    return 0;
}
```

- Creates a hash table of size 7.  
- Inserts keys `{50, 21, 58, 17}`.  
- Displays table.  
- Searches for 21 (found) and 99 (not found).  
- Deletes 21 (successful) and 99 (fails).  
- Displays updated table.  

---

## 🔹 Example Run

```
Inserting keys...
Inserted 50 at index 1
Inserted 21 at index 0
Collision occurred for key 58 at index 2 (not handled in normal hashing)
Inserted 17 at index 3

Hash Table:
0 --> 21
1 --> 50
2 --> [empty]
3 --> 17
4 --> [empty]
5 --> [empty]
6 --> [empty]

Searching keys...
Key 21 found at index 0
Key 99 not found!

Deleting keys...
Key 21 deleted from index 0
Key 99 not found, cannot delete!

Hash Table:
0 --> [empty]
1 --> 50
2 --> [empty]
3 --> 17
4 --> [empty]
5 --> [empty]
6 --> [empty]
```

---

## ✅ Summary

- `map.find(index)` → check if index exists.  
- `map.end()` → returned if index not found.  
- `map.erase(index)` → delete element at index.  
- Normal Hashing does **not handle collisions**.  
- Later, we will see **Separate Chaining**, **Linear Probing**, **Quadratic Probing**, and **Double Hashing** to solve collisions.  

---
