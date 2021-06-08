#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashTableItem.h"

#include <iostream>
#include <vector>

const int primeNumbers[] = { 2, 5, 11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437 };

template <class Key, class Value>
class HashTable {

public: // DO NOT CHANGE THIS PART.

    HashTable();
    bool insert(const Key& key, const Value& value);
    bool remove(const Key& key);
    bool contains(const Key& key) const;
    const HashTableItem<Key, Value>* find(const Key& key) const;
    int getTableSize() const;
    int getNumberOfItems() const;
    void print() {
        // Prints whole hash table.
        cout << "HashTable (tableSize=" << tableSize << " and numberOfItems=" << numberOfItems << ") <<--" << endl;
        for (int i = 0; i < tableSize; ++i)
            cout << table[i] << endl;
        cout << "-->>" << endl;
    }

private: // DO NOT CHANGE THIS PART.
    vector<HashTableItem<Key, Value> > table;

    int tableSize;
    int numberOfItems;

    int hashFunction(const Key& key) const;
    int hashFunction2(int key) const;
    void rehash();

    // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS BELOW:
    bool insert_nearest_free_spot(const Key& key, const Value& value);
    HashTableItem<Key, Value>* bring(const Key& key);
};

#endif //HASHTABLE_H
