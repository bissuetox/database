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
            void insert_iter(T data);
            TreeNode<T>* insert_rec(TreeNode<T>* node, T data);
            void insert(T data);
            bool search(T data);
            void remove(T data);
            void inorder(TreeNode<T> *node);
    };

    template <class T>
    BST<T>::BST() {
        root = NULL;
    }


    template <class T>
    void BST<T>::inorder(TreeNode<T> *node) {
        if (node == NULL) return;
        else {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    // Iterative insertion
    template <class T>
    void BST<T>::insert_iter(T data) {
        TreeNode<T> *newNode = new TreeNode<T>(data);

        // If root is null, make the new node root
        if (root == NULL) {
            root = newNode;
            return;
        }

        TreeNode<T> *curr = root;
        // Traverse until current finds spot
        while(curr != NULL) {
            // If data less than current, look left
            if (data < curr->data) {
                // If left child is null, insert
                if (curr->left == NULL) {
                    curr->left = newNode;
                    curr = NULL; // Break loop
                }
                // Else traverse left
                else {
                    curr = curr->left;
                }
            } else {
                // If right child is null, insert
                if (curr->right == NULL) {
                    curr->right = newNode;
                    curr = NULL; // Break loop
                }
                // Else traverse right
                else {
                    curr = curr->right;
                }
            }
        }
    }

    // Wrapper for recursive insertion so we don't have to worry about passing root
    template <class T>
    void BST<T>::insert(T data) {
        if (root == NULL) {
            root = new TreeNode<T>(data);
        } else {
            insert_rec(root, data);
        }
    }

    // Recursive function for inserting
    template <class T>
    TreeNode<T>* BST<T>::insert_rec(TreeNode<T>* node, T data) {
        // If reached a null location, pass the new node up
        if (node == NULL) {
            return new TreeNode<T>(data);
        }

        // Traverse left
        if (data < node->data) {
            node->left = insert_rec(node->left, data);
        }

        // Traverse right
        else {
            node->right = insert_rec(node->right, data);
        }

        // Bubble up the node after insertion calls
        return node;
    }

    // Recursive Search
    template <class T>
    bool BST<T>::search(T data) {
        if (root == NULL || root->data == data) {
            return root;
        }
        if (root->data < data) {
            return search(root->right, data);
        }

        return search(root->left, data);
    }

    // Iterative Remove
    template <class T>
    void BST<T>::remove(T data) {
        // Track current and parent node
        TreeNode<T> *par = NULL;
        TreeNode<T> *curr = root;

        // Search for node to remove
        while (curr != NULL) {
            // If node is found
            if (curr->data == data) {
                // Leaf case
                if (curr->left == NULL && curr->right == NULL) {
                    // If par is unset, tree only contains root node
                    if (par == NULL) {
                        root = NULL;
                    }
                    // Else dereference appropriate child
                    else if (par->left == curr) {
                        par->left = NULL;
                    } else {
                        par->right = NULL;
                    }
                }

                // Node only has left child
                else if (curr->right == NULL) {
                    // If par is unset, tree only contains root node
                    if (par == NULL) {
                        root = curr->left;
                    }
                    // If node is parents left child, set it
                    else if (par->left == curr) {
                        par->left = curr->left;
                    }
                    // Else node is parent's right child
                    else {
                        par->right = curr->left;
                    }
                }

                // Node only has right child
                else if (curr->left == NULL) {
                    // If par is unset, tree only contains root node
                    if (par == NULL) {
                        root = curr->right;
                    }
                    // If node is parents left child, set it
                    else if (par->left == curr) {
                        par->left = curr->right;
                    }
                    // Else node is parent's right child
                    else {
                        par->right = curr->right;
                    }
                }

                // Node has two children
                else {
                    // Must find successor (leftmost child of right subtree)
                    TreeNode<T> *suc = curr->right;
                    while (suc->left != NULL) {
                        suc = suc->left;
                    }
                    T sucData = suc->data;
                    remove(sucData); // Remove the successor
                    curr->data = sucData; // Replace current's data with successor
                }

                return;
            }
            // Traverse left
            else if (data < curr->data) {
                par = curr;
                curr = curr->left;
            }
            // Traverse right, tracking the parent node
            else {
                par = curr;
                curr = curr->right;
            }
        }
        // Not found if we reached this point
        return;
    }

#endif