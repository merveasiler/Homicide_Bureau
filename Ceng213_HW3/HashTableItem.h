#ifndef HASHTABLEITEM_H
#define HASHTABLEITEM_H

#include <iostream>

// DO NOT CHANGE THIS FILE.

template <class T>
class HashTableItem {
public:
    std::string key;
    T value;
    bool deleted;
    bool active;

    HashTableItem() : key(), value(), deleted(false), active(false) {}

    friend std::ostream& operator<<(std::ostream& os, const HashTableItem& item) {
        os << "key: " << (item.key == "" ? "empty" : item.key) << " | ";
        os << "value: " << item.value << " | ";
        os << "deleted: " << (item.deleted ? "true" : "false") << " | ";
        os << "active: " << (item.active ? "true" : "false");

        return os;
    }
};

#endif //HASHTABLEITEM_H
