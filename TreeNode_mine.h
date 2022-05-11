#ifndef TREENODE_H
    #define TREENODE_H
    #include <iostream>
    using namespace std;

    template <class T>
    class TreeNode {
        public:
            T data;
            TreeNode<T> *left;
            TreeNode<T> *right;
            TreeNode();
            TreeNode(T new_data);
    };

    // Default Constructor
    template <class T>
    TreeNode<T>::TreeNode() {
        left = NULL;
        right = NULL;
        key = NULL;
    }

    // Overloaded Constructor
    template <class T>
    TreeNode<T>::TreeNode(T new_data) {
        data = new_data;
        left = NULL;
        right = NULL;
    }

#endif