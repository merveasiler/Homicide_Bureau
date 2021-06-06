#include "HashTable.h"

template <class Key, class Value>
HashTable<Key, Value>::HashTable() {
    tableSize = 2;
    numberOfItems = 0;
    table.resize(tableSize);
}

template <class Key, class Value>
void HashTable<Key, Value>::insert_nearest_free_spot(const Key& key, const Value& value) {

    int index, h1Val = hashFunction(key);
    // Find nearest free spot
    for (int i = 0; table[index].active && !table[index].deleted; i++)
        index = (h1Val + i * hashFunction2(key)) % tableSize;

    //insert the key-value in there
    table[index].key = key;
    table[index].value = value;
    table[index].deleted = false;
    table[index].active = true;

    //increment the number of items
    numberOfItems++;
};

template <class Key, class Value>
bool HashTable<Key, Value>::insert(const Key& key, const Value& value) {
   
    float load_factor = ((float)numberOfItems) / tableSize;

    if (load_factor >= 0.5)
        rehash();
    
    //check if key-value is already in hashtable
    HashTableItem<Key, Value>* found = find(key);
    if (found == NULL) {
        insert_nearest_free_spot(key, value);
        return true;
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
        int location = (linear_prob * hashFunction2(key) + h1Val) % tableSize;
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
        int location = (linear_prob * hashFunction2(key) + h1Val) % tableSize;
        if ((table[location].key == key) && (table[location].deleted == false) && (table[location].active == true))
            return true;
    }

    return false;
}

template <class Key, class Value>
const HashTableItem<Key, Value>* HashTable<Key, Value>::find(const Key& key) const {
    
    int h1Val = hashFunction(key);
    for (int linear_prob = 0; linear_prob < tableSize; linear_prob++) {
        int location = (linear_prob * hash2Function(key) + h1Val) % tableSize;
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
    return number_of_items;
}

template <class Key, class Value>
int HashTable<Key, Value>::hashFunction(const Key& key) const {
    // Hash function that calculates the integer hash code corresponding to the given key string.
    // It maps the given key string to an integer value from 0 to (tableSize - 1).

    int h = pow(key.length(), 2) % tableSize;

    if (h < 0) {
        // in case overflows occurs
        h += tableSize;
    }

    return h;
}

template <class Key, class Value>
int HashTable<Key, Value>::hashFunction2(const Key& key) const {
    int H2_CONST = 5;
    return (H2_CONST - (key.length() % H2_CONST));
}

template <class Key, class Value>
void HashTable<Key, Value>::rehash() {
    // You will use these prime numbers while rehashing.
    // You will not be asked to expand your hash table further.
    const int primeNumbers[] = { 2, 5, 11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437 };

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

