# Quadratic Probing Hash Table (C++)

## 📘 Introduction

Quadratic Probing is an **open addressing collision resolution technique** used in hash tables. When a collision occurs (i.e., when two keys hash to the same index), instead of simply checking the next slot (like in Linear Probing), Quadratic Probing searches for an empty slot using a quadratic function.

### Formula:

```
index = (h(key) + i^2) % size
```

Where:

* `h(key)` = hash function (usually key % size)
* `i` = attempt number (0, 1, 2, 3...)
* `size` = size of the hash table

✅ Advantage: Quadratic probing reduces clustering compared to linear probing.

---

## ⚙️ Implementation Code (C++)

```cpp
#include<iostream>
#include<vector>
using namespace std;

class QuadraticProbingHashing {
    vector<int> hashtable;
    int size;

public:
    // constructor
    QuadraticProbingHashing(int s) {
        size = s;
        hashtable.resize(size, -1); // -1 means empty
    }

    // hash function
    int hashfunction(int key) {
        return key % size;
    }

    // insert function
    void insert(int key) {
        int index = hashfunction(key);
        int i = 0;

        while (hashtable[(index + i * i) % size] != -1 && i < size) {
            i++;
        }

        if (i < size) {
            hashtable[(index + i * i) % size] = key;
        } else {
            cout << "Hash table is full, cannot insert " << key << endl;
        }
    }

    // search function
    bool search(int key) {
        int index = hashfunction(key);
        int i = 0;

        while (hashtable[(index + i * i) % size] != -1 && i < size) {
            if (hashtable[(index + i * i) % size] == key) {
                return true;
            }
            i++;
        }
        return false;
    }

    // remove function
    void remove(int key) {
        int index = hashfunction(key);
        int i = 0;

        while (hashtable[(index + i * i) % size] != -1 && i < size) {
            if (hashtable[(index + i * i) % size] == key) {
                hashtable[(index + i * i) % size] = -1; // mark as deleted
                cout << "Key " << key << " removed." << endl;
                return;
            }
            i++;
        }
        cout << "Key " << key << " not found." << endl;
    }

    // display function
    void display() {
        for (int i = 0; i < size; i++) {
            cout << i << " --> " << hashtable[i] << endl;
        }
    }
};

int main() {
    QuadraticProbingHashing h(7);
    h.insert(10);
    h.insert(20);
    h.insert(5);
    h.insert(15);

    cout << "Hash Table:\n";
    h.display();

    cout << "Searching 15: " << (h.search(15) ? "Found" : "Not Found") << endl;
    cout << "Searching 99: " << (h.search(99) ? "Found" : "Not Found") << endl;

    h.remove(20);
    h.display();

    return 0;
}
```

---

## 🔍 Function-wise Explanation

### 1. **Constructor**

```cpp
QuadraticProbingHashing(int s) {
    size = s;
    hashtable.resize(size, -1);
}
```

* Initializes hash table with size `s`.
* `-1` is used to indicate empty slots.

### 2. **Hash Function**

```cpp
int hashfunction(int key) {
    return key % size;
}
```

* Simple modulo function.
* Ensures that key maps into valid table index.

### 3. **Insert Function**

```cpp
void insert(int key) {
    int index = hashfunction(key);
    int i = 0;

    while (hashtable[(index + i * i) % size] != -1 && i < size) {
        i++;
    }

    if (i < size) {
        hashtable[(index + i * i) % size] = key;
    } else {
        cout << "Hash table is full, cannot insert " << key << endl;
    }
}
```

* Uses quadratic probing `index + i^2`.
* If the computed slot is filled, try again with `i+1`.
* Prevents primary clustering.

### 4. **Search Function**

```cpp
bool search(int key) {
    int index = hashfunction(key);
    int i = 0;

    while (hashtable[(index + i * i) % size] != -1 && i < size) {
        if (hashtable[(index + i * i) % size] == key) {
            return true;
        }
        i++;
    }
    return false;
}
```

* Checks each quadratic probe until empty slot or found key.
* Returns `true` if key is found, else `false`.

### 5. **Remove Function**

```cpp
void remove(int key) {
    int index = hashfunction(key);
    int i = 0;

    while (hashtable[(index + i * i) % size] != -1 && i < size) {
        if (hashtable[(index + i * i) % size] == key) {
            hashtable[(index + i * i) % size] = -1; // mark as deleted
            cout << "Key " << key << " removed." << endl;
            return;
        }
        i++;
    }
    cout << "Key " << key << " not found." << endl;
}
```

* Uses quadratic probing to locate the key.
* Marks slot as deleted by resetting it to `-1`.

### 6. **Display Function**

```cpp
void display() {
    for (int i = 0; i < size; i++) {
        cout << i << " --> " << hashtable[i] << endl;
    }
}
```

* Prints index and its stored value.
* Useful for debugging.

---

## 📊 Sample Output

```
Hash Table:
0 --> -1
1 --> 15
2 --> -1
3 --> 10
4 --> -1
5 --> 5
6 --> 20

Searching 15: Found
Searching 99: Not Found
Key 20 removed.
0 --> -1
1 --> 15
2 --> -1
3 --> 10
4 --> -1
5 --> 5
6 --> -1
```

---

## ⏱️ Complexity

* **Insertion:** O(1) average, O(n) worst-case (when many probes are required)
* **Search:** O(1) average, O(n) worst-case
* **Deletion:** O(1) average

---

## ⚠️ Pitfalls

* **Secondary clustering**: Though less than linear probing, quadratic probing can still cluster keys.
* **Table Size**: Should ideally be prime to reduce collisions.
* **Full Table**: If table is full, insertion fails.

---

## 🚀 Improvements

1. Use **rehashing** when load factor > 0.7.
2. Use **lazy deletion markers** instead of `-1`.
3. Combine with **double hashing** for even better performance.
