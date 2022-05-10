#include "BST.h"

int main(int argc, char **argv) {
	// Faculty f(1, "bob", "professor", "CS");
    // f.print();
    // Student s(1, "jimmy", "freshman", "CS", 4.0, 1);
    // s.print();
    // TreeNode<int> tn;
    // cout << tn.data << endl;

    BST<int> bst;
    // bst.insert_iter(5);
    // bst.insert_iter(10);
    // bst.insert_iter(3);
    bst.insert(5);
    bst.inorder(bst.root);
}