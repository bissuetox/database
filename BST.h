#ifndef BST_H
    #define BST_H
    #include <iostream>
    using namespace std;

    template <class T>
    class TreeNode{
        public:
            TreeNode();
            TreeNode(T key);
            virtual ~TreeNode();

            T key; //key = data
            TreeNode<T> *left;
            TreeNode<T> *right;
    };

    template <class T>
    TreeNode<T>::TreeNode(){
        left = NULL;
        right = NULL;
        key = NULL;
    }

    template <class T>
    TreeNode<T>::TreeNode(T k){
        left = NULL;
        right = NULL;
        key = k;
    }

    template <class T>
    TreeNode<T>::~TreeNode(){
        left = NULL;
        right = NULL;
    }

    template <class T>
    class BST{
        public:
            BST();
            virtual ~BST();
            void insert(T value);
            bool contains(T value);//search
            bool deleteNode(T k);
            bool isEmpty();

            T* getMin();
            T* getMax();
            TreeNode<T> *getSuccessor(TreeNode<T> *d); //d represents the node we are going to delete
            void printNodes();
            void recPrint(TreeNode<T> *node);
            T calcSum(TreeNode<T> *node);
            TreeNode<T>* getRoot();
        private:
            TreeNode<T> *root;
    };

    template <class T>
    BST<T>::BST(){
        root = NULL;
    }

    template <class T>
    BST<T>::~BST(){
        //build some character
        //and do a little research
    }

    template <class T>
    TreeNode<T>* BST<T>::getRoot(){
        return root;
    }

    template <class T>
    void BST<T>::recPrint(TreeNode<T> *node){
        if(node == NULL)
            return;

        cout << node->key << endl;
        recPrint(node->left);
        recPrint(node->right);
    }

    template <class T>
    T BST<T>::calcSum(TreeNode<T> *node){
        if(node == NULL)
            return 0;
        
        return (node->key + calcSum(node->left) + calcSum(node->right));
    }

    /*this function prints the entire tree*/
    template <class T>
    void BST<T>::printNodes(){
        recPrint(root);
    }

    template <class T>
    bool BST<T>::isEmpty(){
        return (root == NULL);
    }

    template <class T>
    T* BST<T>::getMin(){
        if(isEmpty())
            return NULL;

        TreeNode<T> *current = root;
        while(current->left != NULL){
            current = current->left;
        }
        return &(current->key);
    }

    template <class T>
    T* BST<T>::getMax(){
        if(isEmpty())
            return NULL;

        TreeNode<T> *current = root;
        while(current->right != NULL){
            current = current->right;
        }
        return &(current->key);
    }

    template <class T>
    void BST<T>::insert(T value){
        TreeNode<T> *node = new TreeNode<T>(value);
        
        if(isEmpty())
            root = node;
        else{
            //the tree is not empty
            TreeNode<T> *current = root;
            TreeNode<T> *parent = NULL;

            while(true){
                parent = current;
                
                if(value < current->key){
                    //we go left
                    current = current->left;
                    if(current == NULL){
                        //we found the insertion point
                        parent->left = node;
                        break;
                    }
                }
                else{
                    //we go right
                    current = current->right;
                    if(current == NULL){
                        //we found the insertion point
                        parent->right = node;
                        break;
                    }
                }
            }
        }
        
    }

    template <class T>
    bool BST<T>::contains(T value){
        if(isEmpty())
            return false;

        TreeNode<T> *current = root;

        while(current->key != value){
            if(value < current->key)
                current = current->left;
            else
                current = current->right;

            if(current == NULL)
                return false;
        }
        return true;
    }

    template <class T>
    bool BST<T>::deleteNode(T key){
        // Track current and parent node
        TreeNode<T> *par = NULL;
        TreeNode<T> *curr = root;

        // Search for node to remove
        while (curr != NULL) {
            // If node is found
            if (curr->key == key) {
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
                    TreeNode<T> *suc = getSuccessor(curr);
                    T sucData = suc->key;
                    remove(sucData); // Remove the successor
                    curr->key = sucData; // Replace current's key with successor
                }

                return true;
            }
            // Traverse left
            else if (key < curr->key) {
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
        return true;
    }

    template <class T>
    /* d represents the node to be delete */
    TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d){
        TreeNode<T> *suc = d->right;
        while (suc->left != NULL) {
            suc = suc->left;
        }
        return suc;
    }

#endif