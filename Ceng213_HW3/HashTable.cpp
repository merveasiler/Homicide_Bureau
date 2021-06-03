#include "HashTable.h"

template <class T>
HashTable<T>::HashTable() {
    tableSize = 2;
    numberOfItems = 0;
    table.resize(tableSize);
}

template <class T>
void HashTable<T>::insert_nearest_free_spot(const std::string& key, const T& value) {

    int index, h1Val = hashFunction(key);
    // Find nearest free spot
    for (int i = 0; table[index].active && !table[index].deleted; i++) {
        index = (h1Val + i * hash2Function(key)) % tableSize;

    }

    //insert the key-value in there
    table[index].key = key;
    table[index].value = value;
    table[index].deleted = false;
    table[index].active = true;

    //increment the number of items
    numberOfItems++;
};

template <class T>
bool HashTable<T>::insert(const std::string& key, const T& value) {
   
    float load_factor = ((float)numberOfItems) / tableSize;

    if (load_factor >= 0.5)
        rehash();
    
    //check if key-value is already in hashtable
    if (contains(key)) {
        return false;
    }
    else {
        insert_nearest_free_spot(key, value);
        return true;
    }
}

template <class T>
bool HashTable<T>::remove(const std::string& key) {

    int h1Val = hashFunction(key);
    for (int linear_prob = 0; linear_prob < tableSize; linear_prob++) {
        int location = (linear_prob * hash2Function(key) + h1Val) % tableSize;
        if ((table[location].key == key) && (table[location].deleted == false) && (table[location].active == true)) {
            table[location].deleted = true;
            numberOfItems--;
            return true;
        }
    }

    return false;
}

template <class T>
bool HashTable<T>::contains(const std::string& key) const {
    is_found = false;

    int h1Val = hashFunction(key);
    for (int linear_prob = 0; linear_prob < tableSize; linear_prob++) {
        int location = (linear_prob * hash2Function(key) + h1Val) % tableSize;
        if ((table[location].key == key) && (table[location].deleted == false) && (table[location].active == true)) {
            is_found = true;
            break;
        }
    }

    return is_found;
}

template <class T>
const HashTableItem<T>* HashTable<T>::find(const std::string& key) const {
    const HashTableItem<T>* current = NULL;

    int h1Val = hashFunction(key);
    for (int linear_prob = 0; linear_prob < tableSize; linear_prob++) {
        int location = (linear_prob * hash2Function(key) + h1Val) % tableSize;
        if ((table[location].key == key) && (table[location].deleted == false) && (table[location].active == true)) {
            current = &table[location];
            break;
        }
    }

    return current;
}

template <class T>
int HashTable<T>::getTableSize() const {
    return tableSize;
}

template <class T>
int HashTable<T>::getNumberOfItems() const {
    return number_of_items;
}

template <class T>
int HashTable<T>::hashFunction(const std::string& key) const {
    // Hash function that calculates the integer hash code corresponding to the given key string.
    // It maps the given key string to an integer value from 0 to (tableSize - 1).

    int h = pow(key.length(), 2) % tableSize;

    if (h < 0) {
        // in case overflows occurs
        h += tableSize;
    }

    return h;
}

template <class T>
int HashTable<T>::hash2Function(const std::string& key) const {
    int H2_CONST = 5;
    return (H2_CONST - key.length() % H2_CONST);
}

template <class T>
void HashTable<T>::rehash() {
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

    //std::cout << "rehash";
    //create a temporary hashtable by copying actual one
    HashTable temp_hash;
    temp_hash.table = table;
    //resize it
    temp_hash.table.resize(new_size);
    temp_hash.tableSize = new_size;

    //inactivate all the copied values, now it is a empt table
    for (int i = 0; i < tableSize; i++)
        temp_hash.table[i].active = false;

    //rearrange numberofItems and insert all the items in actual one 

    temp_hash.numberOfItems = 0;

    for (int i = 0; i < tableSize; i++) {
        if (table[i].active && !table[i].deleted) {
            temp_hash.insert_nearest_free_spot(table[i].key, table[i].value);
        }
    }

    //copy all the values in temp hashtable into our resized actual hashtable
    table.resize(new_size);
    tableSize = new_size;
    table = temp_hash.table;

}

template <class T>
void HashTable<T>::print() {
    // Prints whole hash table.

    std::cout << "HashTable (tableSize=" << tableSize << " and numberOfItems=" << numberOfItems << ") <<--" << std::endl;

    for (int i = 0; i < tableSize; ++i) {
        std::cout << table[i] << std::endl;
    }

    std::cout << "-->>" << std::endl;
}
