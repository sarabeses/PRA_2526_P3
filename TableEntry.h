
#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V>
class TableEntry {
public:
    std::string key; 
    V value;    

    TableEntry() = default;

    TableEntry(const std::string& k, const V& v) : key(k), value(v) {}

    explicit TableEntry(const std::string& k) : key(k), value(V{}) {}

    friend bool operator<(const TableEntry<V>& te1, const TableEntry<V>& te2) {
        return te1.key < te2.key;
    }

    friend bool operator>(const TableEntry<V>& te1, const TableEntry<V>& te2) {
        return te1.key > te2.key; 
    }

    friend bool operator==(const TableEntry<V>& te1, const TableEntry<V>& te2) {
        return te1.key == te2.key;
    }

    friend std::ostream& operator<<(std::ostream& out, const TableEntry<V>& te) {
        out << te.key;
        return out;
    }
};

#endif 