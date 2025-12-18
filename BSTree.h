#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    int nelem;
    BSNode<T>* root;

    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr) {
            throw std::runtime_error("BSTree::search: elemento no encontrado");
        }
        if (e < n->elem) {
            return search(n->left, e);
        } else if (e > n->elem) {
            return search(n->right, e);
        } else {
            return n;
        }
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            nelem++;
            return new BSNode<T>(e);
        }
        if (e < n->elem) {
            n->left = insert(n->left, e);
        } else if (e > n->elem) {
            n->right = insert(n->right, e);
        } else {
            throw std::runtime_error("BSTree::insert: elemento ya existente");
        }
        return n;
        }

    void print_inorder(std::ostream &out, BSNode<T>* n) const {
        if (n == nullptr) return;
        print_inorder(out, n->left);
        out << n->elem << ' ';
        print_inorder(out, n->right);
    }

    T max(BSNode<T>* n) const {
        if (n == nullptr) {
            throw std::runtime_error("BSTree::max: subárbol vacío");
        }
        while (n->right != nullptr) {
            n = n->right;
        }
        return n->elem;
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n == nullptr) {
            throw std::runtime_error("BSTree::remove_max: subárbol vacío");
        }
        if (n->right == nullptr) {
            BSNode<T>* left_sub = n->left;
            delete n;
            nelem--;
            return left_sub;
        }
        n->right = remove_max(n->right);
        return n;
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (n == nullptr) {
            throw std::runtime_error("BSTree::remove: elemento no existente");
        }
        if (e < n->elem) {
            n->left = remove(n->left, e);
            return n;
        } else if (e > n->elem) {
            n->right = remove(n->right, e);
            return n;
        } else {
            if (n->left == nullptr && n->right == nullptr) {
                delete n;
                nelem--;
                return nullptr;
            } else if (n->left == nullptr) {
                BSNode<T>* r = n->right;
                delete n;
                nelem--;
                return r;
            } else if (n->right == nullptr) {
                BSNode<T>* l = n->left;
                delete n;
                nelem--;
                return l;
            } else {
                T pred = max(n->left);
                n->elem = pred;
                n->left = remove_max(n->left);
                return n;
            }
        }
    }

    void delete_cascade(BSNode<T>* n) {
        if (n == nullptr) return;
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }

public:
    BSTree() {
        nelem=0;
        root=nullptr;
    }

    ~BSTree() {
        delete_cascade(root);
        root = nullptr;
        nelem = 0;
    }

    int size() const {
        return nelem;
    }

    T search(T e) const {
        BSNode<T>* n = search(root, e);
        return n->elem;
    }

    T operator[](T e) const {
        return search(e);
    }

    void insert(T e) {
        root = insert(root, e);
    }

    void remove(T e) {
        root = remove(root, e);
    }

    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
};

#endif