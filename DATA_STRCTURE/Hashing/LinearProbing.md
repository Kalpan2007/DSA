# README — Linear Probing Hash Table (C++)

## Overview

This document explains a simple **Linear Probing** hash table implementation in C++ (the version you wrote with `map<int,int>` as the underlying storage). It contains:

* A short definition and formula for linear probing.
* Why we chose this approach in this example.
* A function-by-function explanation with the exact code snippets and a step-by-step explanation of the logic.
* Example run / expected output.
* Notes, complexity, and recommended improvements.

This README is written so you (or anyone reading your code) can quickly understand *how* each function works and *why* certain decisions were made.

---

# 1. Definition & formula

**Linear probing** is a collision-resolution technique used in open-addressed hash tables. When a key hashes to a slot that's already occupied, linear probing searches the table sequentially (linearly) for the next available slot.

**Basic hash formula:**

```
h(k) = k % m
```

where `m` is the table size and `k` is the key.

**Probe sequence (i-th probe):**

```
h_i(k) = (h(k) + i) % m     // i = 0,1,2,...
```

That means: start at `h(k)` and check `h(k)`, `h(k)+1`, `h(k)+2`, ... (wrapping around using modulo) until you find an empty slot or circle back to the start.

**When to use linear probing?**

* Simple to implement and cache-friendly (keys placed close together in memory).
* But suffers from "primary clustering": long runs of filled slots can form and slow insert/search.

---

# 2. Why this implementation (quick rationale)

* You used `map<int,int>` as the backing store. That makes the table *sparse*: only indices that were used are stored. (Note: `std::map` lookups are `O(log n)` instead of `O(1)`.)
* We use a special marker value `-2` to represent a *deleted* slot (a tombstone). That preserves the probe chain for keys inserted after the deleted slot.
* Naming and style: everything is lowercase (class `linearprobing`, functions `hashfunction`, `insert`, etc.) and the index variable is `i` with a `mainindex` variable storing the original hash — this is your consistent style request.

---

# 3. The code structure (members)

```cpp
class linearprobing {
    map<int, int> hashtable; // index -> key (sparse storage)
    int size;
    ...
};
```

* `hashtable`: `map<int,int>` that maps index -> stored key.
* `size`: the table capacity `m` used by `% size`.

---

# 4. Function-by-function explanation (code + line-by-line)

> All code snippets below match the lowercase styling and `i` / `mainindex` naming used in your final code.

## 4.1 Constructor

```cpp
linearprobing(int m) {
    size = m;
}
```

**What it does:**

* Stores the table capacity `m` into the member `size`.
* `hashtable` (the `map`) is default constructed and empty.

**Why:**

* We need `size` to compute the hash (`key % size`). No allocation for slots is required because we use `map`.

## 4.2 hashfunction

```cpp
int hashfunction(int key) {
    return key % size;
}
```

**What it does:**

* Computes the base hash index `mainindex = h(k)` using modulo.

**Notes:**

* This is the simplest hash function for integers. For negative keys you may want `((key % size) + size) % size` to guarantee non-negative index.
* Choosing `size` as a prime number often reduces clustering for some key distributions.

## 4.3 insert

```cpp
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
```

**Step-by-step explanation:**

1. Compute `mainindex = hashfunction(key)` — the starting index.
2. Set `i = mainindex`. `i` is the current probe index.
3. Enter `do { ... } while (i != mainindex);` to ensure we check every slot at most once and stop if we return to the start.
4. Inside the loop, we check `if (hashtable.find(i) == hashtable.end() || hashtable[i] == -2)`:

   * `hashtable.find(i) == hashtable.end()` means the index `i` has never been used before (empty slot).
   * `hashtable[i] == -2` means the index `i` was used but then deleted (a tombstone) — we can reuse it.
5. If the slot is usable, store `key` in `hashtable[i]` and return.
6. Otherwise increment `i = (i + 1) % size` to probe the next index, wrapping with `% size`.
7. If the loop finishes (we returned to `mainindex`), the table is full — print a message.

**Why this logic?**

* We use `map` so empty slots are represented by the absence of the key `i` in `hashtable`. That makes the `find` check reliable to know if the slot was never occupied.
* Tombstone (`-2`) is required because erasing that index from the map would make it *appear* empty — and that would incorrectly terminate a search for keys placed later in the probe chain.

**Trade-offs:**

* Using `map` makes each `find`/`operator[]` `O(log n)` (tree operations) rather than O(1) array indexing. But it's convenient for sparse demonstration and avoids allocating a vector upfront.

## 4.4 search

```cpp
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
```

**Step-by-step explanation:**

1. Start at `mainindex = h(k)` and set `i = mainindex`.
2. Loop over the probe sequence.
3. If `hashtable.find(i) == hashtable.end()` — the slot `i` has never been used, so the key cannot be in the table (we can stop early).
4. If `hashtable[i] == key` — key found; return true.
5. Otherwise continue probing: `i = (i + 1) % size`.
6. If we wrap back to the `mainindex` the key is not present.

