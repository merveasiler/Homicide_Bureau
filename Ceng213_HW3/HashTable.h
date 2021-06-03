#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>

#include "HashTableItem.h"

template <class T>
class HashTable {
public: // DO NOT CHANGE THIS PART.
    HashTable();

    bool insert(const std::string& key, const T& value);
    bool remove(const std::string& key);
    bool contains(const std::string& key) const;
    const HashTableItem<T>* find(const std::string& key) const;
    int getTableSize() const;
    int getNumberOfItems() const;
    void print();

private: // DO NOT CHANGE THIS PART.
    std::vector<HashTableItem<T> > table;

    int tableSize;
    int numberOfItems;

    int hashFunction(const std::string& key) const;
    int hash2Function(const std::string& key) const;
    void rehash();

    // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS BELOW:
    void insert_nearest_free_spot(const std::string& key, const T& value)
};

#endif //HASHTABLE_H
