# Double Hashing in C++

## 📌 Definition

Double Hashing is an **open addressing collision resolution technique** used in hashing. When a collision occurs, instead of just probing linearly or quadratically, **Double Hashing uses a second hash function to calculate the step size for probing**.

This ensures that collisions are resolved more effectively and avoids the primary/secondary clustering problem of linear and quadratic probing.

---

## 📌 Formula

For inserting/searching:

```
index = (hash1(key) + i * hash2(key)) % tableSize
```

* `hash1(key)` → primary hash function.
* `hash2(key)` → secondary hash function.
* `i` → number of attempts (0,1,2,...).
* `tableSize` → size of the hash table.

⚡ The main requirement: `hash2(key)` must **never evaluate to 0** and should be **relatively prime to tableSize**.

---

## 📌 Why Double Hashing?

* Avoids **clustering** issues that arise in Linear and Quadratic Probing.
* Provides a **better spread** of keys in the table.
* Considered one of the **best open addressing techniques** for collision resolution.

---

## 📌 Implementation in C++

```cpp
#include<iostream>
#include<vector>
using namespace std;

class DoubleHashing {
    vector<int> hashtable;
    int size;
    int prime;

public:
    // Constructor
    DoubleHashing(int s) {
        size = s;
        hashtable.resize(size, -1); // initialize table with -1
        prime = getPrime(); // for secondary hash function
    }

    // Primary hash function
    int hash1(int key) {
        return key % size;
    }

    // Secondary hash function
    int hash2(int key) {
        return prime - (key % prime);
    }

    // Utility function to find prime smaller than table size
    int getPrime() {
        for (int i = size - 1; i >= 1; i--) {
            bool isPrime = true;
            for (int j = 2; j * j <= i; j++) {
                if (i % j == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime)
                return i;
        }
        return 3;
    }

    // Insert function
    void insert(int key) {
        int index = hash1(key);

        if (hashtable[index] == -1) {
            hashtable[index] = key;
            return;
        }

        int stepSize = hash2(key);
        int i = 1;
        while (true) {
            int newIndex = (index + i * stepSize) % size;
            if (hashtable[newIndex] == -1) {
                hashtable[newIndex] = key;
                return;
            }
            i++;
            if (i == size) {
                cout << "Hash table is full! Cannot insert key: " << key << endl;
                return;
            }
        }
    }

    // Search function
    bool search(int key) {
        int index = hash1(key);
        int stepSize = hash2(key);
        int i = 0;

        while (i < size) {
            int newIndex = (index + i * stepSize) % size;
            if (hashtable[newIndex] == key)
                return true;
            if (hashtable[newIndex] == -1)
                return false;
            i++;
        }
        return false;
    }

    // Remove function
    void remove(int key) {
        int index = hash1(key);
        int stepSize = hash2(key);
        int i = 0;

        while (i < size) {
            int newIndex = (index + i * stepSize) % size;
            if (hashtable[newIndex] == key) {
                hashtable[newIndex] = -1; // mark as deleted
                cout << "Key " << key << " deleted.\n";
                return;
            }
            if (hashtable[newIndex] == -1)
                break;
            i++;
        }
        cout << "Key " << key << " not found.\n";
    }

    // Display function
    void display() {
        for (int i = 0; i < size; i++) {
            if (hashtable[i] != -1)
                cout << i << " --> " << hashtable[i] << endl;
            else
                cout << i << " --> Empty" << endl;
        }
    }
};

int main() {
    DoubleHashing dh(7);

    dh.insert(49);
    dh.insert(63);
    dh.insert(56);
    dh.insert(52);
    dh.insert(54);
    dh.insert(48);

    dh.display();

    cout << "Search 63: " << (dh.search(63) ? "Found" : "Not Found") << endl;
    cout << "Search 100: " << (dh.search(100) ? "Found" : "Not Found") << endl;

    dh.remove(56);
    dh.display();

    return 0;
}
```

---

## 📌 Step-by-Step Explanation

### 1. **Constructor**

```cpp
DoubleHashing(int s) {
    size = s;
    hashtable.resize(size, -1);
    prime = getPrime();
}
```

* Initializes table with `-1` (empty slots).
* Calls `getPrime()` to get the largest prime smaller than `size` (for secondary hash).

---

### 2. **Primary Hash Function**

```cpp
int hash1(int key) { return key % size; }
```

* Basic modulo function.
* Determines the base index.

---

### 3. **Secondary Hash Function**

```cpp
int hash2(int key) { return prime - (key % prime); }
```

* Ensures a non-zero step size.
* Provides better distribution of collisions.

---

### 4. **Insert Function**

```cpp
void insert(int key) {
    int index = hash1(key);
    if (hashtable[index] == -1) {
        hashtable[index] = key;
        return;
    }
    int stepSize = hash2(key);
    int i = 1;
    while (true) {
        int newIndex = (index + i * stepSize) % size;
        if (hashtable[newIndex] == -1) {
            hashtable[newIndex] = key;
            return;
        }
        i++;
        if (i == size) {
            cout << "Hash table is full! Cannot insert key: " << key << endl;
            return;
        }
    }
}
```

* Places key in calculated index.
* If collision occurs → moves in steps defined by `hash2`.
* Ensures **no clustering**.

---

### 5. **Search Function**

```cpp
bool search(int key) {
    int index = hash1(key);
    int stepSize = hash2(key);
    int i = 0;
    while (i < size) {
        int newIndex = (index + i * stepSize) % size;
        if (hashtable[newIndex] == key)
            return true;
        if (hashtable[newIndex] == -1)
            return false;
        i++;
    }
    return false;
}
```

* Starts from initial hash index.
* Uses double hashing to probe further.
* Stops when empty slot is reached or element found.

---

### 6. **Remove Function**

```cpp
void remove(int key) {
    int index = hash1(key);
    int stepSize = hash2(key);
    int i = 0;
    while (i < size) {
        int newIndex = (index + i * stepSize) % size;
        if (hashtable[newIndex] == key) {
            hashtable[newIndex] = -1;
            cout << "Key " << key << " deleted.\n";
            return;
        }
        if (hashtable[newIndex] == -1)
            break;
        i++;
    }
    cout << "Key " << key << " not found.\n";
}
```

* Searches for key using same probing sequence.
* Marks the slot as empty (`-1`).

---

### 7. **Display Function**

```cpp
void display() {
    for (int i = 0; i < size; i++) {
        if (hashtable[i] != -1)
            cout << i << " --> " << hashtable[i] << endl;
        else
            cout << i << " --> Empty" << endl;
    }
}
```

* Prints the entire table.
* Shows which indices are occupied.

---

## 📌 Why This Logic Works

* **hash1** ensures base position.
* **hash2** gives unique steps, preventing clustering.
* Combination of both ensures **uniform distribution** of keys.

Thus, Double Hashing is considered **one of the most efficient and practical open addressing methods** in real-world hash table implementations.
