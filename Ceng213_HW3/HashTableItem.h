#ifndef HASHTABLEITEM_H
#define HASHTABLEITEM_H

#include <iostream>
#include <string>

using namespace std;

// DO NOT CHANGE THIS FILE.

template <class Key, class Value>
class HashTableItem {
    friend class HashTable;
private:
    Key key;
    Value value;
    bool deleted;
    bool active

public:
    HashTableItem() : key(), value(), deleted(false), active(false) {}

    friend ostream& operator<<(ostream& os, const HashTableItem& item) {
        os << "key: " << (item.key == "" ? "empty" : item.key) << " | ";
        os << "value: " << item.value << " | ";
        os << "deleted: " << (item.deleted ? "true" : "false") << " | ";
        os << "active: " << (item.active ? "true" : "false");

        return os;
    }
};

#endif //HASHTABLEITEM_H
