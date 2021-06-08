#ifndef HASHTABLEITEM_H
#define HASHTABLEITEM_H

#include <iostream>
#include <string>

using namespace std;

// DO NOT CHANGE THIS FILE.

template <class Key, class Value>
class HashTableItem {

    template <class K, class V> friend class HashTable;
private:
    Key key;
    Value value;
    bool deleted;
    bool active;

public:
    HashTableItem() : key(), value(), deleted(false), active(false) {}
    HashTableItem(const Key& k, const Value& v, bool d = false, bool a = false) : key(k), value(v), deleted(d), active(a) {}

    const Value& getValue() const { return value; };
    const Key& getKey() const { return key; };
    void setValue(Value& value) { this->value = value; };
    void setKey(Key& key) { this->key = key; };

    friend ostream& operator<<(ostream& os, const HashTableItem& item) {
        os << "key: " << (item.key == "" ? "empty" : item.key) << " | ";
        os << "value: " << item.value << " | ";
        os << "deleted: " << (item.deleted ? "true" : "false") << " | ";
        os << "active: " << (item.active ? "true" : "false");

        return os;
    }
};

#endif //HASHTABLEITEM_H
