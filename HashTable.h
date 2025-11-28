#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../../pr1/PRA_2526_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {
private:
    int n;
    int max;
    ListLinked<TableEntry<V>>* table;

    int h(std::string key) {
        int sum = 0;
        for (char c : key) sum += static_cast<int>(c);
        return sum % max;
    }

public:
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable() {
        delete[] table;
    }

    int capacity() {
        return max;
    }

    int entries() override {
        return n;
    }

    void insert(std::string key, V value) override {
        int idx = h(key);
        TableEntry<V> entry(key, value);
        if (table[idx].search(entry) != -1) {
            throw std::runtime_error("Clave duplicada: " + key);
        }
        table[idx].insert(0, entry);
        n++;
    }

    V search(std::string key) override {
        int idx = h(key);
        TableEntry<V> entry(key);
        int pos = table[idx].search(entry);
        if (pos == -1) throw std::runtime_error("Clave no encontrada: " + key);
        return table[idx].get(pos).value;
    }

    V remove(std::string key) override {
        int idx = h(key);
        TableEntry<V> entry(key);
        int pos = table[idx].search(entry);
        if (pos == -1) throw std::runtime_error("Clave no encontrada: " + key);
        V val = table[idx].get(pos).value;
        table[idx].remove(pos);
        n--;
        return val;
    }

    V operator[](const std::string& key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& ht) {
        for (int i = 0; i < ht.max; i++) {
            out << i << ": ";
            for (int j = 0; j < ht.table[i].size(); j++) {
                out << ht.table[i].get(j) << " ";
            }
            out << "\n";
        }
        return out;
    }
};

#endif