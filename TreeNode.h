#ifndef TREENODE_H
    #define TREENODE_H
    template <class T>
    class TreeNode {
        public:
            T data;
            TreeNode *left;
            TreeNode *right;
            TreeNode();
            TreeNode(T new_data);
    };

    // Default Constructor
    template <class T>
    TreeNode<T>::TreeNode() {
        left = NULL;
        right = NULL;
    }

    // Overloaded Constructor
    template <class T>
    TreeNode<T>::TreeNode(T new_data) {
        data = new_data;
        left = NULL;
        right = NULL;
    }

#endif