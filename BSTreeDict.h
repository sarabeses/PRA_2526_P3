
#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include <string>

#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>> bst;

public:
    BSTreeDict() = default;
    ~BSTreeDict() = default;

    int entries() override {
        return bst.size();
    }

    void insert(std::string key, V value) override {
        bst.insert(TableEntry<V>(key, value));
    }

    V search(std::string key) override {
        TableEntry<V> q(key);
        TableEntry<V> found = bst.search(q);
        return found.value;
    }

    V remove(std::string key) override {
        TableEntry<V> q(key);
        V val = bst.search(q).value;
        bst.remove(q);
        return val;
    }

    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& dict) {
        out << dict.bst;
        return out;
    }
};

#endif // BSTREEDICT_H

