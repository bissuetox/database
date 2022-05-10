#include "BST.h"
#include "Student.h"
#include "Faculty.h"

int main(int argc, char **argv) {
	Faculty f(1, "bob", "professor", "CS");
    f.print();
    Student s(2, "jimmy", "freshman", "CS", 4.0, 1);
    s.print();
    TreeNode<int> tn;
    bool eq1 = f == s;
    bool lt = f < s;
    bool gt = f > s;
    BST<int> bst;
    // bst.insert_iter(5);
    // bst.insert_iter(10);
    // bst.insert_iter(3);
    bst.insert(5);
    bst.inorder(bst.root);
}