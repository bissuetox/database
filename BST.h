#ifndef BST_H
    #define BST_H
    #include "TreeNode.h"
    using namespace std;

    template <class T>
    class BST {
        public:
            TreeNode<T>* root;
            int size;

            BST();
            void insert(T data);
            bool search(T data);
            void remove(T data);
    };

    template <class T>
    BST<T>::BST() {
        root = NULL;
    }

    template <class T>
    void BST<T>::insert(T data) {

    }

    template <class T>
    bool BST<T>::search(T data) {

    }

    template <class T>
    void BST<T>::remove(T data) {

    }

#endif