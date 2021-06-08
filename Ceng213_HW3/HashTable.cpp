#include "HashTable.h"

template <class Key, class Value>
HashTable<Key, Value>::HashTable() {
    tableSize = 2;
    numberOfItems = 0;
    table.resize(tableSize);
}

template <class Key, class Value>
bool HashTable<Key, Value>::insert_nearest_free_spot(const Key& key, const Value& value) {

    int h1Val = hashFunction(key);
    int index = h1Val % tableSize;

    // Find nearest free spot
    for (int i = 0; table[index].active && !table[index].deleted; i++) {
        index = (h1Val + i * hashFunction2(h1Val)) % tableSize;
        if (i > 0 && hashFunction2(h1Val) == 0)
            return false;
    }

    //insert the key-value in there
    table[index].key = key;
    table[index].value = value;
    table[index].deleted = false;
    table[index].active = true;

    //increment the number of items
    numberOfItems++;
    return true;
};

template <class Key, class Value>
bool HashTable<Key, Value>::insert(const Key& key, const Value& value) {

    float load_factor = ((float)numberOfItems) / tableSize;

    //check if key-value is already in hashtable
    HashTableItem<Key, Value>* found = bring(key);
    if (found == NULL) {
        if (load_factor >= 0.5)
            rehash();
        if (insert_nearest_free_spot(key, value))
            return true;
        return false;
    }
    else {
        if (found->value == value)
            return false;
        found->value = value;
        return true;
    }
}

template <class Key, class Value>
bool HashTable<Key, Value>::remove(const Key& key) {

    int h1Val = hashFunction(key);
    for (int linear_prob = 0; linear_prob < tableSize; linear_prob++) {
        int location = (linear_prob * hashFunction2(h1Val) + h1Val) % tableSize;
        if ((table[location].key == key) && (table[location].deleted == false) && (table[location].active == true)) {
            table[location].deleted = true;
            numberOfItems--;
            return true;
        }
    }

    return false;
}

template <class Key, class Value>
bool HashTable<Key, Value>::contains(const Key& key) const {

    int h1Val = hashFunction(key);
    for (int linear_prob = 0; linear_prob < tableSize; linear_prob++) {
        int location = (linear_prob * hashFunction2(h1Val) + h1Val) % tableSize;
        if ((table[location].key == key) && (table[location].deleted == false) && (table[location].active == true))
            return true;
    }

    return false;
}

template <class Key, class Value>
const HashTableItem<Key, Value>* HashTable<Key, Value>::find(const Key& key) const {

    int h1Val = hashFunction(key);
    for (int linear_prob = 0; linear_prob < tableSize; linear_prob++) {
        int location = (linear_prob * hashFunction2(h1Val) + h1Val) % tableSize;
        if ((table[location].key == key) && (table[location].deleted == false) && (table[location].active == true))
            return &table[location];
    }

    return NULL;
}

template <class Key, class Value>
HashTableItem<Key, Value>* HashTable<Key, Value>::bring(const Key& key) {

    int h1Val = hashFunction(key);
    for (int linear_prob = 0; linear_prob < tableSize; linear_prob++) {
        int location = (linear_prob * hashFunction2(h1Val) + h1Val) % tableSize;
        if ((table[location].key == key) && (table[location].deleted == false) && (table[location].active == true))
            return &table[location];
    }

    return NULL;
}

template <class Key, class Value>
int HashTable<Key, Value>::getTableSize() const {
    return tableSize;
}

template <class Key, class Value>
int HashTable<Key, Value>::getNumberOfItems() const {
    return numberOfItems;
}

template <class Key, class Value>
int HashTable<Key, Value>::hashFunction(const Key& key) const {
    // Hash function that calculates the integer hash code corresponding to the given key string.
    // It maps the given key string to an integer value from 0 to (tableSize - 1).

    int length = key.length();
    int newK = 0;
    for (int i = 0; i < length; i++)
        newK += (int)key[i];

    return (newK % tableSize);
}

template <class Key, class Value>
int HashTable<Key, Value>::hashFunction2(int key) const {

    int h2Val = (key * tableSize - 1) % tableSize;
    if (h2Val < 0)
        return h2Val + tableSize;
}

template <class Key, class Value>
void HashTable<Key, Value>::rehash() {
    // You will use these prime numbers while rehashing.
    // You will not be asked to expand your hash table further.

    int new_size;
    for (int i = 0; i < 15; i++) {
        if (tableSize == primeNumbers[i]) {
            new_size = primeNumbers[i + 1];
            break;
        }
    }

    //create a temporary hashtable by copying actual one
    HashTable temp_hash;
    temp_hash.table = table;
    //resize it
    temp_hash.table.resize(new_size);
    temp_hash.tableSize = new_size;

    //inactivate all the copied values, now it is a empty table
    for (int i = 0; i < tableSize; i++)
        temp_hash.table[i].active = false;

    //rearrange numberofItems and insert all the items in actual one 

    temp_hash.numberOfItems = 0;

    for (int i = 0; i < tableSize; i++) {
        if (table[i].active && !table[i].deleted)
            temp_hash.insert_nearest_free_spot(table[i].key, table[i].value);
    }

    //copy all the values in temp hashtable into our resized actual hashtable
    table.resize(new_size);
    tableSize = new_size;
    table = temp_hash.table;

}

