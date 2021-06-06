#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>

#include "HashTableItem.h"

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
    void print();

private: // DO NOT CHANGE THIS PART.
    vector<HashTableItem<Key, Value> > table;

    int tableSize;
    int numberOfItems;

    int hashFunction(const Key& key) const;
    int hashFunction2(const Key& key) const;
    void rehash();

    // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS BELOW:
    void insert_nearest_free_spot(const Key& key, const Value& value)
};

#endif //HASHTABLE_H

template <class Key, class Value>
void HashTable<Key, Value>::print() {
    // Prints whole hash table.

    cout << "HashTable (tableSize=" << tableSize << " and numberOfItems=" << numberOfItems << ") <<--" << endl;

    for (int i = 0; i < tableSize; ++i) {
        cout << table[i] << endl;
    }

    cout << "-->>" << endl;
}