**Why the early stop on `find(i) == end()`?**

* If we see a slot that was never used, there cannot be any key further in the probe sequence that originated from `mainindex` (because insertion would have placed a key in the first unused spot it saw). So the search can stop early.

**Note about tombstones:**

* When encountering a tombstone (`-2`) we cannot stop — tombstones are stored in the map, so `find(i) != end()` and the code will continue probing, which is correct.

## 4.5 remove

```cpp
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
```

**Step-by-step explanation:**

1. Compute the starting index and set `i`.
2. Probe until you find an unused slot (end) or come full circle.
3. If you reach a slot that has never been used (`find(i) == end()`), the key is not present — return.
4. If `hashtable[i] == key` — set `hashtable[i] = -2` to mark as deleted (tombstone) and return.

**Why mark deleted (`-2`) instead of erasing?**

* If you erase the map entry entirely, it will look like an unused slot to future searches and insertions — but removing the slot would break probe chains for keys that were inserted after this deleted slot. Using a tombstone preserves correctness of searches for those later keys.

**Alternative approaches:**

* Reinsert (rehash) elements in the cluster after removal to eliminate tombstones (costly but removes tombstones).
* Use an array/vector with a separate boolean `used[]` and `deleted[]` arrays.

## 4.6 display

```cpp
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
```

**What it does:**

* Iterates 0..`size-1` and prints whether each index is empty, deleted, or contains a key.
* Uses `hashtable.find(i) == end()` to test "never used".

## 4.7 main (example usage)

```cpp
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
```

**What `main` shows:**

* How to instantiate and use the class. It exercises insert, display, search and remove.

---

# 5. Example run (expected console output)

With the inserted keys and `m = 7` the insertions will go like:

* `50 % 7 = 1` → index 1
* `21 % 7 = 0` → index 0
* `58 % 7 = 2` → index 2
* `17 % 7 = 3` → index 3
* `28 % 7 = 0` → collision → probes 0,1,2,3 → index 4
* `35 % 7 = 0` → probes 0..4 → index 5

Sample console output (matching the lowercase log messages):

```
inserting keys...
inserted 50 at index 1
inserted 21 at index 0
inserted 58 at index 2
inserted 17 at index 3
inserted 28 at index 4
inserted 35 at index 5

hash table (linear probing with map):
0 --> 21
1 --> 50
2 --> 58
3 --> 17
4 --> 28
5 --> 35
6 --> [empty]

searching keys...
key 21 found at index 0
key 99 not found!

deleting keys...
key 21 deleted from index 0
key 99 not found, cannot delete!

hash table (linear probing with map):
0 --> [deleted]
1 --> 50
2 --> 58
3 --> 17
4 --> 28
5 --> 35
6 --> [empty]
```

---

# 6. Complexity & behavior notes

* **Algorithmic complexity (conceptual for array-backed open addressing):**

  * Average `insert` / `search` / `delete`: O(1) if load factor is low.
  * Worst-case: O(n) when table is nearly full or heavy clustering occurs.

* **This implementation's complexity with `std::map`:**

  * Each `find()` and `operator[]` on `std::map` is `O(log t)` where `t` is the number of stored indices — not ideal for performance but fine for teaching and sparse cases.

* **Why tombstones matter:**

  * Without tombstones, removing an element by erasing its index will create a false empty slot and break searches for elements in the same cluster.

* **Load factor:**

  * With open addressing, keep load factor < \~0.7 for decent performance. When exceeded, resize and rehash.

---

# 7. Common pitfalls & suggested improvements

1. **Use `vector<int>` for O(1) access:**

   * If you want realistic performance, use `vector<int>` (or `vector<optional<int>>`) sized `m` and use a special sentinel (e.g., `INT_MIN`) or a separate `state[]` to track empty/occupied/deleted.

2. **Dynamic resizing & rehashing:**

   * When load factor grows too large, create a new bigger table (preferably with prime size) and reinsert all existing non-deleted keys.

3. **Avoid magic number `-2`:**

   * Use an `enum { EMPTY = INT_MIN, DELETED = INT_MIN+1 }` or `std::optional<int>` to make intent clear and avoid accidental collisions with legitimate keys.

4. **Better hashing for non-integers:**

   * For string or custom types, use `std::hash<T>` and compress with `% size`.

5. **Cluster handling (tombstone cleanup):**

   * After many deletes, tombstones may slow down probing. You can periodically rehash to a new table to clear tombstones.

---

# 8. Final notes

* This README explains the code you wrote with emphasis on why each check exists and why `-2` tombstones are used. The code is excellent for learning the algorithm and seeing linear probing behavior; if you want production-level performance, switch to `vector`/`optional` + resizing and avoid `std::map` for the main table.

* If you want, I can:

  * Convert this README to Hinglish (as you often prefer), or
  * Produce a version that shows the exact full code file and compilation instructions, or
  * Convert the implementation to a `vector<int>`/`optional<int>` version with automatic rehashing.

Tell me which of these you'd like next and I will update the document.
